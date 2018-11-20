package servidor;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author abraham
 */
public class Mensaje {
    private int messageType;
    private int requestId;
    private String IP;
    int puerto;
    int operationId;
    private double X;
    private double Y;
    

    public Mensaje(){};
    public Mensaje(int messageType, int requestId, String IP, int puerto, int operationId, double X, double Y) {
        this.messageType = messageType;
        this.requestId = requestId;
        this.IP = IP;
        this.puerto = puerto;
        this.operationId = operationId;
        this.X=X;
        this.Y=Y;
    }

    public int getMessageType() {
        return messageType;
    }

    public int getRequestId() {
        return requestId;
    }

    public String getIP() {
        return IP;
    }

    public int getPuerto() {
        return puerto;
    }

    public int getOperationId() {
        return operationId;
    }

   

    public void setMessageType(int messageType) {
        this.messageType = messageType;
    }

    public void setRequestId(int requestId) {
        this.requestId = requestId;
    }

    public void setIP(String IP) {
        this.IP = IP;
    }

    public void setPuerto(int puerto) {
        this.puerto = puerto;
    }

    public void setOperationId(int operationId) {
        this.operationId = operationId;
    }

    public double getX() {
        return X;
    }

    public double getY() {
        return Y;
    }

    public void setX(double X) {
        this.X = X;
    }

    public void setY(double Y) {
        this.Y = Y;
    }

    @Override
    public String toString() {
        return "Mensaje{" + "messageType=" + messageType + ", requestId=" + requestId + ", IP=" + IP + ", puerto=" + puerto + ", operationId=" + operationId + ", X=" + X + ", Y=" + Y + '}';
    }
    
    
    

 
    
    
}
