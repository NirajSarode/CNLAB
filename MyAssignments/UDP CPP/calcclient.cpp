#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<fstream>
#define SERVER_ADDRESS "127.0.0.1"
using namespace std;

int main(){
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(8003);
	server.sin_addr.s_addr =inet_addr(SERVER_ADDRESS);
	char s[20] = "HELLO SERVER";
	
	int msg = sendto(sock,s,20,0,(struct sockaddr *)&server,sizeof(server));

	socklen_t ser=sizeof(server);

	long long int msg_len;
	char buffer[256];
	cout<<"Wating for server to send  filename.";
	char filename[100];
	bzero((char *)filename,sizeof(filename));
	msg_len=recvfrom(sock,filename,100,0,(struct sockaddr*)&server,&ser);
	cout<<"\nFilename:"<<filename;


	char *filebuff=new char[90000*80];

	bzero((char *)filebuff,sizeof(filebuff));
	msg_len=recvfrom(sock,filebuff,90000*80,0,(struct sockaddr*)&server,&ser);
	ofstream fout;
	fout.open(filename,ios::out|ios::binary);
		fout.write(filebuff,msg_len);
		fout.close();
		cout<<"File received";
}
