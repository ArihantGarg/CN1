#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

// Receiver

#define MAX_CLIENT 5

int main()
{
	int sockfd[MAX_CLIENT],newsockfd[MAX_CLIENT];
	char ans[500]="";
	
	for(int i=0;i<MAX_CLIENT;i++)
	{
        int PORT=5000+i;
		struct sockaddr_in recvaddr,cliaddr;
	
		memset(&recvaddr,0,sizeof(recvaddr));
		
		sockfd[i]=socket(AF_INET,SOCK_STREAM,0);
		
		if(sockfd[i]<0)
		{
			printf("Error");
			return 0;
		}
		
		recvaddr.sin_family=AF_INET;
		recvaddr.sin_port=htons(PORT);
		recvaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		
		if(bind(sockfd[i],(struct sockaddr *)&recvaddr,sizeof(recvaddr))<0)
		{
			printf("Error");
			return 0;
		}
		
		int listenfd=listen(sockfd[i],5);
		
		if(listenfd<0)
		{
			printf("Error");
			return 0;
		}

        int len=sizeof(cliaddr);
		
		newsockfd[i]=accept(sockfd[i],(struct sockaddr *)&cliaddr,(socklen_t *)&len);
		
		char buffer[50];
		
		read(newsockfd[i],buffer,sizeof(buffer));

        int n=0;
        while(buffer[n]!='\0')
            n++;
		
		printf("Message from client %d = %s\n",i,buffer);
		
		int chk=1;
		
		for(int j=0;j<n;j++)
		{
			if(buffer[n-j-1]!=buffer[j])
				chk=0;		
		}
		
		if(chk)
		{
            strcat(ans," ");
			strcat(ans,buffer);
		}
	}
	
	for(int i=0;i<MAX_CLIENT;i++)
	{
		send(newsockfd[i],ans,sizeof(ans),0);
		close(sockfd[i]);
        close(newsockfd[i]);
	}

    printf("Final message = %s\n",ans);
	
	return 0;
}