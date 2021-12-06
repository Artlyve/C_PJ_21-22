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
	myassert(ret > -1, "ERROR : The file didn't open");

	return ret;
}

/*Read*/
void myRead(int fd, void *buf, size_t cmpt)
{
	int test = (int) read(fd, buf, count);
	myassert(test > -1, "ERROR : No reading in the file");
}

/*Write*/
void myWrite(int fd, const void *buf, size_t cmpt)
{
	int test = (int) write(fd, buf, count);
	myassert(test > -1, "ERROR : No writing in the file");
}

/*Close*/
void myClose(int fd)
{
	int test = close(fd);
	myassert(test > -1, "ERROR : The file didn't close");
}

/*Tube nommé*/
int myMkfifo(const char *pathname, mode_t mode)
{
	int ret = mkfifo(pathname, mode);
	myassert(ret > -1, "ERROR : Named pipe isnt created");
	
	return ret;
}

/*Tube anonyme*/
void myPipe(int fd[])
{
	int test = pipe(fd);
	myassert(test > -1, "ERROR : Anonymous pipe isnt created");
}


// ---- SÉMAPHORES ---- //

/* Get Key*/
key_t getKey(const char *pathname, int proj_id)
{
	int key = ftok(pathname, proj_id);
	myassert(key > -1, "ERROR : Issue with the creation of the key");
	
	return key;
}

/*Semaphore*/
int semCreator(key_t key)
{
	int semid = semget(key, 1, IPC_CREAT | 0641);
	myassert(semid > -1, "ERROR : Issue when trying to create the semaphore");
	
	return semid;
}

/*Get Semaphore*/
int semGet(key_t key)
{
	int semid = semget(key, 1, 0);
	myassert(semid > -1, "ERROR : Issue with semGet");
	
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
	myassert(test > -1,"ERROR : Issue when trying to set the value of the semaphore");
}

/*Destruction Semaphore*/
void semDestruct(int semid)
{
	int test = semctl(semid, 0, IPC_RMID);
	myassert(test > -1, "ERROR : Issue with the destruction of the semaphore");
}