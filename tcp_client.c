#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
/*包含头文件。*/
#define PORT 5678
/*定义远程端口。*/
#define REMOTE_IP "192.168.0.104" 
/*定义远程 IP。*/
int main(int argc,char *argv[])
{
int s ;
struct sockaddr_in addr ;
char mybuffer[256]; /*定义相关变量。*/
if( (s=socket(AF_INET,SOCK_STREAM,0))<0 )
{
perror("socket");
exit(1);
}
else
{
printf("socket created .\n");
printf("socked id: %d \n",s);
} /*新建一个 socket。*/
bzero(&addr,sizeof(addr));
addr.sin_family =AF_INET;
addr.sin_port=htons(PORT);
addr.sin_addr.s_addr=inet_addr(REMOTE_IP); /*设置 addr。*/
if(connect(s,&addr,sizeof(addr))<0)
{
perror("connect");exit(1);
}
else
{
printf("connected ok!\n");
printf("remote ip:%s\n",REMOTE_IP);
printf("remote port:%d\n",PORT);
}
recv(s ,mybuffer,sizeof(mybuffer),0);
printf("%s\n",mybuffer);
/*接收服务器发送的信息。*/
/*输出信息。*/
while(1)
/*进入一个循环。*/
{
bzero(mybuffer,sizeof(mybuffer));
/*清空 mybuffer 字符串。*/
read(STDIN_FILENO,mybuffer,sizeof(mybuffer)); /*读取输入。*/
if(send(s,mybuffer,sizeof(mybuffer),0)<0)
{
perror("send");
exit(1);
}
else
{
bzero(mybuffer,sizeof(mybuffer));
recv(s ,mybuffer,sizeof(mybuffer),0);
printf("received:%s\n",mybuffer);
}
/*发送信息。*/
/*错误处理。*/
/*清空 mybuffer 内存。*/
/*接收信息。*/
/*输出信息。*/
}
}
