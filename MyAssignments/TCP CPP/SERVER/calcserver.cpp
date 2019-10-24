#include<iostream>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fstream>

using namespace std;

int main(){
	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server,client;

	server.sin_family = AF_INET;
	server.sin_port = htons(8003);
	server.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sock,(struct sockaddr *)&server,sizeof(server))){
		cout<<"Bind Error"<<endl;
	}
	if(listen(sock,5)<0){
		cout<<"ERROR IN LISTEN"<<endl;	
	}
	socklen_t clen = sizeof(client);
	int newsock = accept(sock,(struct sockaddr *)&client,&clen);
	int y;
	
do{
	int choice;
	char ch[2];

	int  n = recv(newsock,ch,2,0);
	choice = atoi(ch);
	bzero((char *)ch,sizeof(ch));
	switch(choice)
	{
		case 1:{
				
			float a,b,ans1;
			char op[2],n1[20],n2[20];
			bzero((char*)op,sizeof(op));
			bzero((char*)n1,sizeof(n1));
			bzero((char*)n2,sizeof(n2));

			while(1){
				int  n = recv(newsock,n1,20,0);
				cout<<"1st number is "<<n1<<endl;
				a = atof(n1);
				bzero((char *)n1,sizeof(n1));

				int p = recv(newsock,n2,20,0);
				cout<<"2nd number is "<<n2<<endl;
				b = atof(n2);
				bzero((char *)n2,sizeof(n2));
				
				int o = recv(newsock,op,2,0);
				cout<<"Operator is "<<op<<endl;
			
				switch(op[0]){
					case '+':{
						char ans[20];
						ans1 = a+b;
						cout<<"Answer is : "<<ans1<<endl;
						bzero((char *)ans,sizeof(ans));
						sprintf(ans,"%f",ans1);
						send(newsock,ans,strlen(ans),0);
						break;
					}
					case '-':{
						char ans[20];
						ans1 = a-b;
						cout<<"Answer is : "<<ans1<<endl;
						bzero((char *)ans,sizeof(ans));
						sprintf(ans,"%f",ans1);
						send(newsock,ans,strlen(ans),0);
						break;
					}
					case '*':{
						char ans[20];
						ans1 = a*b;
						cout<<"Answer is : "<<ans1<<endl;
						bzero((char *)ans,sizeof(ans));
						sprintf(ans,"%f",ans1);
						send(newsock,ans,strlen(ans),0);
						break;
					}
					case '/':{
						char ans[20];
						ans1 = a/b;
						cout<<"Answer is : "<<ans1<<endl;
						bzero((char *)ans,sizeof(ans));
						sprintf(ans,"%f",ans1);
						send(newsock,ans,strlen(ans),0);
						break;
					}
				}
				bzero((char *)op,sizeof(op));
			}
			break;
		}
		case 2:{
			long long int msglen;
			cout<<"Enter Filename"<<endl;
			char filename[100];
			cin>>filename;
			fstream fout;
			msglen = send(newsock,filename,100,0);
			fout.open(filename,ios::in|ios::out|ios::binary);
				fout.seekg(0,ios::end);
				long long int filesize = fout.tellg();
				char *filebuff = new char[filesize];
				fout.seekg(0,ios::beg);
				fout.read(filebuff,filesize);
			msglen = send(newsock,filebuff,filesize,0);
				cout<<"Transmission Successful";
			fout.close();
			break;
		}
		case 3:
			//chat();
			break;
		default:
			cout<<"Invalid Choice !"<<endl;
	}

	char cnt[2];

	int  n1 = recv(newsock,cnt,2,0);
	y = atoi(cnt);
	bzero((char *)cnt,sizeof(cnt));

}while(y==1);


	return 0;
}
