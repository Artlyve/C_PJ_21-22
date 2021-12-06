#ifndef ORCHESTRE_SERVICE_H
#define ORCHESTRE_SERVICE_H

// Ici toutes les communications entre l'orchestre et les services :
// - le tube anonyme pour que l'orchestre envoie des données au service
// - le sémaphore pour que  le service indique à l'orchestre la fin
//   d'un traitement


/*Identifiant pour le deuxième paramètre de ftok*/
#define MASTER_SERVICE_ID 9
#define CODE_END 777

struct oS
{
    //Tube anonyme
    int pipeMasterService;

    //Semaphore
    int sem;
};



#endif
