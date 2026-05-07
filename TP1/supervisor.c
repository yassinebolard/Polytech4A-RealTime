#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;

    pid = fork();

    if(pid != -1) {
        printf("Processus créé\n");
        execvp("./tcp-echo-server.c", argv);

        printf("Fin d'exécution du programme\n");

    } else {
        printf("Erreur dans la création du processus\n");
        return -1;

    }

    return 0;
}
