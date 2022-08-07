#include <vector>
#include <string>
#include <stdint.h>
#include <netinet/in.h>
#define N 256

class Packet
{

private:
    static int binaryArrayToInt(bool *bool_array, __UINT8_TYPE__ start, __UINT8_TYPE__ end);
    static char binaryArrayToChar(bool *bool_array);

    __UINT16_TYPE__ acknoledgement_number;
    __UINT16_TYPE__ sequence_number;
    char *data = new char[256];

public:
    __UINT16_TYPE__ getAckNum();
    __UINT16_TYPE__ getSeqNum();
    std::string getData();
    // Packet(__UINT16_TYPE__ acknoledgement_number,
    //        __UINT16_TYPE__ sequence_number, char data[256]);
    // Packet(bool datagram[16 + 16 + (256 * 8)]);
    Packet(char datagram[2 + 2 + 256]);
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

Packet::Packet(char datagram[2 + 2 + 256])
{
    this->acknoledgement_number = ((int)datagram[0] << 1) + ((int)datagram[1] << 1);
    this->sequence_number = ((int)datagram[2] << 1) + ((int)datagram[3] << 1);
    for (int i = 0; i < 256; i++)
    {
        this->data[i] = datagram[4 + i];
    }
}

// Packet::Packet(bool datagram[16 + 16 + (256 * 8)])
// {
//     this->acknoledgement_number = (__U16_TYPE)binaryArrayToInt(datagram, 0, 16);
//     this->sequence_number = (__U16_TYPE)binaryArrayToInt(datagram, 16, 32);
//     for (int i = 0; i < 256; i++)
//     {
//         data[i] = binaryArrayToChar(datagram + 32 + (8 * i));
//     }
// }

Packet::~Packet()
{
    delete (this->data);
}

int Packet::binaryArrayToInt(bool *bool_array, __UINT8_TYPE__ start, __UINT8_TYPE__ end)
{
    int val = 0;
    for (__UINT8_TYPE__ i = end - 1; i >= start; i++)
    {
        if (bool_array[i] == true)
        {
            val = val << 1 + 1;
        }
        else
        {
            val = val << 1 + 0;
        }
    }
    return val;
}
char Packet::binaryArrayToChar(bool *bool_array)
{
    int charecter = 0;
    for (int i = 0; i < 8; i++)
    {
        if (bool_array[i] == true)
        {
            charecter = (charecter << 1) + 1;
        }
        else
        {
            charecter = (charecter << 1) + 0;
        }
    }
    return (char)charecter;
}

State::State(struct sockaddr_in cliaddr)
{
}
