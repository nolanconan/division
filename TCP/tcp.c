
#include "erreur.h"
#include "tcp.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Créer une socket */
int creer_socket(char* adresseIP, int port) {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        traiter_erreur(__FUNCTION__);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(adresseIP);
    serv_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        traiter_erreur(__FUNCTION__);
    }

    return sock;
}

/* Connecter une socket */
void connecter_socket(int sock) {
    // Ici, on assume que la connexion est déjà faite dans creer_socket
    // Donc cette fonction pourrait ne rien faire de plus
    (void)sock; // Pour éviter un avertissement de variable non utilisée
}

/* Attacher une socket */
void attacher_socket(int sock, struct sockaddr_in *addr) {
    if (bind(sock, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        traiter_erreur(__FUNCTION__);
    }
}

/* Dimensionner la file d'attente d'une socket */
void dimensionner_file_attente_socket(int sock, int taille) {
    if (listen(sock, taille) < 0) {
        traiter_erreur(__FUNCTION__);
    }
}

/* Initialiser la structure adresse client */
void init_addr_client(struct sockaddr_in *client_addr) {
    memset(client_addr, 0, sizeof(*client_addr));
    client_addr->sin_family = AF_INET;
    client_addr->sin_addr.s_addr = INADDR_ANY;
}

/* Attendre une connexion */
int attendre_connexion(int sock, struct sockaddr_in *client_addr) {
    socklen_t client_len = sizeof(*client_addr);
    int socktraitement = accept(sock, (struct sockaddr *) client_addr, &client_len);
    if (socktraitement < 0) {
        traiter_erreur(__FUNCTION__);
    }

    return socktraitement;
}

/* Recevoir un message */
void recevoir_message(int socktraitement, char *buffer, size_t buffer_size) {
    ssize_t n = recv(socktraitement, buffer, buffer_size, 0);
    if (n < 0) {
        traiter_erreur(__FUNCTION__);
    }
}

/* Émettre un message */
void envoyer_message(int socktraitement, char *message) {
    ssize_t n = send(socktraitement, message, strlen(message), 0);
    if (n < 0) {
        traiter_erreur(__FUNCTION__);
    }
}

/* Fermer la connexion */
void fermer_connexion(int socktraitement) {
    close(socktraitement); // close() retourne 0 en cas de succès et -1 en cas d'échec
    traiter_erreur(__FUNCTION__); // Si close échoue, traiter_erreur sera appelé
}
