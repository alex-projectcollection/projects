package com.example.parkingfinderapp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.android.material.textfield.TextInputEditText;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class LoginActivity extends AppCompatActivity {

    int state=1;

    TextView errormes;

    TextInputEditText userName, pass;
    Button signIn, regester;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);


        userName = (TextInputEditText) findViewById(R.id.userText);
        pass = (TextInputEditText) findViewById(R.id.passText);
        signIn = (Button) findViewById(R.id.sign_in_button);
        regester = (Button) findViewById(R.id.create_new_account);

        errormes = (TextView) findViewById(R.id.erroText);

        // sign in button
        signIn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                    state=1;
                   new LogTask().execute();

            }
        });

        //register new user button
        regester.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
            state=2;
            new LogTask().execute();
            }
        });

    }

        // main task to connect to db creating new users or conncting to main activiry
        class LogTask extends AsyncTask<Void, Void, Void> {
            String errorTop="" ,index="2",newUser="",newPass="";

            @SuppressLint("WrongThread")
            protected Void doInBackground(Void... voids) {

                try {

                    Class.forName("com.mysql.jdbc.Driver").newInstance();
                    Connection connection = DriverManager.getConnection("jdbc:mysql://10.100.102.5:3306/android", "andro", "andro");
                    Statement statement = connection.createStatement();

                    ResultSet resultSet = statement.executeQuery("SELECT * FROM users");

                    while (resultSet.next()) {

                        if (state == 1) {

                            if ((userName.getEditableText().toString().compareTo(resultSet.getString(2)) == 0) && (pass.getEditableText().toString().compareTo(resultSet.getString(3)) == 0)) {
                                Intent intent = new Intent(LoginActivity.this, MapsActivity.class);
                                startActivity(intent);
                                break;

                            } else if ((userName.getEditableText().toString().compareTo(resultSet.getString(2)) != 0) || (pass.getEditableText().toString().compareTo(resultSet.getString(3)) != 0)) {
                                errorTop = "user name or password are incorrect";
                                continue;

                            }
                            } else if (state == 2) {
                                if (Integer.parseInt(index) == Integer.parseInt(resultSet.getString(1))) {

                                    index = resultSet.getString(1);
                                }
                                newUser = "'" + userName.getEditableText().toString() + "'";
                                newPass = "'" + pass.getEditableText().toString() + "'";

                                statement.executeUpdate("INSERT INTO users VALUES (" + Integer.parseInt(index) + "," + newUser + "," + newPass + ")");
                                errorTop="new  account created";
                                break;

                            }
                        }

                } catch (Exception e) {
                   errorTop=e.toString();

                        e.printStackTrace(System.err);
                        System.err.println("SQLState: " +
                                ((SQLException)e).getSQLState());

                        System.err.println("Error Code: " +
                                ((SQLException)e).getErrorCode());

                        System.err.println("Message: " + e.getMessage());

                        Throwable t = e.getCause();
                        while(t != null) {
                            System.out.println("Cause: " + t);
                            t = t.getCause();
                        }

                }

                return null;
            }

            protected void onPostExecute(Void aVoid) {

                errormes.setText(errorTop);

                super.onPostExecute(aVoid);
            }

            }


        }





