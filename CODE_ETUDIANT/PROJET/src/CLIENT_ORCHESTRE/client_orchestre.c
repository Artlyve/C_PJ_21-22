#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>

#include "myassert.h"

#include "client_orchestre.h"

/*** ---- FONCTIONS ---- ***/

// ---- SÉMAPHORES ----

/*Création d'un sémaphore et initialisation*/
int semCreationCO(int key, int initVal)
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