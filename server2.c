#include<strings.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <fcntl.h>
#include "camera.h"
#define W 400
#define H 280


int main(int argc,char *argv[])
{
/////////////////////////////////////////////
	unsigned int index = 0;
	unsigned int width =W;
	unsigned int height =H;
	unsigned int size = 0;
	unsigned int isjpeg = 0;
	char *buf;
	char bufs[300*1024] = {0};
	int fd = camera_init("/dev/video0",&width,&height,&size,&isjpeg);
	camera_start(fd);
	int c = 0;


	//memcpy(bufs+5,bufs,sizeof(bufs));	strcpy(bufs,buf);

	//sprintf(bufs,"%s",buf);	

////////////////////////////////////////////














	/*if(argc != 2)
	{
		printf("Usage: %s <pic_file1>\n",argv[0]);
		return -1;
	}*/
		/*打开图片*/
	/*int fd2 = open(argv[1],O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}*/




	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("socket error\n");
		return -1;
	}
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(6666);
	seraddr.sin_addr.s_addr = inet_addr("0.0.0.0");	   //自动获取本机IP


	
	int ret = bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(ret == -1)
	{
		printf("bind error\n");
		return -1;
	}


	
	if(-1 == listen(sockfd,5))  // 5代表可同时监听的个数
	{
		printf("listen failed\n");
		return -1;
	}
	printf("listen--------\n");

	




	int connfd = accept(sockfd, NULL, NULL);
	if(connfd == -1)
	{
		printf("accept failed\n");
		return -1;
	}
	printf("accept success\n");

	char char_buf[32] = {0};

	//char send_buf[300*1024] = {0};


	/* 获取图片大小 */

	char pic_buf[32] = {0};




 

	/*数据处理*/
	while(1)
	{
		memset(char_buf, 0, sizeof(char_buf));
		if(0 == read(connfd, char_buf, sizeof(char_buf)))
		{
			printf("client quit\n");
			break;
		}
		if(strcmp(char_buf, "PIC") == 0)
		{
			printf("pass success!\n");

		
			/*int ret2 = read(fd2,send_buf,sizeof(send_buf));
			printf("%d\n",ret2);	*/	
			while(1){
			camera_dqbuf(fd,(void**)&buf,&size,&index);//*buf里为内容,size为大小
			//printf("%d\n",size);
			sprintf(pic_buf,"%d",size);
			write(connfd, pic_buf, sizeof(pic_buf));
			memcpy(bufs, buf, size);
			write(connfd,bufs,size);
			camera_eqbuf(fd,index);			
			}		
		}
		else
		{
			write(connfd, "error", 5);
		}
	}

	camera_stop(fd);
	camera_exit(fd);


	close(sockfd);
	close(connfd);

	return 0;
}


