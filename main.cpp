#include <iostream>
#include <fstream>
//#include "CSVparse.h"
#include "pixelUpdate.h"
#include "bplustree.h"

using namespace std;


int main() {
    cout << "Hewwo, World!" << endl;

    //pixelUpdateLoader();
    bplusTree node;
    node.insert(new pixelUpdate("5"));
    node.insert(new pixelUpdate("15"));
    node.insert(new pixelUpdate("25"));
    node.insert(new pixelUpdate("35"));
    node.insert(new pixelUpdate("45"));
    node.insert(new pixelUpdate("55"));
    node.insert(new pixelUpdate("40"));
    node.insert(new pixelUpdate("30"));
    node.insert(new pixelUpdate("20"));
    node.insert(new pixelUpdate("10"));
    node.printbplusTree(node.getRoot());

    return 0;
}

