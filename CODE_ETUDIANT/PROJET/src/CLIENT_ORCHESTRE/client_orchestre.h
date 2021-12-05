#ifndef CLIENT_ORCHESTRE_H
#define CLIENT_ORCHESTRE_H

// Ici toutes les communications entre l'orchestre et les clients :
// - le sémaphore pour que 2 clients ne conversent pas en même
//   temps avec l'orchestre
// - les deux tubes nommés pour la communication bidirectionnelle


/*** STRUCTURES ***/


//Structure de l'orchestre
struct orc
{
	//tubes
	int pipeOrchestreService;
	int pipeServiceOrchestre;

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


// === SÉMAPHORES ===

/*Création d'un sémaphore et initialisation*/
int semCreation(int key, int initVal);


// === TUBES ===

/*Création des tubes nommés*/
void linkMasterClient(char *tubeCM, char *tubeMC);

/*Fermeture des pipes*/
void closePipe(int r, int w);

/*Initialisation des thread*/
void preInitThread(int N, int nbThread, bool *tab, ThreadData *data);

/*Code des threads du client*/
void *codeThread(void *var);

#endif
