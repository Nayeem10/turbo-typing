#ifdef linux
#include <fcntl.h>
#include <linux/input.h>
#include <X11/XKBlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int client_socket = 0;

bool serverConnect(){
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        return 0;
    }

    // Set server address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 0;
    }
    printf("Connected to server\n");
    return 1;
}

#elif _WIN32
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

SOCKET client_socket;

bool serverConnect(){
    WSADATA wsaData;
    struct sockaddr_in server_addr;
    int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0){
        fprintf(stderr, "WSAStartup failed with error: %d\n", result);
        exit(EXIT_FAILURE);
    }

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET){
        fprintf(stderr, "Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Set server address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Connect to server
    result = connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR){
        fprintf(stderr, "Connection failed with error: %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");
}

#endif

char* gameData(){
    char *buffer = malloc(322);
    read(client_socket,buffer, 32);
    return buffer;
}

void sendToServer(float data) {
    char message[10];
    sprintf(message,"%.3f",data);
    send(client_socket, message, strlen(message), 0);
}

char* receiveStr(){
    char *message;
    message = (char*) malloc(sizeof(char) * 400);
    recv(client_socket, message, 400, 0);
    return message;
}

void sendStr(char *message){
    send(client_socket, message, 16, 0);
}

float receiveFromServer(){
    char message[10];
    recv(client_socket, message, 10, 0);
    if(strlen(message) == 0){
        return 0;
    }
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

void close_socket(){
    close(client_socket);
}