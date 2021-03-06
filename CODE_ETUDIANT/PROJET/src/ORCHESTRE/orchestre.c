//Pierre Guillaume
//Valdrin Salihi

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "config.h"
#include "client_orchestre.h"
#include "orchestre_service.h"
#include "service.h"
#include "io.h"
#include "client_service.h"

#define SIZE_MAX 100

static void usage(const char *exeName, const char *message)
{
    fprintf(stderr, "usage : %s <fichier config>\n", exeName);
    if (message != NULL)
        fprintf(stderr, "message : %s\n", message);
    exit(EXIT_FAILURE);
}

char *randStr(int size){
    const char template[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *str = NULL;
    str = malloc(size * sizeof(char));
    for(int i = 0; i < size-1; i++){
        int j = rand() % (int) sizeof(template-1);
        str[i] = template[j];
    }
    str[size] = '\0';
    return str;
}

int main(int argc, char * argv[])
{
    if (argc != 2)
        usage(argv[0], "nombre paramètres incorrect");
    
    bool fin = false;

    // lecture du fichier de configuration
    config_init(argv[1]);

    // Pour la communication avec les clients
    // - création de 2 tubes nommés pour converser avec les clients
    linkClientOrchestre(CLIENT_ORCHESTRE, ORCHESTRE_CLIENT);
    // - création d'un sémaphore pour que deux clients ne
    //   ne communiquent pas en même temps avec l'orchestre
    int semClient = semCreationCO(CLIENT_ORCHESTRE_ID, 1);
    // lancement des services, avec pour chaque service :
    // - création d'un tube anonyme pour converser (orchestre vers service)
    int fdOS[2];
    myPipe(fdOS);
    // - un sémaphore pour que le service préviene l'orchestre de la
    //   fin d'un traitement

    // - création de deux tubes nommés (pour chaque service) pour les
    //   communications entre les clients et les services

    //tube només pour le service somme
    myMkfifo(CLIENT_SERVICE_0, 0641);
    myMkfifo(SERVICE_CLIENT_0, 0641);
    //tube només pour le Service compression
    myMkfifo(CLIENT_SERVICE_1, 0641);
    myMkfifo(SERVICE_CLIENT_1, 0641);
    //tube només pour le Service maximum
    myMkfifo(CLIENT_SERVICE_2, 0641);
    myMkfifo(SERVICE_CLIENT_2, 0641);
    

    while (! fin)
    {
        // ouverture ici des tubes nommés avec un client
        int tco = myOpen(CLIENT_ORCHESTRE , O_RDONLY);
        int toc = myOpen(ORCHESTRE_CLIENT, O_WRONLY);
        // attente d'une demande de service du client
        wait(NULL);
        // détecter la fin des traitements lancés précédemment via
        // les sémaphores dédiés (attention on n'attend pas la
        // fin des traitement, on note juste ceux qui sont finis)

        // analyse de la demande du client
        int ask;
        myRead(tco, &ask, sizeof(int));
        // si ordre de fin
        //     envoi au client d'un code d'acceptation (via le tube nommé)
        //     marquer le booléen de fin de la boucle
        // sinon si service non ouvert
        //     envoi au client d'un code d'erreur (via le tube nommé)
        // sinon si service déjà en cours de traitement
        //     envoi au client d'un code d'erreur (via le tube nommé)
        // sinon
        //     envoi au client d'un code d'acceptation (via le tube nommé)
        //     génération d'un mot de passe
        //     envoi d'un code de travail au service (via le tube anonyme)
        //     envoi du mot de passe au service (via le tube anonyme)
        //     envoi du mot de passe au client (via le tube nommé)
        //     envoi des noms des tubes nommés au client (via le tube nommé)
        // finsi
        if(ask == REQUEST_STOP){
            int r = REQUEST_AGREE;
            myWrite(toc, &r, sizeof(int));
            fin = true;
        }/*else if(){
            myWrite(toc, REQUEST_ERROR, sizeof(int));
        }else if(){
            myWrite(toc, REQUEST_ERROR, sizeof(int));
            }*/
        else{
            int r = REQUEST_AGREE;
            myWrite(toc, &r, sizeof(int));
            int size = rand() % SIZE_MAX;
            char *password = randStr(size);

            int c = CODE_SERVICE_AGREE;

            myWrite(fdOS[1] , &c, sizeof(int));
            myWrite(fdOS[1], password, strlen(password) * sizeof(char));
            myWrite(toc , &c, sizeof(int));

            
        }

        // attente d'un accusé de réception du client
        // fermer les tubes vers le client
        int receipt = 0;
        myRead(tco, &receipt, sizeof(int));
        if(receipt == CONTINUE){
            myClose(toc);
            myClose(tco);
            
        }

        // il peut y avoir un problème si l'orchestre revient en haut de la
        // boucle avant que le client ait eu le temps de fermer les tubes
        // il faudrait régler cela avec un sémaphore, mais on va se contenter
        // d'une attente de 1 seconde (solution non satisfaisante mais simple)
        sleep(1);
    }

    // attente de la fin des traitements en cours (via les sémaphores)

    // envoi à chaque service d'un code de fin

    // attente de la terminaison des processus services

    // libération des ressources
    
    return EXIT_SUCCESS;
}
