#include <iostream>
#include "loadgrap.h"

int main() {

    string filename;
    bool debug = true;

    filename = "../graphs/sample.graph";

    if (loadAdjListContiguous(filename, debug))
        return -1;
    
    return 0;
}