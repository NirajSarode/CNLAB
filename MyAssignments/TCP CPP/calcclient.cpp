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
	int sock = socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(8003);
	server.sin_addr.s_addr =inet_addr(SERVER_ADDRESS);
	
	connect(sock,(struct sockaddr *)&server,sizeof(server));


	int y=1;
	
	do{
		char ch[2];		
		cout<<"1. CALCULATOR"<<endl;
		cout<<"2. FILE TRANSFER"<<endl;
		cout<<"3. CHAT"<<endl;
		cin>>ch;
		send(sock,ch,strlen(ch),0);
		int choice = atoi(ch);
		bzero((char*)ch,sizeof(ch));

	switch(choice)
	{
		case 1:{
			int n;
			char a[20];
			char b[20];
			char c[20];
			char ans[20];
			bzero((char*)a,sizeof(a));
			bzero((char*)b,sizeof(b));
			bzero((char*)c,sizeof(c));
			bzero((char*)ans,sizeof(ans));
			while(1)
			{

				cout<<"Enter first number"<<endl;
				cin>>a;
				send(sock,a,strlen(a),0);
				bzero((char*)a,sizeof(a));


				cout<<"Enter second number"<<endl;
				cin>>b;
				send(sock,b,strlen(b),0);
				bzero((char*)b,sizeof(b));

				cout<<"Enter operator "<<endl;
				cin>>c;
				send(sock,c,20,0);
				bzero((char*)c,sizeof(c));


				recv(sock,ans,strlen(ans),0);

				cout<<"RESULt OF operation "<<ans<<endl;
				bzero((char*)ans,sizeof(ans));

			}

			
			break;
		}
		case 2:{
			long long int msg_len;
			char buffer[256];
			cout<<"Wating for server to send  filename.";
			char filename[100];
			bzero((char *)filename,sizeof(filename));
			msg_len=recv(sock,filename,100,0);
			cout<<"\nFilename:"<<filename;


			char *filebuff=new char[90000*80];

			bzero((char *)filebuff,sizeof(filebuff));
			msg_len=recv(sock,filebuff,90000*80,0);
			ofstream fout;
			fout.open(filename,ios::out|ios::binary);
				fout.write(filebuff,msg_len);
				fout.close();
				cout<<"File received";
			break;
		}
		case 3:
			//chat();
			break;
		default:
			cout<<"Invalid Choice !"<<endl;
	}



		cout<<"Do you want to continue ? (0/1)"<<endl;
		char cnt[2];		
		cin>>cnt;
		send(sock,cnt,strlen(cnt),0);
		y = atoi(cnt);
		bzero((char*)cnt,sizeof(cnt));

	}while(y==1);	
}
