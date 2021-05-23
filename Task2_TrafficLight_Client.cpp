#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>
#include<bits/stdc++.h>
using namespace std;

 
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
 
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int t;
 
    char buffer[1024];
    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    cout<<"========Client========== \n";
    
    read(sockfd,buffer,1024);
    printf("%s",buffer);
    cin>>t;
    write(sockfd,&t,sizeof(int));   
    for(int i=1;i>0;i++)
    {
        int a;
        if(i<=t)
        {
            cout<<"Input line "<<i<<": ";
            for(int i=0;i<8;i++)
            {
                cin>>a;
                write(sockfd,&a,sizeof(int));
            }
        } 
    }

    close(sockfd);
    return 0;
}
 



