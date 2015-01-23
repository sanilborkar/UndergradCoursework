#include <winsock2.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define my_port 8000

int main()
{
	int sock;
	int addr_len, bytes_read;
	char recv_data[1024];

	struct sockaddr_in server_addr , client_addr;

    if ((sock=socket(PF_INET, SOCK_STREAM, 0)) < 0) 
	{
            perror("Socket");
            exit(1);
    }
    
	server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(my_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

	memset(&server_addr, 0, sizeof(server_addr));

//	bzero(&(server_addr.sin_zero),8);

	//bzero(&(server_addr), sizeof(server_addr));
 
	if (bind(sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr)) == -1)
        {
            perror("Bind");
            exit(1);
        }
    
	addr_len = sizeof(struct sockaddr);
	printf("\nUDPServer Waiting for client on port 5000");
	fflush(stdout);
 
    while (1)
    {
			bytes_read = recvfrom(sock,recv_data,1024,0,
                            (struct sockaddr *)&client_addr, &addr_len);
			recv_data[bytes_read] = '\0';
			printf("\n(%s,%d)said:",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

			//convert netid to host short
			printf("%s", recv_data);
			fflush(stdout);
 
     } 
	
	return 0;

}
