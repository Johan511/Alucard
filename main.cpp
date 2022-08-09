#include <stdio.h>
#include <string>
#include "./state/state.cpp"
using namespace std;
bool *string_to_bool(string s);
int main()
{

    char buffer[2 + 2 + 256] = {};
    buffer[0] = (char)0b10000000;
    buffer[1] = (char)0b00000000;
    buffer[2] = (char)0b10000000;
    buffer[3] = (char)0b00000000;

    for (int i = 4; i < 14; i++)
    {
        buffer[i] = 'a';
    }

    Packet p(buffer);
    return 0;
}
