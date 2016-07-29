/*
	Name: semaphore_B.c
	Copyright: free
	Author: zacario
	Date: 25/07/16 11:29
	Description: 
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main(){
	int res = -1;
	key_t sem_key = ftok("/tmp",1); // 获取key 
	printf("sem_key :%d \n",sem_key);
	
	res = semget(sem_key,1,IPC_CREAT);	//创建sem 
	if(-1 == res){
		printf("semget error\n");
	}
	return 1;
}

