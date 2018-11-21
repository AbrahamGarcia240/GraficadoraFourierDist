/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author abraham
 */
public class SocketUDPSeguro {
    private byte[]buffer = new byte [65536];
    DatagramSocket sock;
     int numeroDeSecuencia=1;
    

    public SocketUDPSeguro(int puerto) {
        try {
            this.sock = new DatagramSocket(puerto);
        } catch (SocketException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public Mensaje recibirPaquete(){
         Mensaje m;
        try {
            do{
                DatagramPacket reply =  new DatagramPacket(buffer,buffer.length);

                sock.receive(reply);
                //System.out.println("Ya recibí "+reply.getLength()+" bytes");

                int messageType;
                int requestID;
                int operationID;
                int puerto;
                double X;
                double Y;

                byte[] data = reply.getData();
                ByteBuffer buf = ByteBuffer.wrap(data);
                buf.order(ByteOrder.LITTLE_ENDIAN);
                messageType = buf.getInt();
                requestID = buf.getInt();
                byte[] bytes= new byte[16];
                for(int i=0; i<16; i++)
                    bytes[i]=buf.get();

                puerto = buf.getInt();
                operationID = buf.getInt();
                X= buf.getDouble();
                Y= buf.getDouble();
                m=new Mensaje(messageType, requestID, new String(bytes), puerto, operationID, X, Y);
                //System.out.println(m.toString());
            
            }while(!this.ValidarYResponder(m));
            
            
            return m;
            
            
            
        } catch (IOException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
        }
         m= new Mensaje();
        return m;
               
    }
    
    private Boolean ValidarYResponder(Mensaje m){
        int numeroRecibido=m.getMessageType();
        m.toString();
        if(numeroDeSecuencia==numeroRecibido){
            numeroDeSecuencia++;
            this.Responder(m);
            return true;
        }
        else if(numeroDeSecuencia-1==numeroRecibido){
             this.Responder(m);
             return false;
         }
        else{
            this.Responder(m);
            return false;
        }
    }
    
    
    private void Responder(Mensaje m){
        ByteBuffer buf = ByteBuffer.allocate(4032);
        buf.order(ByteOrder.LITTLE_ENDIAN);
        buf.putInt(m.getMessageType()); //Mínimo valor entero
        buf.putInt(m.getRequestId());
        try {
            InetAddress host = InetAddress.getByName(m.getIP());
        
        buf.put(m.getIP().getBytes()); 
        buf.putInt(m.getPuerto());
        buf.putInt(m.getOperationId());
        String datos=String.valueOf(m.getX())+","+String.valueOf(m.getY());
        buf.put(datos.getBytes());
        
        DatagramPacket dp = new DatagramPacket(buf.array() , buf.limit(), host , m.getPuerto());
        sock.send(dp);
        } catch (UnknownHostException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
        }
       
            
        
    }
}
