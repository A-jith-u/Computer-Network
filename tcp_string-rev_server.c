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
    int sockfd,newfd;
    char buffer[size];
    char z[100]="Not pallindrome";
    char t[100]="Is pallindrome";
    struct sockaddr_in addr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
       perror("Error creating socket");
    
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;
    
    int b=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(b<0)
      perror("Error binding socket");
    if(listen(sockfd,3)<0)
       perror("Error listening");
    
    ssize_t byte;
    int sock_len=sizeof(addr);
    newfd=accept(sockfd,(struct sockaddr*)&addr,&sock_len);
    if(newfd<0)
      perror("Error accepting");
    byte=read(newfd,buffer,size);
    char string[100];
    strcpy(string,buffer);
    printf("The original message is:%s",string);
    int temp;
    while(byte>0)
        {
         buffer[byte]='\0';
         printf("\nThe message is:%s",buffer);
         break;
        }
         int len=strlen(buffer);
         for(int i=0;i<(len/2);i++)
            {
             temp=buffer[i];
             buffer[i]=buffer[len-i-1];
             buffer[len-i-1]=temp;
            }
         printf("\nThe reversed string is:%s",buffer);
         send(newfd,buffer,strlen(buffer),0);
   if(!strcmp(string,buffer)){
       write(newfd,t,strlen(t));
      }
      else{
            write(newfd,z,strlen(z));
           }    
   close(sockfd);
   close(newfd);
  }
       
