/*
	Name: shm_server.c
	Copyright: free
	Author: zacario
	Date: 20/07/16 11:09
	Description: Ô­ÀíÉÐÎ´Çå³þ¡£¡£¡£¡£¡£¡£ 
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 27

main()
{
    char c;
    int shmid1, shmid2;
    key_t key1, key2;
    char *shm, *shm1, *s;

    /* Naming shared memory segments */
    key1 = 5678;
    key2 = 8899;

    /* Created shared memory segments */
    if ((shmid1=shmget(key1,SHMSZ,IPC_CREAT|0666)) < 0){
        perror("shmget key1");
        exit(1);
    } // if shmget

    if ((shmid2=shmget(key2,SHMSZ,IPC_CREAT|0666)) < 0){
        perror("shmget key2");
        exit(1);
    } // if shmget

    /* Attach segment 1 to our data space */
    if ((shm=shmat(shmid1,NULL,0))==(char *)-1){
        perror("shmat");
        exit(1);
    } // if shmat

    /* Put somethings into the memory for the other process to read */
    s = shm;
    
    for (c='a';c<='z';c++)
        *s++ = c;
    *s = NULL;
    
    /* Wait until other process changes the first character of our memory to 
     * '*', indicating that it has read what we put there. */
    while (*shm != '*')
        sleep(1);

    /* Print the new contents of the segment */
    for (s=shm;*s!=NULL;s++)
        putchar(*s);
    putchar('\n');

    /* Attach segment 2 to our data space */
    if ((shm1=shmat(shmid2,NULL,0))==(char *)-1){
        perror("shmat");
        exit(1);
    } // if shmat

    /* Put somethings into the memory for the other process to read */
    s = shm1;
    
    for (c='A';c<='Z';c++)
        *s++ = c;
    *s = NULL;

    /* Change the first character of the first segment to $ to indicate that 
     * the client can read and change the second segment */
    *shm = '$';

    /* Wait until other process changes the first character of our memory to 
     * '*', indicating that it has read what we put there. */
    while (*shm1 != '*')
        sleep(1);

    /* Print the new contents of the segment */
    for (s=shm;*s!=NULL;s++)
        putchar(*s);
    putchar('\n');

    exit(0);
} // main
