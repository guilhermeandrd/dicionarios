#include <iostream>

using namespace std;
#include "estruturas_auxiliares/ChainedHashTable.hpp"

int main() {
    ChainedHashTable<string, int> oi;

    oi.add("moca", 8);

    cout << oi;
    return 0;
}