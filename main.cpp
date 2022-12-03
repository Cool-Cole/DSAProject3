#include <iostream>
#include <fstream>
#include "CSVparse.h"
#include "pixelUpdate.h"
#include "bplustree.h"

using namespace std;


int main(int argc, char **argv) {

    // Sanity check to ensure that the user isn't just running this binary without arguments
    if(argc < 3){
        cout << "Please ensure that you are running ./project3 -hashmap data.csv or ./project3 -bplustree data.csv." << endl;
        return 0;
    }



    if(argv[1] == "-hashmap"){

        cout << "The r/place data set is being loaded into memory as a hashmap... (this might take a while)" << endl;

        // TODO set up hashmap

        cout << "The r/place data set has been successfully loaded into memory!" << endl;

    } else if(argv[1] == "-bplustree"){

        cout << "The r/place data set is being loaded into memory as a bplustree... (this might take a while)" << endl;

        // TODO set up bplustree

        cout << "The r/place data set has been successfully loaded into memory!" << endl;

    }



    return 0;
}

