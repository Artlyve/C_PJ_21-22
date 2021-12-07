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
void createFirstService(int pipeOrchestreService)
{
    
    //ordre des arguments : 
    //    - numéro du service
    //    - clé du sémaphore
    //    - "file descriptor du tube anonyme" orchestre vers service
    //    - tube nommé de client vers service
    //    - tube nommé de service vers client
    int numService = 0;
    int keySem = numService + 1;
    char * c1 = intToString(pipeOrchestreService);
    char * arguments[5] = { 
        numService,
        keySem,
        c1,
        pipe_c2s_0,
        pipe_s2c_0};
        
    int son = fork();
    
    //Fils créé ?
    if (son == -1) {
       perror("createFirstWorker");
       exit(EXIT_FAILURE);
    }
    
    if(son == 0){
        execv("service",arguments);
    }
    free(c1);
}