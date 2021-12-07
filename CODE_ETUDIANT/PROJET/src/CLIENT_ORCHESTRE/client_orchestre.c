#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>

#include "myassert.h"

#include "client_orchestre.h"

/*** ---- FONCTIONS ---- ***/

// ---- ORCHESTRE ----

/*Création et initialisation de la structure*/
struct oC *initOrchestre(int w, int r,int s)
{
	struct oC *o = malloc(sizeof(struct oC));

	o->pipeOrchestreService = w;
	o->sem = s;
	return o;
}


// ---- SÉMAPHORES ----

/*Création d'un sémaphore et initialisation*/
int semCreation(int key, int initVal)
{
	int semClient = semCreator(key);
    semSetVal(semClient,initVal);

    return semClient;
}


// ---- TUBES ----

/*Création des tubes nommés*/
void linkOrchestreClient(char *pipe_c2o, char *pipe_o2c)
{
	myMkfifo(pipe_c2o,0600); //tube nommé client vers orchestre
    myMkfifo(pipe_o2c,0600); //tube nommé orchestre vers client
}

/*Fermeture des pipes*/
void closePipe(int r, int w)
{
	myClose(r); //partie lecture dans le tube
	myClose(w); //partie ecriture dans le tube
}


// ---- THREADS CLIENT ----

void myCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
	int test = pthread_create(thread, attr, start_routine, arg);
	myassert(test > -1, "ERROR : Thread isn't created !");
}

void myJoin(pthread_t thread, void **retval)
{
	int test = pthread_join(thread, retval);
	myassert(test > -1, "ERROR : Thread isn't join !");
}

/*Initialisation des thread*/
void preInitThread(int N, int nbThread, bool *tab, ThreadData *data)
{
	for (int i = 0; i < nbThread; i++)
    {
        data[i].thValue = i+2;
        data[i].value = N;
        data[i].res = &tab[i];
    }
}

/*Code des threads du client*/
void *codeThread(void *var)
{
	ThreadData *d = (ThreadData*) var;

    if ((d->value) % (d->thValue) == 0)
    {
        *d->res = false;
    }

    return NULL;
}