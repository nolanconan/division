
#include "erreur.h"
#include "udp.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Créer une socket */
void creer_socket(char* adresseIP, int port, SOCK* sock) {
    sock->fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock->fd < 0) {
        traiter_erreur("creer_socket");
        return;
    }

    memset(&(sock->addr), 0, sizeof(sock->addr));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_port = htons(port);
    sock->addr.sin_addr.s_addr = inet_addr(adresseIP);

    traiter_erreur("creer_socket");
}

/* Attacher une socket */
void attacher_socket(SOCK* sock) {
    if (bind(sock->fd, (struct sockaddr*)&(sock->addr), sizeof(sock->addr)) < 0) {
        traiter_erreur("attacher_socket");
        return;
    }
    traiter_erreur("attacher_socket");
}

/*Initialiser la structure adresse client */
void init_addr(SOCK* sock) {
    memset(&(sock->addr), 0, sizeof(sock->addr));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->addr.sin_port = 0;

    traiter_erreur("init_addr");
}

/* Dimensionner la file d'attente d'une socket */
void dimensionner_file_attente_socket(int taille, SOCK* sock) {
    if (listen(sock->fd, taille) < 0) {
        traiter_erreur("dimensionner_file_attente_socket");
        return;
    }
    traiter_erreur("dimensionner_file_attente_socket");
}

/* Recevoir un message */
void recevoir_message(SOCK* dst, char * buffer) {
    socklen_t addr_len = sizeof(dst->addr);
    if (recvfrom(dst->fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&(dst->addr), &addr_len) < 0) {
        traiter_erreur("recevoir_message");
        return;
    }
    traiter_erreur("recevoir_message");
}

/* Émettre un message */
void envoyer_message(SOCK* dst, char * message) {
    if (sendto(dst->fd, message, strlen(message), 0, (struct sockaddr*)&(dst->addr), sizeof(dst->addr)) < 0) {
        traiter_erreur("envoyer_message");
        return;
    }
    traiter_erreur("envoyer_message");
}

/* Fermer la connexion */
void fermer_connexion(SOCK* sock) {
    if (close(sock->fd) < 0) {
        traiter_erreur("fermer_connexion");
        return;
    }
    traiter_erreur("fermer_connexion");
}
