#include "erreur.h"
#include "udp.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Créer une socket */
void creer_socket(char* adresseIP, int port, SOCK* sock) {
      sock->descripteur = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock->descripteur == -1) {
      traiter_erreur(__FUNCTION__);
      /*A COMPLETER*/
}
      bzero(&sock->adresse, sizeof(sock->adresse));
    sock->adresse.sin_family = AF_INET;
    sock->adresse.sin_port = htons(port);
    if (inet_aton(adresseIP, &sock->adresse.sin_addr) == 0) {

}
/* Attacher une socket */
void attacher_socket(SOCK* sock) {
      if (bind(sock->descripteur, (struct sockaddr*)&sock->adresse, sizeof(sock->adresse)) == -1) {
      traiter_erreur(__FUNCTION__);
}

/*Initialiser la structure adresse client */
void init_addr(SOCK* sock) {
      bzero(&sock->adresse, sizeof(sock->adresse));
    sock->adresse.sin_family = AF_INET;
    sock->adresse.sin_addr.s_addr = htonl(INADDR_ANY);
    traiter_erreur(__FUNCTION__);
}

/* Dimensionner la file d'attente d'une socket */
void dimensionner_file_attente_socket(int taille, SOCK* sock) {
      if (listen(sock->descripteur, taille) == -1) {
      traiter_erreur(__FUNCTION__);
}

/* Recevoir un message */
void recevoir_message(SOCK* dst, char * buffer) {
      struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);
    int recu = recvfrom(dst->descripteur, buffer, BUFSIZ, 0, (struct sockaddr*)&src_addr, &addr_len);
    if (recu == -1) {
      traiter_erreur(__FUNCTION__);
      buffer[recu] = '\0';
}

/* Émettre un message */
void envoyer_message(SOCK* dst, char * message) {
      int envoye = sendto(dst->descripteur, message, strlen(message), 0, (struct sockaddr*)&dst->adresse, sizeof(dst->adresse));
    if (envoye == -1) {
      traiter_erreur(__FUNCTION__);
}

/* Fermer la connexion */
void fermer_connexion(SOCK* sock) {
      if (close(sock->descripteur) == -1) {
      traiter_erreur(__FUNCTION__);
}

