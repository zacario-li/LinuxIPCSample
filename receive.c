/*
	Name: receive.c
	Copyright: free
	Author: zacario
	Date: 15/07/16 11:22
	Description: 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*������Ϣ�շ��Ľṹ��--my_msg_type����Ϣ���ͣ�some_text����Ϣ����*/
struct my_msg_st
{
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main()
{
	int running = 1;//�������б�ʶ��
	int msgid; //��Ϣ���б�ʶ��
	struct my_msg_st some_data; 
	long int msg_to_receive = 0;//������Ϣ������--0��ʾmsgid�����ϵĵ�һ����Ϣ
	key_t msgKey = -1;
	
	
	
	/*������Ϣ����*/
	msgKey = ftok("/tmp",1);
	msgid = msgget(msgKey, 0666 | IPC_CREAT);
	
	if (msgid == -1) 
	{
		fprintf(stderr, "msgget failed with error: %d/n", errno);
		exit(EXIT_FAILURE);
	}
	
	
	
	/*������Ϣ*/
	while(running) 
	{
		sleep(2);
		if (msgrcv(msgid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) 
		{
			fprintf(stderr, "msgrcv failed with error: %d/n", errno);
			exit(EXIT_FAILURE);
		}
		
		printf("You wrote: %s", some_data.some_text);
		
		if (strncmp(some_data.some_text, "end", 3) == 0) 
		{
			running = 0;
		}
	}
	
	
	
	/*ɾ����Ϣ����*/
	if (msgctl(msgid, IPC_RMID, 0) == -1) 
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed/n");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}
