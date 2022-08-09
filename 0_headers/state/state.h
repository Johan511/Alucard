#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include <netinet/in.h>
#define N 256

class Packet
{

private:
    bool ACKd;
    __UINT16_TYPE__ acknoledgement_number;
    __UINT16_TYPE__ sequence_number;
    char *data = new char[N];

public:
    __UINT16_TYPE__ getAckNum();
    __UINT16_TYPE__ getSeqNum();
    bool isACKd();
    std::string getData();

    Packet(char datagram[2 + 2 + N]);
    ~Packet();

protected:
};
class State
{
private:
    std::vector<Packet *> packets;
    struct sockaddr_in cliaddr;
    __UINT8_TYPE__ number_of_buffered_packets;
    __UINT16_TYPE__ initial_acknoledgement_number;
    __UINT16_TYPE__ final_acknoledgement_number;

    __UINT16_TYPE__ initial_sequence_number;
    __UINT16_TYPE__ final_sequence_number;

public:
    State(struct sockaddr_in cliaddr, __U16_TYPE intial_acknowledgement_number, __U16_TYPE intial_sequence_number);
    bool receivePacket(Packet *packet);
    bool receivePacket(Packet packet);

    ~State();

protected:
};