#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
#include <iostream.h>

#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);

void main(int argc, char *argv[])
{
int sock;
struct sockaddr_in echoServAddr;
unsigned short echoServPort;
int servIP;
const char *echoString;
char echoBuffer[RCVBUFSIZE];
int echoStringLen;
int bytesRcvd, totalBytesRcvd;
WSADATA wsaData;

/*
if ((argc < 3) || (argc > 4))
{
fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",argv[0]);
exit(1);
}



if (argc == 4)
echoServPort = atoi(argv[3]);
else
echoServPort = 7;
*/

servIP = 5000;
echoString = "hello";

if (WSAStartup(MAKEWORD(2, 0),
&wsaData) != 0)
{
fprintf(stderr,"WSAStartup() failed");
exit(1);
}

if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
DieWithError("socket() failed");

memset(&echoServAddr, 0, sizeof(echoServAddr));

/*echoServAddr.sin_family = AF_INET;
echoServAddr.sin_addr.s_addr = inet_addr(servIP);
echoServAddr.sin_port = htons(echoServPort);*/

	echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_port = htons(servIP);
    echoServAddr.sin_addr.s_addr = INADDR_ANY;


if (accept(sock, (struct sockaddr *) &echoServAddr, (int*)sizeof(&echoServAddr)) < 0)
DieWithError("connect() failed");

//cout<<"accept: "<<accept(sock, (struct sockaddr *) &echoServAddr, (int*)sizeof(&echoServAddr))<<endl;
//cout<<sock<<endl;

echoStringLen = strlen(echoString);
//cout<<echoStringLen<<"\t"<<strlen(echoString)<<"\t"<<send(sock, echoString, echoStringLen, 0);

if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
DieWithError("send() sent a different number of bytes than expected");

totalBytesRcvd = 0;
printf("Received: ");

while (totalBytesRcvd < echoStringLen)
{
	bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);

if (bytesRcvd <= 0)
DieWithError("recv() failed or connection closed prematurely");

totalBytesRcvd += bytesRcvd;
echoBuffer[bytesRcvd] = '\0';
printf(echoBuffer);
}
printf("\n");

closesocket(sock);
WSACleanup();
exit(0);
}

void DieWithError(char *errorMessage)
{
fprintf(stderr,"%s: %d\n",
errorMessage, WSAGetLastError());
exit(1);
}
