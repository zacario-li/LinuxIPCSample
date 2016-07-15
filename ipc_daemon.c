/*
	Name: ipc_daemon.c
	Copyright: free
	Author: zacario
	Date: 15/07/16 11:22
	Description: ÉÐÎ´Íê³É 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>


#define LOGBUFSZ 256    
#define LOGFILE  "wsiod.log" 
#define NOFILE 65535

int init_daemon(void)
{
	pid_t pid;
	int i;
	int lfp;
	
	printf("Init daemon \n");
	
	if((pid = fork()) < 0)
	{
		printf("fork failed \n");
		return -1;
	}
	else if(pid != 0)
	{
		printf("pid is:%d \n",pid);
		exit(0);
	}
	
	setsid();
	printf("set sid done \n");
	
//	for(i = getdtablesize(); i>=0; --i){
//		close(i);
//	}
	
	umask(027);
	chdir("/home/lizhijian/test/ipc/");
	
	lfp = open("ipcd.lock",O_RDWR|O_CREAT,0640);
	if(lfp < 0)
	{
		return -1;
	}
	
	return 0;
}

int wsio_logit(char * func, char *msg, ...)
{
	va_list args;
	char prtbuf[LOGBUFSZ];
	int save_errno;
	struct tm *tm;
	time_t current_time;
	int fd_log;
	save_errno = errno;
	
	va_start(args, msg);
	
	(void)time(&current_time);           
	tm = localtime(&current_time);
	
	sprintf(prtbuf,"d/d d:d:d %s ", tm->tm_mon+1,tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, func);
	    
	vsprintf(prtbuf+strlen(prtbuf), msg, args);
	
	va_end(args);
	
	fd_log = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0664);
	write(fd_log, prtbuf, strlen(prtbuf));
	close(fd_log);
	errno = save_errno;
	
	return 0;
}

void sig_term(int signo)
{
	if(signo == SIGTERM) 
	{
		wsio_logit("", "wsiod stopped\n");
		exit(0);
	}
}

int main(void)
{
	printf("Start daemon \n");
	if(init_daemon() == -1){
		printf("can't fork self\n");
		exit(0);
	}
	printf("Start daemon Ok\n");
	
	wsio_logit("", "wsiod started\n");
	signal(SIGTERM, sig_term);

	while (1) 
	{
		printf("Start daemon while\n");
	// Do what you want here
	//¡­ ¡­
	}
	
	exit(0);
}
