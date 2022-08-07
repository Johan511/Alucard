#include <stdio.h>
#include <string>
#include "./state/state.cpp"
using namespace std;
bool *string_to_bool(string s);
int main()
{

    char buffer[2 + 2 + 256] = "\0\0\0\0HiMy Name Is __X";
    Packet p(buffer);
    return 0;
}
