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

int precision[5]={2,3,5,100,10000};
Semaforo sem1, sem2;
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


double CalculaY(double n, int precision){
	//double Y=1.5;
	double Y=M_PI/4; //serie 2
	//double Y=0;
	register int i=0;
	for ( i = 1; i < precision; i++)
	{
		/*if(i%2!=0){
			
			Y+=(6/(i*M_PI))*sin(i*n);
			
		}
		else{
			Y+=0;
		}*/
		Y=Y-((2)/(M_PI*pow((2*i-1),2)))*cos(i*n)+(pow(-1,i+1)/(i))*sin(i*n); //serie 2
		//cout<<precision<<endl;
		//Y=Y+(2/i)*(pow(-1,i+1))*sin(i*n);
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
	//if(control2==0){
		sem1.wait();
	//}
	
	while(aux<16){
		switch(control2){
			case 0:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,1,(double)aux,(double)coordenadas.find(aux)->second);
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
		
		datos=respuesta->X;
		numeroSecuenciaRecibido=(respuesta->messageType);
		if(numeroSecuenciaRecibido!=numeroSecuencia){
			cout<<"Me ha llegado la respuesta  de "<<numeroSecuenciaRecibido<<" pero yo quiero la respuesta de "<<numeroSecuencia<<endl;
			cout<<"sigo en el hilo 1"<<endl;
			if(numeroSecuenciaRecibido==-1)
				numeroSecuencia--;

		}
		else{
				cout<<"Antes tenia usted $"<<numeroSecuencia<<" ahora tiene $"<<datos<<endl;
				cout<<datos<<endl;
				numeroSecuencia++;
				aux+=0.2;
				entrada-=0.2;
			
		}
		cout<<"ENtrada=="<<entrada<<endl;
		cout<<"Control2=="<<control2<<endl;
		
	}
	//sem2.post();
	//if(control2==0){
		sem2.post();
		
	//}
	control2++;
	
}	

void funcion2(string ip, string ip2, double entrada, Solicitud cliente){
	double aux2=1;
	//if(control2==0){
		sem2.wait();
	//}
	
	while(aux2<16){
		switch(control2){
			case 1:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,2,(double)aux2,(double)coordenadas.find(aux2)->second);
				break;
			case 2:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,4,(double)aux2,(double)coordenadas2.find(aux2)->second);
				break;
			case 3:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,6,(double)aux2,(double)coordenadas3.find(aux2)->second);
				break;
			case 4:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,8,(double)aux2,(double)coordenadas4.find(aux2)->second);
				break;
			case 5:
				prueba=FormarMensaje(numeroSecuencia,entrada,ip,7777,10,(double)aux2,(double)coordenadas5.find(aux2)->second);
				break;
		}
		
		
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
				aux2+=0.2;
				//entrada-=0.2;
				cout<<"Control2=="<<control2<<endl;
			
		}
		//sem1.post();
		
		
	}
	
	//if(control2==0){
		sem1.post();
	//}
	
	
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
	Solicitud cliente(ip);
	int fase=40;
	do{
		sem1.init(1);
		sem2.init(0);
		CreaCoordenadas(fase,precision[entrada],control);
		thread th1(funcion1,ip,ip2,200,cliente), th2(funcion2, ip, ip2, 200,cliente);
		th1.join();
		th2.join();
		entrada+=1;
		coordenadas.clear();
		control++;
	}while(1);
	

	
	
	

	
	return 0;
}
