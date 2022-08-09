#include <pthread.h>
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>    //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#include "./0_headers/state/map.h"

#define TRUE 1
#define FALSE 0
#define PORT 3000

int main()
{
    int sockfd;
    char buffer[255 + 2 + 2];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket connection failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(3000);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    len = sizeof(cliaddr);
    State s(cliaddr, 0, 0);
    while (1)
    {
        n = recvfrom(sockfd, (char *)buffer, 255,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &clilen);

        if (n > 0)
        {
            buffer[n] = '\0';
            s.receivePacket(new Packet(buffer));
            // if (map.find(cliaddr) == map.end())
            // {
            //     map[cliaddr] = new State(cliaddr, 0, 0);
            // }
            // else
            // {
            //     Packet *p = new Packet(buffer);
            //     map[cliaddr]->receivePacket(p);
            // }

            printf("Client : %s\n", buffer);
        }
    }
}