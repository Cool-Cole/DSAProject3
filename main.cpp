#include <iostream>
#include <fstream>
#include "CSVparse.h"
#include "bplustree.h"
#include "hashmap.h"

using namespace std;


int main(int argc, char **argv) {

    // Sanity check to ensure that the user isn't just running this binary without arguments
    if(argc < 3){
        cout << "Please ensure that you are running ./project3 -hashmap data.csv or ./project3 -bplustree data.csv." << endl;
        return 0;
    }

    vector<pixelUpdate*> rawPixelData;

    pixelUpdateLoader(rawPixelData, argv[2]); // Load the file information into the rawPixelData array

    /*

     VERY VERY IMPORTANT NOTE!!!

     For the sake of performance please don't copy pixel objects into new pixel objects
     Just take the pointers and shove them into whatever data structure you are using

     If I see the pixelUpdate copy constructor being used unironically I will murder whoever wrote that code

     */


    if(argv[1] == "-hashmap"){

        cout << "The r/place data set is being loaded into memory as a hashmap... (this might take a while)" << endl;

        Hashmap cord_map(CORD);
        Hashmap userid_map(USERID);
        Hashmap color_map(COLOR);

        for(auto it = rawPixelData.begin(); it != rawPixelData.end(); it++){
            cord_map.insert(*it);
            //userid_map.insert(*it);
            //color_map.insert(*it);
        }

        cout << "The r/place data set has been successfully loaded into memory!" << endl;

    } else if(argv[1] == "-bplustree"){

        cout << "The r/place data set is being loaded into memory as a bplustree... (this might take a while)" << endl;

        // TODO set up bplustree

        cout << "The r/place data set has been successfully loaded into memory!" << endl;

    }



    return 0;
}

