#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define port 9001
#define size 1024

int main()
    {
     int sockfd;
     char buffer[size];
     struct sockaddr_in cli_addr;
     //socklen_t cli_len=sizeof(cli_addr);
     sockfd=socket(AF_INET,SOCK_DGRAM,0);
     if(sockfd<0)
        perror("Error creating socket");
     memset(&cli_addr,0,sizeof(cli_addr));
     cli_addr.sin_family=AF_INET;
     cli_addr.sin_port=htons(port);
     cli_addr.sin_addr.s_addr=INADDR_ANY;
     
     while(1)
          {
           memset(buffer,0,size);
           printf("Enter the message:");
           fgets(buffer,size,stdin);
           ssize_t s=sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
           if(s<0)
             perror("Error sending message");
           ssize_t r=recvfrom(sockfd,buffer,size,0,NULL,NULL);
           if(r<0)
              perror("Error recieving message");
              break;
           printf("Echo message:%s",buffer);
          }
    close(sockfd);
   }
     
