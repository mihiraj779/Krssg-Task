#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>
using namespace std;

#define space cout<<"             ";
class traffic_light{
    public:
        int state=1;
        void trafficlight(int* arr,int n);
        void config1(int* arr,int n,int i);//defines state of straight and right direction from the same lane
        void config2(int* arr,int n,int i);//defines state of right direction from two opposite lane
        void config3(int* arr,int n,int i);//defines straight path from opposite lane
        void config4(int* arr,int n,int i);//defines straight path from one lane and right path from other lane
        int maxthree(int a,int b,int c);

};
void traffic_light::config1(int* arr,int n,int i)
{
    switch(i)
    {
    case 0:
    if(state!=1){
    cout<<"A- go straight, go right"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- off\n";
    state=1;
    break;
    }
    case 2:
    if(state!=5){
    cout<<"A- off"<<endl;
    space;
    cout<<"B- go straight, go right\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- off\n";
    state=5;
    break;
    }
    case 4:
    if(state!=8){
    cout<<"A- off"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- go straight, go right\n";
    space;
    cout<<"D- off\n";
    state=8;
    break;
    }
    case 6:
    if(state!=12){
    cout<<"A- off"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- go straight, go right\n";
    state=12;
    break;
    }
    }
    if(arr[i]>0)
    arr[i]-=1;
    if(arr[i+1]>0)
    arr[i+1]-=1;
}
void traffic_light::config2(int* arr,int n,int i)
{
    if(i==1&&state!=4)
    {
    cout<<"A- go right"<<endl;
    space;
    cout<<"B- go right\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- off\n";
    state=4;
    }
    else if(state!=11)
    {
    cout<<"A- off"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- go right\n";
    space;
    cout<<"D- go right\n";
    state=11;
    }
    if(arr[i]>0)
    arr[i]-=1;
    if(arr[i+2]>0)
    arr[i+2]-=1;
}
void traffic_light::config3(int* arr,int n,int i)
{
    if(i==0&&state!=2)
    {
    cout<<"A- go straight"<<endl;
    space;
    cout<<"B- go straight\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- off\n";
    state=2;
    }
    else if(i==4&&state!=9)
    {
    cout<<"A- off"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- go straight\n";
    space;
    cout<<"D- go straight\n";
    state=9;
    }
    if(arr[i]>0)
    arr[i]-=1;
    if(arr[i+2]>0)
    arr[i+2]-=1;
}
void traffic_light::config4(int* arr,int n,int i)
{
    switch(i)
    {
    case 0:
    if(state!=3){
    cout<<"A- go straight"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- go right\n";
    state=3;
    break;
    }
    case 2:
    if(state!=6){
    cout<<"A- off"<<endl;
    space;
    cout<<"B- go straight\n";
    space;
    cout<<"C- go right\n";
    space;
    cout<<"D- off\n";
    state=6;
    break;
    }
    case 4:
    if(state!=5){
    cout<<"A-go right"<<endl;
    space;
    cout<<"B- off\n";
    space;
    cout<<"C- go straight\n";
    space;
    cout<<"D- off\n";
    state=5;
    break;
    }
    case 6:
    if(state!=7){
    cout<<"A- off"<<endl;
    space;
    cout<<"B- go right\n";
    space;
    cout<<"C- off\n";
    space;
    cout<<"D- go straight\n";
    state=7;
    break;}
    }
    if(i==0 || i==2)
    {
        if(arr[i]>0)
        arr[i]-=1;
        if(arr[7-i]>0)
        arr[7-i]-=1;
    }
    else
    {
        if(arr[i]>0)
        arr[i]-=1;
        if(arr[i-3]>0)
        arr[i-3]-=1;
    }
}

int traffic_light::maxthree(int a,int b,int c)
{
    int max=a,i=1;
    if(b>max)
    {
        max=b;
        i=2;
    }
    if(c>max)
    {
        max=c;
        i=3;
    }
    return i;
}

void traffic_light::trafficlight(int* arr,int n)
{
    int max=INT_MIN,index=-1;

    for(int i=0;i<n;i++)
    if(arr[i]>max)
    {
        max=arr[i];
        index=i;
    }
    int index1;
   switch(index)
    {
        case 0:
        index1=maxthree(arr[1],arr[2],arr[7]);
        if(index1==1)
        config1(arr,8,0);
        else if(index1==2)
        config3(arr,8,0);
        else
        config4(arr,8,0);
        break;
        case 1:
        index1=maxthree(arr[0],arr[3],arr[4]);
        if(index1==1)
        config1(arr,8,0);
        else if(index1==2)
        config2(arr,8,1);
        else
        config4(arr,8,4);
        break;
        case 2:
        index1=maxthree(arr[0],arr[3],arr[5]);
        if(index1==1)
        config3(arr,8,0);
        else if(index1==2)
        config1(arr,8,2);
        else
        config4(arr,8,2);
        break;
        case 3:
        index1=maxthree(arr[1],arr[2],arr[6]);
        if(index1==1)
        config2(arr,8,1);
        else if(index1==2)
        config1(arr,8,2);
        else
        config4(arr,8,3);
        break;
        case 4:
        index1=maxthree(arr[1],arr[5],arr[6]);
        if(index1==1)
        config4(arr,8,4);
        else if(index1==2)
        config1(arr,8,4);
        else
        config3(arr,8,4);
        break;
        case 5:
        index1=maxthree(arr[2],arr[4],arr[7]);
        if(index1==1)
        config4(arr,8,2);
        else if(index1==2)
        config1(arr,8,4);
        else
        config2(arr,8,5);
        break;
        case 6:
        index1=maxthree(arr[3],arr[4],arr[7]);
        if(index1==1)
        config4(arr,8,6);
        else if(index1==2)
        config3(arr,8,4);
        else
        config1(arr,8,6);
        break;
        case 7:
        index1=maxthree(arr[0],arr[5],arr[6]);
        if(index1==1)
        config4(arr,8,0);
        else if(index1==2)
        config2(arr,8,5);
        else
        config1(arr,8,6);
        break;
    }
}
 
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[1024];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        herror("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              herror("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          herror("ERROR on accept");
          else{
              cout<<"======Server======== \n";
          }

          
     int t;
    //cout<<"Enter no. of test lines: ";
    //cin>>t;
    write(newsockfd,"Enter no. of test lines: ",strlen("Enter no. of test lines: "));
    cout<<"Enter no. of test lines:";
    read(newsockfd,&t,sizeof(int));
    cout<<t<<endl;
    int arr[8],arg[8];

    for(int i=0;i<8;i++)
    arr[i]=0;
    traffic_light obj;

    for(int i=1;i>0;i++)
    {
        int a;
        if(i<=t)
        {
            cout<<"Input line "<<i<<": ";
            for(int i=0;i<8;i++)
            {
                //cin>>a;
                read(newsockfd,&a,sizeof(int));
                arr[i]+=a;
            }
        }
        for(int i=0;i<8;i++)
            arg[i]=arr[i];
        cout<<"Time step "<<i<<":" ;
        obj.trafficlight(arr,8);

        space;
        cout<<"Intial queue-";
        for(int i=0;i<8;i++)
        cout<<arg[i]<<" ";

        cout<<endl;
        space;
        cout<<"Final queue-";
        for(int i=0;i<8;i++)
        cout<<arr[i]<<" ";

        int c=0;
        for(int i=0;i<8;i++)
            if(arr[i]>0)
            c++;
        if(c==0)
            break;
        cout<<endl;
    }     

 

close(newsockfd);
close(sockfd);
return 0;
     
}
