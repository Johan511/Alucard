#include <vector>
#include <string>
#include <stdint.h>
#include <netinet/in.h>
#define N 256

class Packet
{

private:
    __UINT16_TYPE__ acknoledgement_number;
    __UINT16_TYPE__ sequence_number;
    char *data = new char[N];

public:
    __UINT16_TYPE__ getAckNum();
    __UINT16_TYPE__ getSeqNum();
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

public:
    State(struct sockaddr_in cliaddr);

    ~State();

protected:
};

Packet::Packet(char datagram[2 + 2 + N])
{
    this->acknoledgement_number = ((int)datagram[0] << 1) + ((int)datagram[1] << 1);
    this->sequence_number = ((int)datagram[2] << 1) + ((int)datagram[3] << 1);
    for (__UINT8_TYPE__ i = 0; i < N - 1; i++)
    {
        this->data[i] = datagram[4 + i];
    }
    data[255] = datagram[2 + 2 + N - 1];
}

Packet::~Packet()
{
    delete (this->data);
}

State::State(struct sockaddr_in cliaddr)
{
}
