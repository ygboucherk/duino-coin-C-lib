#include <openssl/sha.h>
#include <string.h>
#include <stdbool.h>

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <stdio.h>
#include <stdlib.h>
#define PORT 2811

int ducobalance(int sock) {
	char rawbalance[500];
	double balance;
	send(sock,"BALA",4,0);
	recv(sock,rawbalance,500,0);
  
	balance = atof(rawbalance);
	return balance;
}

int ducologin(int sock, char *username, char *password) {
  char request[200];
  char response[128];
  snprintf(request, sizeof request, "%s%s%s%s", "LOGI,", username, ",", password);
  send(sock,request,strlen(request),0);
  recv(sock,response,100,0);
  if (strstr("OK",response) != NULL) {
		return 0;
	}
	else {
		return 1;
	}
} 



int sendduco(int sock, double amount, char *recipient) {
        char request[256];
        char feedback[256];
        char stramount[50];
        printf("Sending DUCO");
        snprintf(stramount,sizeof stramount, "%f",amount);
        snprintf(request, sizeof request, "%s%s%s%s", "SEND,-,", recipient, ",", stramount);
        send(sock,request,strlen(request),0);
        recv(sock,feedback,256,0);
		if (strstr("OK",feedback) != NULL) {
			return 0;
		}
		else {
			return 1;
		}
}


int connectDuco()
{
        char serverip[20] = "51.15.127.80";
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[] = "";

    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        sin.sin_addr.s_addr = inet_addr(serverip);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
            if(recv(sock, buffer, 64, 0) != SOCKET_ERROR) {
                return sock;
            }
        }
        else
        {
            printf("Server error\n");
        }
        closesocket(sock);

        #if defined (WIN32)
            WSACleanup();
        #endif
    }

    return 0;
}
