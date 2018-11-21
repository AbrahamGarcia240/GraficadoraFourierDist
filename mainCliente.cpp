#include <stdio.h>
#include <iostream>
#include <string>
#include <map> 
#include <thread>
#include "Solicitud.h"
#include "mensaje.h"
#include "Semaforo.h"
using namespace std;

Semaforo sem1, sem2;
map <int, double> coordenadas;
mensaje prueba;
double datos;
int numeroSecuenciaRecibido;
int n=1;
int numeroSecuencia=1;  
     
char *resultado=(char*)malloc(sizeof(TAM_MAX_DATA));
void CreaCoordenadas(int n){
	register int i;
	for (i=1; i<=n; i++){
		 coordenadas.insert(pair <int, double> (i, (double)(3*i+2))); 
	}

}

mensaje FormarMensaje(int numeroSecuencia, int entrada, string ip, int puerto, int operationId, double X, double Y){
	mensaje prueba;
	prueba.messageType=numeroSecuencia;
	prueba.requestId=entrada;
	memcpy(prueba.IP,(char *)ip.c_str(),16);
	prueba.puerto=puerto; //MI PUERTO
	prueba.operationId=operationId ;
	prueba.X=X;
	prueba.Y=Y;

	return prueba;
}

void funcion1(string ip, string ip2, int entrada, Solicitud cliente)
{
	int aux=1;
	sem1.wait();
	while(entrada>0){
		
		prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,1,(double)aux,(double)coordenadas.find(numeroSecuencia)->second);
		
		mensaje *respuesta=(mensaje*)malloc(sizeof(mensaje));
		respuesta=((mensaje*)(cliente.doOperation((unsigned char *)ip2.c_str(),7200,prueba.operationId,(char *)&prueba))); //PUERTO DEL SERVIDOR
		datos=respuesta->X;
		numeroSecuenciaRecibido=(respuesta->messageType);
		if(numeroSecuenciaRecibido!=numeroSecuencia){
			cout<<"Me ha llegado la respuesta  de "<<numeroSecuenciaRecibido<<" pero yo quiero la respuesta de "<<numeroSecuencia<<endl;
			if(numeroSecuenciaRecibido==-1)
				numeroSecuencia--;
		}
		else{
				cout<<"Antes tenia usted $"<<numeroSecuencia<<" ahora tiene $"<<datos<<endl;
				cout<<datos<<endl;
				numeroSecuencia++;
				aux++;
				entrada--;
			
		}
		
		
	}
	sem2.post();
}

void funcion2(string ip, string ip2, int entrada, Solicitud cliente){
	int aux=1;
	sem2.wait();
	while(entrada>0){
		
		prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,2,(double)aux,(double)coordenadas.find(numeroSecuencia)->second);
		
		mensaje *respuesta=(mensaje*)malloc(sizeof(mensaje));
		respuesta=((mensaje*)(cliente.doOperation((unsigned char *)ip2.c_str(),7200,prueba.operationId,(char *)&prueba))); //PUERTO DEL SERVIDOR
		datos=respuesta->X;
		numeroSecuenciaRecibido=(respuesta->messageType);
		if(numeroSecuenciaRecibido!=numeroSecuencia){
			cout<<"Me ha llegado la respuesta  de "<<numeroSecuenciaRecibido<<" pero yo quiero la respuesta de "<<numeroSecuencia<<endl;
			if(numeroSecuenciaRecibido==-1)
				numeroSecuencia--;
		}
		else{
				cout<<"Antes tenia usted $"<<numeroSecuencia<<" ahora tiene $"<<datos<<endl;
				cout<<datos<<endl;
				numeroSecuencia++;
				aux++;
				entrada--;
			
		}
		
		
	}
	sem1.post();
}

int main(int argc, char const *argv[])
{	

	

	if(argc<3){
		cout<<"Modo de uso ./mainCliente <ip_cliente> <ip_servidor>"<<endl;
		return 0;
	}
	int entrada;
	cout<<"Ingrese el monto a ingresar"<<endl;
	cin>>entrada;
	CreaCoordenadas(entrada);
	std::string ip(argv[1]); //mi IP
	std::string ip2(argv[2]); //IP DEL SERVIDOR
	Solicitud cliente(ip);
	sem1.init(1);
	sem2.init(0);
	thread th1(funcion1,ip,ip2,entrada,cliente), th2(funcion2, ip, ip2, entrada,cliente);

	th1.join();
	th2.join();

	
	
	

	
	return 0;
}
