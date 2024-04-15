#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

// Sender

int main(int argc,char* argv[])
{
    int PORT=atoi(argv[1]);

	int sockfd;
	struct sockaddr_in servaddr;
	
	memset(&servaddr,0,sizeof(servaddr));
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0)
	{
		printf("Error");
		return 0;
	}
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
	{
		printf("Error");
		return 0;
	}

	char buffer[50];
    strcpy(buffer,argv[2]);

    printf("Message sent = %s\n",buffer);
	
	send(sockfd,buffer,sizeof(buffer),0);

    char ans[50];

    read(sockfd,ans,sizeof(ans));

    printf("Message received = %s\n",ans);
	
	close(sockfd);
	
	return 0;
}