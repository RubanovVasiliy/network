#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024
#define LIMIT 10
#define PORT 8080

void readHtmlData(char responseData[]);
void createResponse(char httpHeader[]);
void info(struct sockaddr_in *serverAddress);

int main(void)
{
    char httpHeader[8000] = "";
    struct sockaddr_in serverAddress, clientAddress;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    socklen_t addressLength = sizeof(serverAddress);
    int listening = listen(serverSocket, LIMIT);
    if (listening < 0)
    {
        printf("Error: The server is not listening.\n");
        return 1;
    }

    info(&serverAddress);
    createResponse(httpHeader);

    int clientSocket;
    while (1)
    {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &addressLength);
        if (clientSocket > 0)
        {
            send(clientSocket, httpHeader, sizeof(httpHeader), 0);
            printf("%s %s:%d\n", "Request from a client with the address:", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
            close(clientSocket);
        }
    }
    return 0;
}

void readHtmlData(char responseData[])
{
    FILE *htmlData = fopen("index.html", "r");
    char line[100];
    while (fgets(line, 100, htmlData) != 0)
    {
        strcat(responseData, line);
    }
}

void createResponse(char httpResponse[])
{
    char response[8000] = "HTTP/1.1 200 OK\n"
                          "Content-Type: text/html\n"
                          "Content-Length: ";

    char responseData[7000];
    readHtmlData(responseData);

    char str[100];
    sprintf(str, "%lu", strlen(responseData));

    strcat(response, str);
    strcat(response, "\n"
                     "Accept-Ranges: bytes\n"
                     "Connection: close\n\n");
    strcat(response, responseData);

    strcat(httpResponse, response);
}

void info(struct sockaddr_in *serverAddress)
{
    char hostBuffer[INET6_ADDRSTRLEN];
    char serviceBuffer[NI_MAXSERV];
    socklen_t addr_len = sizeof(*serverAddress);
    int err = getnameinfo((struct sockaddr *)serverAddress, addr_len, hostBuffer, sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), NI_NUMERICHOST);
    if (err != 0)
    {
        printf("Server error\n");
        exit(1);
    }
    printf("Server started on PORT: %d\nhttp://%s:%s\n", PORT, hostBuffer, serviceBuffer);
}