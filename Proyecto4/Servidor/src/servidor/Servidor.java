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
       SocketUDPSeguro s2= new SocketUDPSeguro(7201);
       Thread t1= new HIlo( chart,s);
       Thread t2 = new HIlo(chart,s2);
       
       t1.start();
       t2.start();
       
        
        

        
        
    }
    
    
}
