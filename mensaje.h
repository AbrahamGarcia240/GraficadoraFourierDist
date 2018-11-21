
#include <stdio.h>
#include <unistd.h>

using namespace std;

#define TAM_MAX_DATA 4000

struct mensaje{
 int messageType; //0= Solicitud, 1 = Respuesta
 unsigned int requestId; //Identificador del mensaje
 unsigned char IP[16];
 int puerto;
 int operationId; //Identificador de la operación
 double X;
 double Y;
};