/*
	Name: shm_client.c
	Copyright: free
	Author: zacario
	Date: 20/07/16 11:10
	Description: Ô­ÀíÉÐÎ´Çå³þ¡£¡£¡£¡£¡£¡£ 
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 27

main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    /* Get segment named 5678, created by the server */
    key = 5678;

    /* Locate segment */
    if ((shmid=shmget(key,SHMSZ,0666))<0){
        perror("shmget");
        exit(1);
    } // if shmget

    /* Attach segment to our data space */
    if ((shm=shmat(shmid,NULL,0))==(char *)-1){
        perror("shmat");
        exit(1);
    } // if shmat

    /* Read what the server put in the memory */
    for (s=shm;*s!=NULL;s++)
        putchar(*s);
    putchar('\n');

    /* Finally, change the first character of the segment to '*', 
     * indicating we have read the segment */
    *shm = '*';

    /* Wait until other process changes the first character of our memory to 
     * '$', indicating that it has read what we put there. */
    while (*shm != '$')
        sleep(1);

    /* Get segment named 8899, created by the server */
    key = 8899;

    /* Locate segment */
    if ((shmid=shmget(key,SHMSZ,0666))<0){
        perror("shmget");
        exit(1);
    } // if shmget

    /* Attach segment to our data space */
    if ((shm=shmat(shmid,NULL,0))==(char *)-1){
        perror("shmat");
        exit(1);
    } // if shmat

    /* Read what the server put in the memory */
    for (s=shm;*s!=NULL;s++)
        putchar(*s);
    putchar('\n');

    /* Finally, change the first character of the segment to '*', 
     * indicating we have read the segment */
    *shm = '*';

    fprintf(stderr,"Changed the second string"); 
    exit(0);
} // main
