#ifndef CLIENT_ORCHESTRE_H
#define CLIENT_ORCHESTRE_H

// Ici toutes les communications entre l'orchestre et les clients :
// - le sémaphore pour que 2 clients ne conversent pas en même
//   temps avec l'orchestre
// - les deux tubes nommés pour la communication bidirectionnelle

/*** ---- INCLUDE ---- ***/

#include "tubesem.h"

#define REQUEST_STOP -1
#define REQUEST_AGREE 10
#define REQUEST_ERROR -10

/*Identifiant pour le deuxième paramètre de ftok*/
#define CLIENT_ORCHESTRE_ID 5

/*Nom des tubes entre le client et l'orchestre*/
#define CLIENT_ORCHESTRE "pipe_c2o"
#define ORCHESTRE_CLIENT "pipe_o2c"

/*** STRUCTURES ***/

//Structure du client et de l'orchestre 
struct cO
{
	//Semaphore
	int sem;
};


/*** ---- FONCTIONS ---- ***/


// ---- CLIENT_ORCHESTRE ----

/*Création et initialisation de la structure entre le client et l'orchestre*/
struct cO *initClientOrchestre(int w, int r,int s);


// ---- SÉMAPHORES ----

/*Création d'un sémaphore et initialisation*/
int semCreation(int key, int initVal);


// ---- TUBES ----

/*Création des tubes nommés*/
void linkClientOrchestre(char *pipe_c2o, char *pipe_o2c);

/*Fermeture des pipes*/
void closePipe(int r, int w);

#endif