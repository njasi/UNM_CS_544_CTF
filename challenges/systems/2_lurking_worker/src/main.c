#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void serve();

int main()
{
    pid_t pid = fork();
    if (pid > 0)
        exit(0);

    // detach from everything
    setsid();
    chdir("/");
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    // serve forever
    serve();

    return 0;
}

void serve()
{
    // make addr & bind to the socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(1337);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 1);

    // accept connection & send the flag
    while (1)
    {
        int client = accept(sockfd, NULL, NULL);
        const char *msg = "cs544{you_spotted_me}\n";
        send(client, msg, strlen(msg), 0);
        close(client);
    }
}