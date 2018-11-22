#include <stdio.h>
#include <iostream>
#include <string>
#include <map> 
#include <math.h>
#include <thread>
#include "Solicitud.h"
#include "mensaje.h"
#include "Semaforo.h"
#include <atomic>

using namespace std;

int precision[5]={2,3,4,5,6};
map <double, double> coordenadas;
map <double, double> coordenadas2;
map <double, double> coordenadas3;
map <double, double> coordenadas4;
map <double, double> coordenadas5;
mensaje prueba;
double datos;
atomic<int> numeroSecuenciaRecibido(0);
int n=1;
atomic<int> numeroSecuencia(1);  
int control=0;
atomic<int> control2(0);    
char *resultado=(char*)malloc(sizeof(TAM_MAX_DATA));
mutex m;


double CalculaY(double n, int precision){
	double Y=M_PI/4; //serie 2
	
	register int i=0;
	for ( i = 1; i < precision; i++)
	{
		Y=Y-((2)/(M_PI*pow((2*i-1),2)))*cos(i*n)+(pow(-1,i+1)/(i))*sin(i*n); //serie 2
	}

	return Y;
}

void CreaCoordenadas(int n, int precision, int control){
	register double i;
	switch(control){
		case 0:
			for (i=1; i<=n; i+=0.2){
				 coordenadas.insert(pair <double, double> (i, CalculaY(i,precision))); 
			}
			break;
		case 1:
			for (i=1; i<=n; i+=0.2){
				 coordenadas2.insert(pair <double, double> (i, CalculaY(i,precision))); 
			}
			break;
		case 2:
			for (i=1; i<=n; i+=0.2){
				 coordenadas3.insert(pair <double, double> (i, CalculaY(i,precision))); 
			}
			break;
		case 3:
			for (i=1; i<=n; i+=0.2){
				 coordenadas4.insert(pair <double, double> (i, CalculaY(i,precision))); 
			}
			break;
		case 4:
			for (i=1; i<=n; i+=0.2){
				 coordenadas5.insert(pair <double, double> (i, CalculaY(i,precision))); 
			}
			break;
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



void funcion1(string ip, string ip2, double entrada, Solicitud cliente)
{
	double aux=1;
	if(control2!=0){
		numeroSecuencia--;
		//sem1.wait();
	}
	
	
	while(aux<16){
		switch(control2){
			case 0:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,1,(double)aux,(double)coordenadas.find(aux)->second);
				break;
			case 5:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,1,(double)aux,(double)coordenadas5.find(aux)->second);
				break;
			
			case 1:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,3,(double)aux,(double)coordenadas2.find(aux)->second);
				break;
			case 2:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,5,(double)aux,(double)coordenadas3.find(aux)->second);
				break;
			case 3:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,7,(double)aux,(double)coordenadas4.find(aux)->second);
				break;
			case 4:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,9,(double)aux,(double)coordenadas5.find(aux)->second);
				break;

		}
		
		
		mensaje *respuesta=(mensaje*)malloc(sizeof(mensaje));
		
		respuesta=((mensaje*)(cliente.doOperation((unsigned char *)ip2.c_str(),7200,prueba.operationId,(char *)&prueba))); //PUERTO DEL SERVIDOR
		
		//usleep(300000);
		datos=respuesta->X;
		numeroSecuenciaRecibido=(respuesta->messageType);
		if(numeroSecuenciaRecibido!=numeroSecuencia){
			//cout<<"Me ha llegado la respuesta  de "<<numeroSecuenciaRecibido<<" pero yo quiero la respuesta de "<<numeroSecuencia<<endl;
			//cout<<"sigo en el hilo 1"<<endl;
			if(numeroSecuenciaRecibido==-1)
				numeroSecuencia--;
			

		}
		else{
				//cout<<"Recibio de manera correcta a "<<numeroSecuencia<<" en el hilo 1"<<endl;
				
				numeroSecuencia++;
				aux+=0.2;
				entrada-=0.2;
			
		}
		//cout<<"ENtrada=="<<entrada<<endl;
		//cout<<"Control2=="<<control2<<endl;

		switch(control2){
			case 1:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,2,(double)aux,(double)coordenadas.find(aux)->second);
				break;
			case 2:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,4,(double)aux,(double)coordenadas2.find(aux)->second);
				break;
			case 3:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,6,(double)aux,(double)coordenadas3.find(aux)->second);
				break;
			case 4:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,8,(double)aux,(double)coordenadas4.find(aux)->second);
				break;
			case 5:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,10,(double)aux,(double)coordenadas5.find(aux)->second);
				break;

		}
		
		
		
		
		respuesta=((mensaje*)(cliente.doOperation((unsigned char *)ip2.c_str(),7201,prueba.operationId,(char *)&prueba))); //PUERTO DEL SERVIDOR
		
		//usleep(300000);
		datos=respuesta->X;
		numeroSecuenciaRecibido=(respuesta->messageType);
		if(numeroSecuenciaRecibido!=numeroSecuencia){
			cout<<"Me ha llegado la respuesta  de "<<numeroSecuenciaRecibido<<" pero yo quiero la respuesta de "<<numeroSecuencia<<endl;
			//cout<<"sigo en el hilo 1"<<endl;
			if(numeroSecuenciaRecibido==-1)
				numeroSecuencia--;

		}
		else{
			//	cout<<"Recibio de manera correcta a "<<numeroSecuencia<<" en el hilo 1"<<endl;
				
				numeroSecuencia++;
				aux+=0.2;
				entrada-=0.2;
			
		}
	}
	//sem2.post();
	if(control2==6){
		control2=1;
	}
	control2++;
	
	
	//sem2.post();
	
	
}	


int main(int argc, char const *argv[])
{	

	

	if(argc<3){
		cout<<"Modo de uso ./mainCliente <ip_cliente> <ip_servidor>"<<endl;
		return 0;
	}
	int entrada=0;
	std::string ip(argv[1]); //mi IP
	std::string ip2(argv[2]); //IP DEL SERVIDOR
	Solicitud cliente(ip,7777);
	Solicitud cliente2(ip,7778);
	control2=0;
	
	do{
		control=0;
		int fase=40;
		entrada=0;
		register int i;
		for(i=0;i<6;i++){
			CreaCoordenadas(fase,precision[i],i);
		}
		
	
		do{
			
			
			thread th1(funcion1,ip,ip2,200,cliente);
			//thread th2(funcion2, ip, ip2, 200,cliente2);
			th1.join();
			//th2.join();
			entrada+=1;
			coordenadas.clear();
			control++;
		}while(entrada<6);

		control2=1;
		for(i=0;i<6;i++){
			precision[i]+=5;
			
		}
		
		coordenadas.clear();
		coordenadas2.clear();
		coordenadas3.clear();
		coordenadas4.clear();
		coordenadas5.clear();
		
	}while(1);

	
	
	

	
	return 0;
}
