
#include <stdio.h>
#include <unistd.h>
#include "SocketDatagrama.h"
#include "mensaje.h"
#include <string>


using namespace std;

class Respuesta{
	public:
	 Respuesta(int pl, String IP);
	 struct mensaje *getRequest(void);
	 void sendReply(char *respuesta, unsigned char *ipCliente, int puertoCliente, int Longitud);
	private:
	 SocketDatagrama *sockt;
};


