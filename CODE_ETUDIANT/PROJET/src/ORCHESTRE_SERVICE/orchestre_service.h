#ifndef ORCHESTRE_SERVICE_H
#define ORCHESTRE_SERVICE_H

// Ici toutes les communications entre l'orchestre et les services :
// - le tube anonyme pour que l'orchestre envoie des données au service
// - le sémaphore pour que  le service indique à l'orchestre la fin
//   d'un traitement

/*** ---- INCLUDE ---- ***/
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "tubesem.h"


/*Identifiant pour les paramètres de ftok*/

#define OS_FICHER "ORCHESTRE_SERVICE/orchestre_service.h"
#define CODE_END 777
#define CODE_SERVICE_AGREE 654

/*** ---- STRUCTURE ---- ***/

//Structure entre l'orchestre et le service
struct oS
{
    //tube anonyme
    int pipeOrchestreService; //tube vers le service (write)

    //Semaphore
    int sem;
};

/*** ---- FONCTIONS ---- ***/


// ---- Orchestre ----

/*Création et initialisation de la structure d'orchestre*/
struct oS *initOrchestreService(int w, int s);

// ---- SÉMAPHORES ----

/*Création d'un sémaphore et initialisation*/
int semCreationOS(int key, int initVal);

//Création du premier service
void createFirstService(int pipeOrchestreService);

#endif