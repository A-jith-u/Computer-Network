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
     struct sockaddr_in serv_addr,cli_addr;
     socklen_t cli_len=sizeof(cli_addr);
     sockfd=socket(AF_INET,SOCK_DGRAM,0);
     if(sockfd<0)
        perror("Error creating socket");
     memset(&serv_addr,0,sizeof(serv_addr));
     serv_addr.sin_family=AF_INET;
     serv_addr.sin_port=htons(port);
     serv_addr.sin_addr.s_addr=INADDR_ANY;
     
     int b=bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
     if(b<0)
       perror("Error binding socket");
     while(1)
          {
           memset(buffer,0,size);
           ssize_t r=recvfrom(sockfd,buffer,size,0,(struct sockaddr*)&cli_addr,&cli_len);
           if(r<0)
              perror("Error receiving message");
           printf("The recieved message is:%s",buffer);
           r=sendto(sockfd,buffer,r,0,(struct sockaddr*)&cli_addr,cli_len);
           if(r<0)
              perror("Error sending message");
           }
     close(sockfd);
    }
