/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import org.jfree.chart.*;
import org.jfree.ui.RefineryUtilities;

/**
 *
 * @author abraham
 */
public class Servidor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
       LineChart_AWT chart = new LineChart_AWT("F(x)" ,"Serie de fourier");
       chart.pack( );
        RefineryUtilities.centerFrameOnScreen( chart );
        chart.setVisible( true );
    
       SocketUDPSeguro s= new SocketUDPSeguro(7200);
     
       Mensaje m;
       
       while(true){
           m=s.recibirPaquete();
           System.out.println(m.toString());
           if(m.operationId==1)
                chart.datasets.add(m.getX(), m.getY());
                
           else{
               try {
                  chart.datasets.remove(m.getX()); 
               } catch (Exception e) {
               }
               
           }
           try {
               java.util.concurrent.TimeUnit.MILLISECONDS.sleep(100);
           } catch (InterruptedException ex) {
               Logger.getLogger(Servidor.class.getName()).log(Level.SEVERE, null, ex);
           }

        
       }
        
        

        
        
    }
    
    
}
