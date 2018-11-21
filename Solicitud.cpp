#include <stdio.h>
#include <iostream>
#include <string>
#include "PaqueteDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"
#include <string>


using namespace std;


Solicitud::Solicitud(string ip){
	sockt=new SocketDatagrama(7777, ip);
}

char* Solicitud::doOperation(unsigned char *IP, int puerto, int operationId, char* argumentos){
	PaqueteDatagrama packet(argumentos,sizeof(mensaje),IP,puerto);	
	//cout<<"Longitud del paquete: "<<packet.obtieneLongitud()<<endl;
	//cout<<"Bytes enviados: "<<endl;

	int i=0;
	do{	
		if(sockt->enviaTimeout(packet,0,3000)>0){
			break;
		}
		else{
			cout<<"Intentando enviar solicitud al servidor"<<endl;
		}

		i++;
	}while(i<6);
	if(i==6)
		cout<<"El servidor no esta disponible, intente mas tarde"<<endl;


	//cout<<"Bytes recibidos: "<<sockt->recibe(packet)<<endl;

	do{	
		if(sockt->recibeTimeout(packet,0,3000)>0){
			break;
		}
		else{
			sockt->enviaTimeout(packet,0,3000);
			cout<<"Intentando enviar solicitud al servidor"<<endl;
		}

		i++;
	}while(1);
	if(i==6)
		cout<<"El servidor no esta disponible, intente mas tarde"<<endl;
	

	return packet.obtieneDatos();
	
}
