#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>

#include "myassert.h"

#include "client_orchestre.h"

/*** ---- FONCTIONS ---- ***/

// ---- CLIENT_ORCHESTRE ----

/*Création et initialisation de la structure entre le client et l'orchestre*/
struct cO *initClientOrchestre(int w, int r,int s)
{
	struct cO *co = malloc(sizeof(struct cO));
	
	co->sem = s;
	return co;
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
void linkClientOrchestre(char *pipe_c2o, char *pipe_o2c)
{
	myMkfifo(pipe_c2o,0641); //tube nommé client vers orchestre
    myMkfifo(pipe_o2c,0641); //tube nommé orchestre vers client
}

/*Fermeture des pipes*/
void closePipe(int r, int w)
{
	myClose(r); //partie lecture dans le tube
	myClose(w); //partie ecriture dans le tube
}