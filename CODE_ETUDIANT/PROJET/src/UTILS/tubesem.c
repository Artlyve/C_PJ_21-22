#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <fcntl.h>

#include "myassert.h"
#include "tubesem.h"

/*** ---- FONCTIONS ---- ***/

// ---- TUBES ---- //

/*Open*/
int myOpen(const char *pathname, int flags)
{
	int ret = open(pathname, flags);
	myassert(ret > -1, "ERROR myOpen");

	return ret;
}

/*Read*/
void myRead(int fd, void *buf, size_t cmpt)
{
	int test = (int) read(fd, buf, cmpt);
	myassert(test > -1, "ERROR myRead");
}

/*Write*/
void myWrite(int fd, const void *buf, size_t cmpt)
{
	int test = (int) write(fd, buf, cmpt);
	myassert(test > -1, "ERROR myWrite");
}

/*Close*/
void myClose(int fd)
{
	int test = close(fd);
	myassert(test > -1, "ERROR myClose");
}

/*Tube nommé*/
int myMkfifo(const char *pathname, mode_t mode)
{
	int ret = mkfifo(pathname, mode);
	myassert(ret > -1, "ERROR myMkfifo");
	
	return ret;
}

/*Tube anonyme*/
void myPipe(int fd[])
{
	int test = pipe(fd);
	myassert(test > -1, "ERROR myPipe");
}


// ---- SÉMAPHORES ---- //

/* Get Key*/
key_t getKey(const char *pathname, int proj_id)
{
	int key = ftok(pathname, proj_id);
	myassert(key > -1, "ERROR getKey");
	
	return key;
}

/*Semaphore*/
int semCreator(key_t key)
{
	int semid = semget(key, 1, IPC_CREAT | 0641);
	myassert(semid > -1, "ERROR semCreator");
	
	return semid;
}

/*Get Semaphore*/
int semGet(key_t key)
{
	int semid = semget(key, 1, 0);
	myassert(semid > -1, "ERROR semGet");
	
	return semid;
}

/*Control Semaphore*/
void semCtl(int semid, int semnum, int cmd)
{
	int test = semctl(semid, semnum, cmd);
	myassert(test > -1, "ERROR : semCtl()");
}

/*Set Value Semaphore*/
void semSetVal(int semid, int val){
	int test = semctl(semid, 0, SETVAL, val);
	myassert(test > -1,"ERROR semCtl");
}

/*Destruction Semaphore*/
void semDestruct(int semid)
{
	int test = semctl(semid, 0, IPC_RMID);
	myassert(test > -1, "ERROR semDestruct");
}

/*Réserve le Semaphore*/
void takeSem(int semid)
{
	struct sembuf op = {0, -1, 0};
	
	int test = semop(semid, &op, 1);
	myassert(test > -1, "ERROR takeSem");
}

/*Libère le Semaphore*/
void letSem(int semid)
{
	struct sembuf op = {0, 1, 0};
	
	int test = semop(semid, &op, 1);
	myassert(test > -1, "ERROR letSem");
}

/*Attend le Semaphore*/
void waitSem(int semid)
{
	struct sembuf op = {0, 0, 0};
	
	int test = semop(semid, &op, 1);
	myassert(test > -1, "ERROR waitSem");
}