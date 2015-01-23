#include<sys/socket.h>

#define PORT 4000
#define MAXDATASIZE 1000

int main(int argc,char *argv[])
{
int sockfd,numbytes;
char buf[MAXDATASIZE];
struct hostent *he;
struct sockaddr_in their_addr;

if(argc!=2)
{
fprintf(stderr,"usage: client hostname\n");
exit(1);
}
if((he=gethostbyname(argv[1]))==NULL)
{
herror("gethostbyname");
exit(1);
}

if((sockfd=socket(PF_INET,SOCK_STREAM,0))==-1)
{
perror("socket");
exit(1);
}
their_addr.sin_family=AF_INET;
their_addr.sin_port=htons(PORT);
their_addr.sin_addr=*((struct in_addr *)he->h_addr);
if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1)
{
perror("connect");
exit(1);
}
if((numbytes=recv(sockfd,buf,MAXDATASIZE-1,0)));
perror("recv");
printf("\n");
printf("the data recorded is %s \n",buf); // dhruti: no problems with printing when i executed ur code it printed hello world
return 0;
}
