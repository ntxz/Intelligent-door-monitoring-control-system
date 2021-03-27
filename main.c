#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <fcntl.h>
#include "convert.h"
#include "camera.h"
#define W 640
#define H 480
int main(int argc, char *argv[])
{
/////////////////////////////////////////////
	unsigned int index = 0;
	unsigned int width =W;
	unsigned int height =H;
	unsigned int size = 0;
	unsigned int isjpeg = 0;
	char *buf;
	char bufs[1024*1024*200] = {0};
	int fd = camera_init("/dev/video0",&width,&height,&size,&isjpeg);
	camera_start(fd);
	int c = 0;
	while(c<1){
		camera_dqbuf(fd,(void**)&buf,&size,&index);//*buf里为内容,size为大小			
		camera_eqbuf(fd,index);
		c++;
	}
	printf("%d\n",size);
	sprintf(bufs,"%s",buf);	
	camera_stop(fd);
	camera_exit(fd);

////////////////////////////////////////////
	return 0;
}
