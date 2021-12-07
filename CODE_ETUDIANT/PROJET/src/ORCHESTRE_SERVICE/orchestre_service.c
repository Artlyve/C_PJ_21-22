#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>

#include "myassert.h"

#include "myassert.h"

#include "orchestre_service.h"


/*** ---- FONCTIONS ---- ***/

// ---- ORCHESTRE_SERVICE ----

/*Création et initialisation de la structure entre l'orchestre et le service*/
struct oS *initOrchestreService(int w, int r,int s)
{
	struct oS *os = malloc(sizeof(struct oS));

	os->pipeOrchestreService = w;
	os->sem = s;
	return os;
}

// ---- SÉMAPHORES ----

/*Création d'un sémaphore et initialisation*/
int semCreation(int key, int initVal)
{
	int semClient = semCreator(key);
    semSetVal(semClient,initVal);

    return semClient;
}

// À REMODIFIER ...
void createFirstWorker(int pipeMasterWorker, int pipeWorkerMaster){
	
	//ordre des arguments : 
	//  - nomExec
	//	- primeNumber
	//	- tube masterWorker
	//	- tube workerMaster
	char * c1 = intToString(pipeMasterWorker);
	char * c2 = intToString(pipeWorkerMaster);
	char * arguments[5] = { 
		"worker",
		"2",
		c1,
		c2,
		NULL};
		
	int son = fork();
	
	//Fils créé ?
	if (son == -1) {
	   perror("createFirstWorker");
	   exit(EXIT_FAILURE);
	}
	
	if(son == 0){
		execv("worker",arguments);
	}
	free(c1);
	free(c2);
}