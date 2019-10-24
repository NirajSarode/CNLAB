#include<iostream>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fstream>

using namespace std;

int main(){
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server,client;

	server.sin_family = AF_INET;
	server.sin_port = htons(8003);
	server.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sock,(struct sockaddr *)&server,sizeof(server))){
		cout<<"Bind Error"<<endl;
	}
	
	char buffer[100];
	bzero((char*)buffer,sizeof(buffer));
	
	socklen_t clen = sizeof(client);
	int msg = recvfrom(sock,buffer,100,0,(struct sockaddr *)&client,&clen);
	long long int msglen;
	cout<<"Enter Filename"<<endl;
	char filename[100];
	cin>>filename;
	fstream fout;
	msglen = sendto(sock,filename,100,0,(struct sockaddr *)&client,sizeof(client));
	fout.open(filename,ios::in|ios::out|ios::binary);
		fout.seekg(0,ios::end);
		long long int filesize = fout.tellg();
		char *filebuff = new char[filesize];
		fout.seekg(0,ios::beg);
		fout.read(filebuff,filesize);
	msglen = sendto(sock,filebuff,filesize,0,(struct sockaddr*)&client,sizeof(client));
		cout<<"Transmission Successful";
	fout.close();
	return 0;
}
