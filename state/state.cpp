#include "../0_headers/state/state.h"

Packet::Packet(char datagram[2 + 2 + N]) : ACKd(false)
{
    this->acknoledgement_number = ((__UINT16_TYPE__)datagram[0] << 8) + ((__UINT16_TYPE__)datagram[1]);
    this->sequence_number = ((__UINT16_TYPE__)datagram[2] << 8) + ((__UINT16_TYPE__)datagram[3]);
    // std::cout << datagram << std::endl;
    // 8 bit integer only goes till 255, so <256 makes no sense => loops back to 0
    __UINT8_TYPE__ i = 0;
    for (; (i < N - 1) && (datagram[i + 4] != '\0'); i++)
    {
        this->data[i] = datagram[4 + i];
    }
    data[i] = '\0';
    data[N - 1] = datagram[2 + 2 + N - 1];
}

// Packet::Packet(const Packet &original_packet)
// {
//     ACKd = original_packet.isACKd();
//     acknoledgement_number = original_packet.getAckNum();
//     sequence_number = original_packet.getSeqNum();
// }

Packet::~Packet()
{
    // not delocating memory remember that in case of any memory leak
    // we need to overlaod copy constructor to do hard copy
}

bool Packet::updateACK(bool to) const
{
    this->ACKd = to;
    return true;
}

bool Packet::isACKd() const
{
    return this->ACKd;
}

__U16_TYPE Packet::getSeqNum() const
{
    return sequence_number;
}

__U16_TYPE Packet::getAckNum() const
{
    return acknoledgement_number;
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
    if ((packet->getSeqNum() > final_sequence_number) || packets_set.size() == 0)
    {
        packets_set.insert(*packet);
        final_sequence_number = packets_set.rbegin()->getSeqNum();
    }

    auto it = std::find_if(packets_set.begin(), packets_set.end(), [packet](auto it)
                           { return (it.getSeqNum() == packet->getAckNum()) ? true : false; });
    // linear time, think about it again
    it->updateACK(true);

    while (packets_set.begin()->isACKd() == true)
    {
        packets_set.erase(packets_set.begin());
    }

    delete packet;

    return true;
}

State::~State()
{
}

std::ostream &operator<<(std::ostream &out, State s)
{
    for (int i = 0; i < s.packets.size(); i++)
    {
        out << "Acknoledgement Number : " << s.packets[i]->getAckNum() << std::endl;
        out << "Sequence Number : " << s.packets[i]->getSeqNum() << std::endl;
        out << "Data : " << s.packets[i]->data << std::endl;
    }
    return out;
}

bool Packet::operator<(Packet const &packet2) const
{
    if (this->sequence_number < packet2.sequence_number)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// bool Packet::operator==(__UINT16_TYPE__ sequence_number) const
// {
//     if (this->sequence_number == sequence_number)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }