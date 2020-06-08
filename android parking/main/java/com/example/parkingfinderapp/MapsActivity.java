package com.example.parkingfinderapp;


import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.fragment.app.FragmentActivity;


import android.Manifest;
import android.annotation.SuppressLint;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.location.Location;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Random;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback , TaskLoadedCallback{
    private GoogleMap mMap;
    MarkerOptions markerOptions;

    Location currentLocation;
    Location closest, lastpark ;


    MarkerOptions place1,place2;
    Polyline route;

    ArrayList<String> parkinglocationslat ;
    ArrayList<String> parkinglocationslong ;

    FusedLocationProviderClient fusedLocationProviderClient;
    private static final int REQUEST_CODE=101;
    int state= 0,refres=0;
    TextView text, errortext;
    Button show, nextlocation , whereIParked, refresh;
    boolean didIPark=false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);

        //MAP STUFF
        fusedLocationProviderClient = LocationServices.getFusedLocationProviderClient(this);
        fetchLastLocation();

        //UI elements
        text = (TextView) findViewById(R.id.textView);
        errortext = (TextView) findViewById(R.id.textView2);
        show = (Button) findViewById(R.id.button);

        //GENERATION DETABASE AND SHOWING THE RECORDS

        show.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(state==2){
                state=1;
                }
                new Async().execute();


            }
        });

        //CREATING ROUTE TO CLOSEST LOCATION
        nextlocation =(Button) findViewById(R.id.button2);

        nextlocation.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                state=2;
                new Async().execute();

              findClosest(parkinglocationslat,parkinglocationslong);

                mMap.clear();

                navigat(currentLocation,closest,"CLOSEST PARKING");

                lastpark =new Location(closest);
                didIPark=true;
            }
        });

        // DIRECTION BACK TO PARKED CAR
        whereIParked=(Button) findViewById(R.id.lastpark);

        whereIParked.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(didIPark=true) {
                    mMap.clear();
                    navigat(currentLocation, lastpark, "MY CAR");

                }

            }
        });

        //REFRESHING THE DATABASE BUTTON
        refresh=(Button) findViewById(R.id.loop);

        refresh.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("SourceLockedOrientationActivity")
            @Override
            public void onClick(View view) {
                if(refres==0){
                    refres=1;
                    new Async2().execute();
                }else if (refres==1) {
                    refres=2;
                    //BUG FIX
                    mMap.clear();

                }else {
                    refres=0;
                    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
                    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
                }
            }
        });

    }

    //creates the polyline and calculates the rute beetwn 2 locations

    private void navigat(Location loc1 ,Location loc2 , String wherTo){

        place1=new MarkerOptions().position(new LatLng(loc1.getLatitude(),loc1.getLongitude())).title("MY LOCATION");

        place2=new MarkerOptions().position(new LatLng(loc2.getLatitude(),loc2.getLongitude())).title(wherTo);

        String url =getUrl(place1.getPosition(),place2.getPosition(),"driving");

        new FetchURL(MapsActivity.this).execute(url,"driving");


        mMap.addMarker(place1);
        mMap.addMarker(place2);

    }
    //CREATES THE URL FOR THE DIRECTION API JASON
    private String getUrl(LatLng origin, LatLng dest, String directionMode) {

        String str_origin = "origin=" + origin.latitude + "," + origin.longitude;

        String str_dest = "destination=" + dest.latitude + "," + dest.longitude;

        String mode = "mode=" + directionMode;

        String parameters = str_origin + "&" + str_dest + "&" + mode;

        String output = "json";

        String url = "https://maps.googleapis.com/maps/api/directions/" + output + "?" + parameters + "&key=" + getString(R.string.google_maps_key);
        return url;
    }

    //initiaring the mapfragment + checks for premissions + end method last onRequestPermissionsResult used in if
    private void  fetchLastLocation(){
        if(ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)!= PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this ,new String[]
                    {Manifest.permission.ACCESS_FINE_LOCATION},REQUEST_CODE);


            return;
        }

        Task<Location> task = fusedLocationProviderClient.getLastLocation();
        task.addOnSuccessListener(new OnSuccessListener<Location>() {
            @Override
            public void onSuccess(Location location) {
                if (location != null){
                    currentLocation = location;

                    // temp location
                    closest = new Location(currentLocation);
                    Toast.makeText(getApplicationContext(), currentLocation.getLatitude()
                            +""+currentLocation.getLongitude(),Toast.LENGTH_SHORT).show();
                    SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                            .findFragmentById(R.id.map);
                    mapFragment.getMapAsync(MapsActivity.this::onMapReady);
                }
            }
        });
    }


    //implementation  HLEPERS TaskLoadedCallback
    @Override
    public void onTaskDone(Object... values) {

        //worlks on pollyline
        if(route!= null){
            route.remove();
        }
        route = mMap.addPolyline((PolylineOptions) values[0]);

    }

    //main thred for map connecting to db and doing diffrent tasks depending on the boutton pressed
    class Async extends AsyncTask <Void, Void, Void> {
       String records ="" , error="";

        @Override
        protected Void doInBackground(Void... voids) {

            try{
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                Connection connection = DriverManager.getConnection(  "jdbc:mysql://your-ip-and-port/android","andro","andro" );
                Statement statement =connection.createStatement();

                //update at the start and creating db
                if (state==0) {
                    statement.executeUpdate("TRUNCATE TABLE test");


                    //creating random parking location; and inserting them

                    parkinglocationslat = randomPark(currentLocation.getLatitude());
                    parkinglocationslong = randomPark(currentLocation.getLongitude());

                    int counter = 1;
                    while (parkinglocationslat.size() > 0) {
                        statement.executeUpdate("INSERT INTO test VALUES (" + counter + "," + parkinglocationslat.get(0) + "," + parkinglocationslong.get(0) + ")");
                        parkinglocationslat.remove(0);
                        parkinglocationslong.remove(0);

                        counter++;

                    }
                    state=1;
                }

                // printing records and for the next location button creating 2 arrys for the locations
                if( state==1 ||  state==2) {
                    ResultSet resultSet = statement.executeQuery("SELECT * FROM test");

                    //print log
                    while (resultSet.next()) {
                        records += resultSet.getString(1) + " " + resultSet.getString(2) + " " + resultSet.getString(3) + "\n";

                            parkinglocationslat.add(resultSet.getString(2));
                            parkinglocationslong.add(resultSet.getString(3));

                    }
                }

            }


            catch (Exception e){
                error=e.toString();
            }

            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            text.setText(records);
            if(error!="")
                errortext.setText(error);

            super.onPostExecute(aVoid);
        }
    }

    //dinding the closest location out of the arrys created from the db.
    private void findClosest (ArrayList<String> lat,ArrayList<String> longetude){

        double currentdis=0;
        double mindis=0;
        int i=0;

//        if(i==0){
            closest.setLatitude(Double.parseDouble(lat.get(0)));
            closest.setLongitude(Double.parseDouble(longetude.get(0)));
            mindis=calculateDistanceBetween2Points(currentLocation.getLatitude(), closest.getLatitude(),currentLocation.getLongitude(), closest.getLongitude());
//
//        }
        while(lat.size()>i || longetude.size()>i){

            currentdis=calculateDistanceBetween2Points(currentLocation.getLatitude(),Double.parseDouble( lat.get(i)),currentLocation.getLongitude(), Double.parseDouble( longetude.get(i)));

            if (mindis>currentdis){
                closest.setLatitude(Double.parseDouble(lat.get(i)));
                closest.setLongitude(Double.parseDouble(longetude.get(i)));
            }
            i++;
        }




    }
        //distance bettwen 2 points
    public double calculateDistanceBetween2Points(double x1, double y1, double x2, double y2) {

        return Math.sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));

    }

    // generation a random arry of cordinates
    public ArrayList<String> randomPark( double location)    {
        ArrayList<String> parkinglocations = new ArrayList<String>();


        for(int i=0 ;i<10;i++){


            double newcordnate=randcord(location);

            String outcord=Double.toString(newcordnate);


            parkinglocations.add(outcord);
        }

        return(parkinglocations);
    }


    // creatung an infinent loop thet adds and removes records
    class Async2 extends AsyncTask <Void, Void, Void> {
        String records ="" , error="";

        @SuppressLint("WrongThread")
        @Override
        protected Void doInBackground(Void... voids) {
            try {
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                Connection connection = DriverManager.getConnection("jdbc:mysql://10.100.102.5:3306/android", "andro", "andro");
                Statement statement = connection.createStatement();
                records="UPDATE DATABASE ENTERYIES PLESE PRESS AGIN WHEN YOU LIKE TO STOP 3 TIMES TO GENERATE NEW DATABASE";
                text.setText(records);

                boolean loop= true;

                while(loop){

                    if(refres==0||refres==2){
                        break;
                    }
                    Random random = new Random();

                    int index = random.nextInt(10) + 1;

                    //del one
                    statement.executeUpdate("DELETE from test where id = "+index);

                    //add new
                    double newLat=randcord(currentLocation.getLatitude());
                    double newlong=randcord(currentLocation.getLongitude());

                    statement.executeUpdate("INSERT INTO test VALUES (" + index + "," + newLat + "," + newlong + ")");
                    Thread.sleep(1000);
                    System.err.println(" UPDATE COMPLET");
                }

            }catch (Exception e){
                error=e.toString();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid) {

            if(error!="")
                errortext.setText(error);

            super.onPostExecute(aVoid);
        }
    }

    //creates 1 random record for random location arry helper method
    private double randcord(double init){

        int maximum =5000;
        int minimum =-5000;
        Random random = new Random();

        int range = maximum - minimum + 1;
        int randomNum =  random.nextInt(range) + minimum;

        double newcordnate=((double) randomNum)*0.000001+init;

        return newcordnate;
    }

        /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
        //map start
    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

            LatLng latLng =new LatLng(currentLocation.getLatitude(),currentLocation.getLongitude());
            markerOptions =new MarkerOptions().position(latLng).title("MY CURRENT LOCATION.");
            mMap.animateCamera(CameraUpdateFactory.newLatLng(latLng));
            mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(latLng,15));
            mMap.addMarker(markerOptions);

    }


    //premissions
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode){
            case REQUEST_CODE:
                if(grantResults.length>0 && grantResults[0] == PackageManager.PERMISSION_GRANTED){
                    fetchLastLocation();
                }
                break;


        }



    }





}
