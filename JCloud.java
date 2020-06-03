package game_of_life;
import javax.swing.JPanel;
import java.awt.*;

public class JCloud extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int tempCloud=0;
	private int tempPolution=0;
	private int tempWind=0;


	
	public JCloud(int C,int P,int Wind){
		tempCloud=C;
		tempPolution=P;
		tempWind=Wind;

	}
	
	@Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        // maybe dont tuch
        repaint();
//        removeAll();

        int width=getWidth();
        int height=getHeight();
         if (tempCloud==1) {
         g.drawOval(0, 0,(int) width,(int) height);
         }
         if (tempPolution==1) {
             g.drawLine(0, 0,(int) width,(int) height);
             g.drawLine((int)width ,0 , 0,(int) height);
            
         }
         //add wind
         if (tempWind==1) { //south wind
        	 g.drawLine(width/2,0 ,  width/2, height);
        	 g.drawLine( width/2, height,(int)(width*0.25) ,(int)(height*0.75));
        	 g.drawLine( width/2, height,(int)(width*0.75) ,(int)(height*0.75));
        	 

         }
         if (tempWind==2) { //south west
        	 g.drawLine(0,height/2,  width, height/2);
        	 g.drawLine( 0,height/2,(int)(width*0.25) ,(int)(height*0.25));
        	 g.drawLine( 0,height/2,(int)(width*0.25) ,(int)(height*0.75));
         }
         if (tempWind==3) { //south north
        	 g.drawLine(width/2,0,  width/2, height);
        	 g.drawLine( width/2,0,(int)(width*0.25) ,(int)(height*0.25));
        	 g.drawLine( width/2,0,(int)(width*0.75) ,(int)(height*0.25));
         }
         if (tempWind==4) { //south east
        	 g.drawLine(0,height/2,  width, height/2);
        	 g.drawLine( width, height/2,(int)(width*0.75) ,(int)(height*0.25));
        	 g.drawLine( width, height/2,(int)(width*0.75) ,(int)(height*0.75));
         }
         
//         repaint();
    }
	

	
}

