#ifndef CLIENT_ORCHESTRE_H
#define CLIENT_ORCHESTRE_H

// Ici toutes les communications entre l'orchestre et les clients :
// - le sémaphore pour que 2 clients ne conversent pas en même
//   temps avec l'orchestre
// - les deux tubes nommés pour la communication bidirectionnelle

/*** ---- INCLUDE ---- ***/

#include "tubesem.h"


/*Identifiant pour le deuxième paramètre de ftok*/
#define CLIENT_ORCHESTRE_ID 5

/*Nom des tubes entre le client et l'orchestre*/
#define CLIENT_ORCHESTRE "pipe_c2o"
#define ORCHESTRE_CLIENT "pipe_o2c"

/*** STRUCTURES ***/


//Structure de l'orchestre
struct orc
{
	//tubes
	int pipeOrchestreService;

	//Semaphore
	int sem;
};


//Structure pour les thread
typedef struct
{
    int thValue;
    int value;
    bool * res;
}ThreadData;


/*** ---- FONCTIONS ---- ***/


// ---- Orchestre ----

/*Création et initialisation de la structure d'orchestre*/
struct orc *initOrchestre(int w, int r,int s);


// ---- SÉMAPHORES ----

/*Création d'un sémaphore et initialisation*/
int semCreation(int key, int initVal);


// ---- TUBES ----

/*Création des tubes nommés*/
void linkOrchestreClient(char *pipe_c2o, char *pipe_o2c);

/*Fermeture des pipes*/
void closePipe(int r, int w);


// ---- THREADS CLIENT ----

void myCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
void myJoin(pthread_t thread, void **retval);

/*Initialisation des thread*/
void preInitThread(int N, int nbThread, bool *tab, ThreadData *data);

/*Code des threads du client*/
void *codeThread(void *var);

#endif