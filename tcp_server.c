#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h> /*包含头文件。*/
#define PORT 5678
#define MAX 10 /*定义端口号。*/
/*最多的连接数。*/
main()
{
int sockfd,newsockfd,is_connected[MAX],fd;
/*定义相关的变量。*/
struct sockaddr_in addr;
int addr_len = sizeof(struct sockaddr_in);
fd_set myreadfds;
char msgbuffer[256];
char msg[] ="This is the message from server.Connected.\n";
if ((sockfd = socket(AF_INET,SOCK_STREAM,0))<0) /*建立一个 socket。*/
{
perror("socket");
exit(1);
}
else
{
printf("socket created .\n");
/*socket 建立成功,输出提示。*/
printf("socked id: %d \n",sockfd);
}
bzero(&addr,sizeof(addr));
addr.sin_family =AF_INET;
addr.sin_port = htons(PORT);
addr.sin_addr.s_addr = htonl(INADDR_ANY); /*清空 addr 所在的内存。*/
if(bind(sockfd,&addr,sizeof(addr))<0)
{
perror("connect");
exit(1);
}
else
{
printf("connected.\n");
printf("local port:%d\n",PORT)
;
} /*绑定端口。*/
if(listen(sockfd,3)<0)
{
perror("listen");
exit(1);
}
else
{
printf("listenning......\n");
} /*开始监听。*/
for(fd=0;fd<MAX;fd++)
{
is_connected[fd]=0;
}
while(1)
{
FD_ZERO(&myreadfds);
FD_SET(sockfd,&myreadfds);
for(fd=0;fd<MAX;fd++)
{
if(is_connected[fd])
/*设置所有的标记为 0。*/
/*进入一个循环,处理所有的连接。*/
/*清空一个标志。*/
/*设置标志。*/
/*判断有没有连接。*/
{
FD_SET(fd,&myreadfds);
/*设置标志。*/
}
}
if(!select(MAX,&myreadfds,NULL,NULL,NULL))
/*如果到达了最大的连接数则进
入下次循环。*/
{
continue;
}
for(fd=0;fd<MAX;fd++)
/*进入一个循环。*/
{
if(FD_ISSET(fd,&myreadfds))
/*判断标志。*/
{
if(sockfd==fd)
/*如果新建的 socket 与 fd 相同。*/
{
if((newsockfd = accept (sockfd,&addr,&addr_len))<0)
/*接受一个连接,新建一个 socket。*/
{
perror("accept");
}
write(newsockfd,msg,sizeof(msg));
/*给客户端发送一段信息。*/
is_connected[newsockfd] =1;
/*设置标志。*/
printf("cnnect from %s\n",inet_ntoa(addr.sin_addr));
/*输出客户端的 IP。*/
}
else
{
bzero(msgbuffer,sizeof(msgbuffer));
/*清空字符串。*/
if(read(fd,msgbuffer,sizeof(msgbuffer))<=0)
/*读取结果。*/
{
printf("connect closed.\n");
/*输出连接关闭。*/
is_connected[fd]=0;
/*设置标志。*/
close(fd);
/*关闭一个 socket。*/
}
else
{
write(fd,msgbuffer,sizeof(msgbuffer));
/*发送接收到的信息。*/
printf("message:%s \n",msgbuffer);
/*输出接收到的信息。*/
}
}
}
}
}
}
