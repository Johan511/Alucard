#include "../0_headers/state/state.h"

Packet::Packet(char datagram[2 + 2 + N]) : ACKd(false)
{
    this->acknoledgement_number = ((__UINT8_TYPE__)datagram[0] << 8) + ((__UINT8_TYPE__)datagram[1]);
    this->sequence_number = ((__UINT8_TYPE__)datagram[2] << 8) + ((__UINT8_TYPE__)datagram[3]);
    // 8 bit integer only goes till 255, so <256 makes no sense => loops back to 0
    __UINT8_TYPE__ i = 0;
    for (; (i < N - 1) && (datagram[i + 4] != '\0'); i++)
    {
        this->data[i] = datagram[4 + i];
    }
    data[i] = '\0';
    data[255] = datagram[2 + 2 + N - 1];
}

Packet::~Packet()
{
    delete (this->data);
}

bool Packet::isACKd()
{
    return this->ACKd;
}

__U16_TYPE Packet::getSeqNum()
{
    return sequence_number;
}

State::State(sockaddr_in cliaddr, __U16_TYPE intial_acknowledgement_number, __U16_TYPE intial_sequence_number)
{
    this->cliaddr = cliaddr;
    this->initial_acknoledgement_number = initial_acknoledgement_number;
    this->initial_sequence_number = initial_sequence_number;
    this->final_acknoledgement_number = initial_acknoledgement_number;
    this->final_sequence_number = final_sequence_number;
}

bool State::receivePacket(Packet *packet)
{
    if ((packet->getSeqNum() > final_sequence_number))
    {
        packets.push_back(packet);
        final_sequence_number = packet->getSeqNum();
    }

    // if ((packet->getAckNum() == initial_acknoledgement_number))
    // {
    //     packets.pop_back();
    //     auto it = packets.begin();
    //     while (it->isACKd() == false)
    //     {
    //         it++;
    //         packets.pop_back();
    //     }
    // }
    return true;
}
// bool State::receivePacket(Packet packet)
// {
//     if ((packet.getSeqNum() > final_sequence_number))
//     {
//         packets.push_back(packet);
//         final_sequence_number = packet.getSeqNum();
//     }

//     // if ((packet->getAckNum() == initial_acknoledgement_number))
//     // {
//     //     packets.pop_back();
//     //     auto it = packets.begin();
//     //     while (it->isACKd() == false)
//     //     {
//     //         it++;
//     //         packets.pop_back();
//     //     }
//     // }
//     return true;
// }

State::~State()
{
}
