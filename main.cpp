#include <stdio.h>
#include <string>
#include "./state/state.cpp"
using namespace std;
bool *string_to_bool(string s);
int main()
{
    // string s = "My name is _";
    // bool *bool_array = string_to_bool(s);
    // Packet p(bool_array);
    char buffer[2 + 2 + 256] = "\0\0\0\0HiMy Name Is __";
    Packet p(buffer);
    return 0;
}
