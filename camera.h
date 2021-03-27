#ifndef __CAM_H__
#define	__CAM_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

//#include "convert.h"
#define CAMERA_USB "/dev/video0"
#define JPG_MAX_SIZE	(1024 * 1024 - sizeof (unsigned int))
#define SIZE 16

#define W 400
#define H 280


struct jpg_buf_t {
	char jpg_buf[JPG_MAX_SIZE];
	unsigned int jpg_size;
};
extern struct jpg_buf_t *jpg;
extern pthread_mutex_t cam_mutex;

int canera_init(char *devpath, unsigned int *width, unsigned int *height, unsigned int *size, unsigned int *ismjpeg);
int camera_start(int fd);
int camera_dqbuf(int fd, void **buf, unsigned int *size, unsigned int *index);
int camera_eqbuf(int fd, unsigned int index);
int camera_stop(int fd);
int camera_exit(int fd);
int camera_on();
#endif
