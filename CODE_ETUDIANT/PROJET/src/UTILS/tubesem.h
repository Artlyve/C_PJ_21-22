#ifndef _TUBESEM_H_
#define _TUBESEM_H_

/*** ---- INCLUDE ---- ***/
 
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>


/*** ---- FONCTIONS ---- ***/

//TUBES

int myOpen(const char *pathname, int flags);

void myRead(int fd, void *buf, size_t cmpt);

void myWrite(int fd, const void *buf, size_t cmpt);

void myClose(int fd);

int myMkfifo(const char *pathname, mode_t mode);

void myPipe(int fd[]);


//SÉMAPHORES

key_t getKey(const char *pathname, int proj_id);

int semCreator(key_t key);

int semGet(key_t key);

void semCtl(int semid, int semnum, int cmd);

void semSetVal(int semid, int val);

void semDestruct(int semid);

void takeSem(int semid);

void letSem(int semid);

void waitSem(int semid);

#endif