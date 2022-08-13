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
#define MAXLINE 255 + 2 + 2

int main()
{
    int sockfd;
    char buffer[MAXLINE];
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
    // while (1)
    // {
    //     n = recvfrom(sockfd, (char *)buffer, 255,
    //                  MSG_WAITALL, (struct sockaddr *)&cliaddr,
    //                  &clilen);

    //     if (n > 0)
    //     {
    //         buffer[n] = '\0';
    //         Packet *p = new Packet(buffer);
    //         // std::cout << p->getSeqNum() << std::endl;
    //         s.receivePacket(p);
    //         // if (map.find(cliaddr) == map.end())
    //         // {
    //         //     map[cliaddr] = new State(cliaddr, 0, 0);
    //         // }
    //         // else
    //         // {
    //         //     Packet *p = new Packet(buffer);
    //         //     map[cliaddr]->receivePacket(p);
    //         // }
    //     }
    //     std::cout << s << std::endl;
    // }
    // char b1[MAXLINE];
    // b1[0] = 'a';
    // b1[1] = 'a';
    // b1[2] = 'a';
    // b1[3] = 'a';

    // char b2[MAXLINE];
    // b2[0] = 'b';
    // b2[1] = 'b';
    // b2[2] = 'b';
    // b2[3] = 'b';
    // Packet p1(b1);
    // Packet p2(b2);
    // std::cout << (p1 < p2) << std::endl;
}