/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author abraham
 */
public class HIlo extends Thread{
  
    LineChart_AWT chart;
    SocketUDPSeguro s;
    public HIlo( LineChart_AWT chart, SocketUDPSeguro s) {
      
       this.chart=chart;
       this.s=s;
        System.out.println("Levante un socket con el puerto "+s.getPuerto());
    }
    @Override
    public void run() {
       
       
        Mensaje m;
         while(true){
           
             
           m=s.recibirPaquete();
           //m2=s2.recibirPaquete();
           System.out.println(m.toString());
           if(m.operationId==1)
                chart.datasets.add(m.getX(), m.getY());
                
           else if(m.operationId==2){
               try {
                  chart.datasets.remove(m.getX()); 
                   chart.datasets.remove(0);
            
               } catch (Exception e) {
               }
               
           }
           else if(m.operationId==3)
                chart.datasets2.add(m.getX(), m.getY());
                
           else if(m.operationId==4){
               try {
                  chart.datasets2.remove(m.getX()); 
                  chart.datasets2.remove(0);
               } catch (Exception e) {
               }
               
           }
           else if(m.operationId==5)
                chart.datasets3.add(m.getX(), m.getY());
                
           else if(m.operationId==6){
               try {
                  chart.datasets3.remove(m.getX()); 
                  chart.datasets3.remove(0);
               } catch (Exception e) {
               }
               
           }
           if(m.operationId==7)
                chart.datasets4.add(m.getX(), m.getY());
                
           else if(m.operationId==8){
               try {
                  chart.datasets4.remove(m.getX());
                  chart.datasets4.remove(0);
               } catch (Exception e) {
               }
               
           }
           if(m.operationId==9)
                chart.datasets5.add(m.getX(), m.getY());
                
           else if(m.operationId==10){
               try {
                  chart.datasets5.remove(m.getX()); 
                  chart.datasets5.remove(0);
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
