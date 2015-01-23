//#include<winsock.h>
//#include<ws2_32.lib>
#include<winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#include<sys/types.h>
//#include<sys/socket.h>
//#include<netdb.h>
//#include<netinet/in.h>
#define MYPORT 5500
#define NUM_CONNECTIONS 10

/*bind(int,struct sockaddr*,int);
listen(int,int);
send(int,char*,int,int);
accept(int,struct sockaddr*,int);*/

int main(int argc,char* argv[])
{

int sock_id,list_ret,new_sock_id;
int bind_ret,send_ret;
struct sockaddr_in serv_addr,clint_addr;

//socklen_t len;
SOCKET sockfd, new_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size, socks, rv;
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(7869);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	memset(&(my_addr.sin_zero), '\0', 8);

	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	listen(sockfd, 1);

	sin_size = sizeof(struct sockaddr_in);
	
	fd_set selectfds;
	timeval tv;
	
	FD_ZERO(&selectfds);
	
	FD_SET(new_fd, &selectfds);
	
	socks = new_fd + 1;
	
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	
	rv = select(1, &selectfds, NULL, NULL, &tv);
	
	if (rv == -1)
	{
		cout << "select error.";
	}
	else if (rv == 0)
	{
		cout << "nothing to select.";
	}
	else
	{
		if (FD_ISSET(new_fd, &selectfds))
		{
			cout << "accepting.";
		}
	}
}