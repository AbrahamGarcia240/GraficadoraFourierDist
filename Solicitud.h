#include <stdio.h>
#include <unistd.h>
#include <string>
#include "SocketDatagrama.h"


using namespace std;


class Solicitud
{
public:
	Solicitud(string ip);
	char * doOperation( unsigned char *IP, int puerto, int operationId, char* argumentos);
private:
	SocketDatagrama *sockt;
};

