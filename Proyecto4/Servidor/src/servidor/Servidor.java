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

/**
 *
 * @author abraham
 */
public class Servidor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       SocketUDPSeguro s= new SocketUDPSeguro(7200);
       while(true){
           System.out.println(s.recibirPaquete().toString());
       }
               
    }
    
}
