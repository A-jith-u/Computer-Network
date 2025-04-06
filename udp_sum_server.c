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
     struct sockaddr_in ser_addr,cli_addr;
     socklen_t cli_len=sizeof(cli_addr);
     
     sockfd=socket(AF_INET,SOCK_DGRAM,0);
     if(sockfd<0)
       perror("Error creating socket");
     
     ser_addr.sin_family=AF_INET;
     ser_addr.sin_port=htons(port);
     ser_addr.sin_addr.s_addr=INADDR_ANY;
     int b=bind(sockfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
     if(b<0)
       perror("Error binding socket");
     
     recvfrom(sockfd,&n1,sizeof(n1),0,(struct sockaddr*)&cli_addr,&cli_len);
     recvfrom(sockfd,&n2,sizeof(n2),0,(struct sockaddr*)&cli_addr,&cli_len);
     sum=n1+n2;
     printf("The sum is:%d",sum);
     sendto(sockfd,&sum,sizeof(sum),0,(struct sockaddr*)&cli_addr,cli_len);
     close(sockfd);
    }
   
