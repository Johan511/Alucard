#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include <netinet/in.h>
#include <iostream>
#include <bits/stdc++.h>

#define N 256
class State;
class Packet
{
    friend std::ostream &operator<<(std::ostream &out, State s);
    friend std::less<Packet>;

private:
    mutable bool ACKd;
    __UINT16_TYPE__ acknoledgement_number;
    __UINT16_TYPE__ sequence_number;
    char *data = new char[N];
    bool operator<(Packet const &packet2) const;

public:
    // bool operator==(__UINT16_TYPE__ sequence_number) const;
    __UINT16_TYPE__ getAckNum() const;
    __UINT16_TYPE__ getSeqNum() const;
    bool isACKd() const;
    bool updateACK(bool to) const;
    std::string getData() const;

    // Packet(const Packet &original_packet);
    Packet(char datagram[2 + 2 + N]);
    ~Packet();

protected:
};
class State
{
    friend std::ostream &operator<<(std::ostream &out, State s);

private:
    std::vector<Packet *> packets;
    std::set<Packet> packets_set;
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
};