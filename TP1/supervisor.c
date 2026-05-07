#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>

char *main_port;

int start_child(char *port) {
    pid_t pid;
    int rv; // Return value
    char *args[4] = {"tcp_echo_server", NULL, NULL, NULL};

    pid = fork();
    args[1] = port;

    if(pid < 0) {
        printf("Erreur dans la création du processus\n");
        return -1;

    } else if (pid ==0) {
        printf("Processus créé qui démarre sur le port %s\n", port);
        rv = execvp("./tcp-echo-server", args);

        if (rv < 0) {
            printf("Echec de l'exécution du tcp-echo-server\n");
            return -1;
        }

    } else {
        printf("PID du fils %d\n", pid);
    }

    return pid;
}

void sighandler(int signum) {
    printf("Signal reçu %d\n", signum);
    if (signum == SIGCHLD) {
        printf("SIGCHLD reçu.\n");
    }
    if (start_child(main_port) < 0) {
        printf("Erreur start_child\n");
        exit(-1);
    }
}

int main(int argc, char **argv) {
    pid_t pid;
    int rv;
    char *args[4] = {"echo_server", NULL, NULL, NULL};

    if (argc < 2) {
        printf("Arguments...\n");
        exit(-2);
    }
    main_port = argv[1];
    signal(SIGCHLD, sighandler);

    if (start_child(main_port)<0) {
        printf("Erreur start_child\n");
        return -1;
    }
    while(1);
}
