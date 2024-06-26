#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "randomtext.h"

#define PORT 12345
#define MESSAGE_SIZE 10

volatile sig_atomic_t server_running = 1;

void sigint_handler(int sig) {
    server_running = 0;
}

char clientName[2][20];

float clientInfo[2] = {20.0, 20.0};

float stof(char *message) {
    float ret = 0;
    int i = 0;
    while (message[i] != '.') {
        ret = ret * 10 + (message[i] - '0');
        i++;
    }

    ret += ((float)(message[i + 1] - '0') / 10.0);
    ret += ((float)(message[i + 2] - '0') / 100.0);
    ret += ((float)(message[i + 3] - '0') / 1000.0);
    return ret;
}

void serverOn() {
    clientInfo[0] = 20.0;
    clientInfo[1] = 20.0;
    int server_socket, client_socket[2];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    fd_set readfds;
    int max_sd, activity, i;

    char message[MESSAGE_SIZE];
    memset(message, 0, sizeof(message));

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 2) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    char *text = generate_random_text(2, 100);
    for (i = 0; i < 2; i++) {
        client_addr_len = sizeof(client_addr);
        client_socket[i] = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if(server_running){
            send(client_socket[i], text, 400, 0);
            recv(client_socket[i], clientName[i], 16, 0);
        }
        if (client_socket[i] < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Connection accepted from client %d\n", i + 1);

        if (fcntl(client_socket[i], F_SETFL, O_NONBLOCK) < 0) {
            perror("Failed to set socket to non-blocking mode");
            exit(EXIT_FAILURE);
        }
    }

    if(server_running){
        for(int i = 0; i < 2; i++){
            char buffer[32];
            sprintf(buffer, "%d%s", i, clientName[1 - i]);
            send(client_socket[i], buffer, 32, 0);
        }
    }
    while (server_running) {
        FD_ZERO(&readfds);

        max_sd = -1;
        for (i = 0; i < 2; i++) {
            if(client_socket[i] == -1) continue;

            FD_SET(client_socket[i], &readfds);
            if (client_socket[i] > max_sd) {
                max_sd = client_socket[i];
            }
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            perror("Select error");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < 2; i++) {
            if(client_socket[i] == -1) continue;

            if (FD_ISSET(client_socket[i], &readfds)) {
                int read_result = read(client_socket[i], message, sizeof(message));
                if (read_result <= 0) {
                    close(client_socket[i]);
                    client_socket[i] = -1;
                    printf("Client %d disconnected\n", i + 1);
                } else {
                    clientInfo[i] = stof(message);
                    sprintf(message, "%.3f", clientInfo[1 - i]);
                    int write_result = write(client_socket[i], message, read_result);
                    if (write_result < 0) {
                        perror("Write error");
                    }
                }
            }
        }
        if(client_socket[0] == -1 && client_socket[1] == -1) break;
    }

    for (i = 0; i < 2; i++) {
        close(client_socket[i]);
    }

    close(server_socket);
}

int main() {
    
    //while(server_running){
        struct sigaction sa;
        sa.sa_handler = sigint_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGINT, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }

        serverOn();    
    //}
    return 0;
}
