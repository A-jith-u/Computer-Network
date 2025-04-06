#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define port 9001
#define size 1024

int main()
   {
    int sockfd;
    char buffer[size];
    struct sockaddr_in addr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
       perror("Error creating socket");
    
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;
    
    int c=connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(c<0)
      perror("Error connecting");
    printf("Enter the message:");
    scanf("%s",buffer);
    send(sockfd,buffer,sizeof(buffer),0);
    ssize_t byte=read(sockfd,buffer,size);
    printf("The recieved message is:%s\n",buffer);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,size);
    
    close(sockfd);
   }
