#ifndef ORCHESTRE_SERVICE_H
#define ORCHESTRE_SERVICE_H

// Ici toutes les communications entre l'orchestre et les services :
// - le tube anonyme pour que l'orchestre envoie des données au service
// - le sémaphore pour que  le service indique à l'orchestre la fin
//   d'un traitement

/*** ---- INCLUDE ---- ***/

#include "tubesem.h"


/*Identifiant pour les paramètres de ftok*/

#define OS_FICHER "ORCHESTRE_SERVICE/orchestre_service.h"
#define CODE_END 777

struct oS
{
    //Tube anonyme
    int pipeOrchestreService;

    //Semaphore
    int sem;
};



#endif
