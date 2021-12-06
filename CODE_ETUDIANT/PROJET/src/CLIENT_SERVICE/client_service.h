#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

// Ici toutes les communications entre les services et les clients :
// - les deux tubes nommés pour la communication bidirectionnelle

#define CODE_ERROR_PSW 951
#define CODE_AGREE_PSW 159

struct cS{
    int tcs;
    int tsc;
};

#endif
