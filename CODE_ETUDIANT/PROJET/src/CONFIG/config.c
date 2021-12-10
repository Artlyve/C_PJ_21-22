/*
 * Indications (à respecter) :
 * - Les erreurs sont gérées avec des assert ; les erreurs traitées sont :
 *    . appel trop tôt ou trop tard d'une méthode (cf. config.h)
 *    . fichier de configuration inaccessible
 *    . une position erronée
 * - Le fichier (si on arrive à l'ouvrir) est considéré comme bien
 *   formé sans qu'il soit nécessaire de le vérifier
 *
 * Un code minimal est fourni et permet d'utiliser le module "config" dès
 * le début du projet ; il faudra le remplacer par l'utilisation du fichier
 * de configuration.
 * Il est inutile de faire plus que ce qui est demandé
 *
 * Dans cette partie vous avez le droit d'utiliser les entrées-sorties
 * de haut niveau (fopen, fgets, ...)
 */

#include <stdlib.h>
#include <stdio.h>
// TODO include des .h système

#include "myassert.h"

#include "config.h"

// TODO Définition des données ici
int countInit = 0;
int countExit = 0;
char *stock;

void config_init(const char *filename)
{
    // TODO erreur si la fonction est appelée deux fois
        myassert(countInit > 1, "ERROR CONFIG INIT utilisé plus d'une fois");
    
    // TODO code vide par défaut, à remplacer
    //      il faut lire le fichier et stocker toutes les informations en
    //      mémoire
    FILE *f = NULL;
    f = fopen(filename, "r");
    int count = 0;
    char caractereActuel = 0;
    myassert(f != NULL, "ERROR CONFIG INIT fichier null");
    

    while(caractereActuel != EOF){
        caractereActuel = fgetc(f);
        count++;
    }

    caractereActuel = 0;

    stock = malloc(count * sizeof(char));

    
    for(int i = caractereActuel; i !=EOF; i++){

        caractereActuel = fgetc(f);
        stock[i] = caractereActuel;
    }

    fclose(f);
    countExit++;

}

void config_exit()
{
    // TODO erreur si la fonction est appelée avant config_init
    myassert(countInit == 0, "ERROR CONFIG EXIT config init n'a pas été appélée");
    // TODO code vide par défaut, à remplacer
    //      libération des ressources
    free(stock);
    countExit++;
}

int config_getNbServices()
{
    // erreur si la fonction est appelée avant config_init
    // erreur si la fonction est appelée après config_exit

    myassert(countInit == 0, "ERROR CONFIG GETNBSERVICES config init n'a pas été appélée");
    myassert(countExit == 1, "ERROR CONFIG GETNBSERVICES config exit est déjà appélee");
    // code par défaut, à remplacer
    return 3;
}

const char * config_getExeName()
{
    // TODO erreur si la fonction est appelée avant config_init
    // TODO erreur si la fonction est appelée après config_exit
    myassert(countInit == 0, "ERROR CONFIG GETEXENAME config init n'a pas été appélée");
    myassert(countExit == 1, "ERROR CONFIG GETEXENAME config exit est déjà appélee");

    // TODO code par défaut, à remplacer
    const char * name = "SERVICE/service";
    return name;
}

bool config_isServiceOpen(int pos)
{
    // TODO erreur si la fonction est appelée avant config_init
    // TODO erreur si la fonction est appelée après config_exit
    myassert(countInit == 0, "ERROR CONFIG GETEXENAME config init n'a pas été appélée");
    myassert(countExit == 1, "ERROR CONFIG GETEXENAME config exit est déjà appélee");
    // TODO erreur si "pos" est incorrect
    myassert(pos > 3, "ERROR CONFIG ISOPENSERVICE pos incorrect");

    // TODO code par défaut, à remplacer
    bool open[] = {true, false, true};
    return open[pos];
}
