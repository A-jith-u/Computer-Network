#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define port 9001

int main()
    {
     int sockfd,n1,n2,sum;
     struct sockaddr_in cli_addr;
     socklen_t cli_len=sizeof(cli_addr);
     
     sockfd=socket(AF_INET,SOCK_DGRAM,0);
     if(sockfd<0)
       perror("Error creating socket");
     
     cli_addr.sin_family=AF_INET;
     cli_addr.sin_port=htons(port);
     cli_addr.sin_addr.s_addr=INADDR_ANY;
     
     printf("Enter the first number:");
     scanf("%d",&n1);
     sendto(sockfd,&n1,sizeof(n1),0,(struct sockaddr*)&cli_addr,cli_len);
     
     printf("\nEnter the second number:");
     scanf("%d",&n2);
     sendto(sockfd,&n2,sizeof(n2),0,(struct sockaddr*)&cli_addr,cli_len);
     
     recvfrom(sockfd,&sum,sizeof(sum),0,(struct sockaddr*)&cli_addr,&cli_len);
     printf("\nThe recieved sum is:%d",sum);
     close(sockfd);
    }
