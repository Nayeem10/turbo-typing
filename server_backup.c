#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 12345
#define MESSAGE_SIZE 10

float clientInfo[2] = {20.0, 20.0} ;

float stof(char* message){
    float ret = 0;
    int i = 0;
    while(message[i] != '.'){
        ret = ret * 10 + (message[i] - '0');
        i++;
    }

    ret += ((float)(message[i+1] - '0') / 10.0);
    ret += ((float)(message[i+2] - '0') / 100.0);
    ret += ((float)(message[i+3] - '0') / 1000.0);
    return ret;
}

int main() {
    int server_socket, client_socket[2];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char message[2][MESSAGE_SIZE];
    fd_set readfds;
    int max_sd, activity, i;

    memset(message, 0, sizeof(message));

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 2) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept connections from two clients
    for (i = 0; i < 2; i++) {
        client_addr_len = sizeof(client_addr);
        client_socket[i] = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket[i] < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Connection accepted from client %d\n", i + 1);

        // Set socket to non-blocking mode
        if (fcntl(client_socket[i], F_SETFL, O_NONBLOCK) < 0) {
            perror("Failed to set socket to non-blocking mode");
            exit(EXIT_FAILURE);
        }
    }

    while (1) {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add client sockets to set
        max_sd = -1;
        for (i = 0; i < 2; i++) {
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
            if (FD_ISSET(client_socket[i], &readfds)) {
                int read_result = read(client_socket[i], message[i], sizeof(message[i]));
                if (read_result <= 0) {
                    close(client_socket[i]);
                    printf("Client %d disconnected\n", i + 1);
                } else {
                    clientInfo[i] = stof(message[i]);
                    sprintf(message[i],"%.3f",clientInfo[1-i]);
                    int write_result = write(client_socket[i], message[i], read_result);
                    if (write_result < 0) {
                        perror("Write error");
                    }
                }
            }
        }
    }

    for (i = 0; i < 2; i++) {
        close(client_socket[i]);
    }
    close(server_socket);

    return 0;
}
