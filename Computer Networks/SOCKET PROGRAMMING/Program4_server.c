#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#define MYPORT 4000
#define NUM_CONNECTIONS 10
int main(int argc,char *argv[])
{
int socket_id,bind_ret,listen_ret,newsock_id;
socklen_t len;
struct sockaddr_in serv_addr,client_addr;

socket_id=socket(PF_INET,SOCK_STREAM,0);
if (socket_id<0)
{
printf("socket not created");
}
else
printf("socket id:%d",socket_id);

serv_addr.sin_family=PF_INET;
serv_addr.sin_port=htons(MYPORT);
serv_addr.sin_addr.s_addr=INADDR_ANY;

bind_ret=bind(socket_id,(struct sockaddr_in *)&serv_addr,sizeof(struct sockaddr_in));
printf("The bin ret is %d\n" , bind_ret);

if(bind_ret<0)
{
printf("no bind");
}
//printf("bind_ret:%d",bind_ret);

listen_ret=listen(socket_id,100);
if(listen_ret<0)
{
printf("No listen_ret");
}
printf("listen_ret:%d",listen_ret);
len = sizeof(struct sockaddr);

int send_bytes;
{
printf("socket not created");
}
else
printf("socket id:%d",socket_id);

serv_addr.sin_family=PF_INET;
serv_addr.sin_port=htons(MYPORT);
serv_addr.sin_addr.s_addr=INADDR_ANY;

bind_ret=bind(socket_id,(struct sockaddr_in *)&serv_addr,sizeof(struct sockaddr_in));
printf("The bin ret is %d\n" , bind_ret);

if(bind_ret<0)
{
printf("no bind");
}
//printf("bind_ret:%d",bind_ret);

listen_ret=listen(socket_id,100);
if(listen_ret<0)
{
printf("No listen_ret");
}
printf("listen_ret:%d",listen_ret);
len = sizeof(struct sockaddr);

int send_bytes;

while(1)
{
newsock_id=accept(socket_id,(struct sockaddr_in *)&client_addr,&len);
if(newsock_id>0)
{
send_bytes = send(newsock_id,"Helloworld",14,0);
printf("send bytes %d\n" , send_bytes);
}
else
printf("connection not made");
}

return 0;
}
