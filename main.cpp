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

    cout << "Loading the r/place data set into memory... (this might take a while)" << endl;

    vector<pixelUpdate*> rawPixelData;

    pixelUpdateLoader(rawPixelData, argv[2]); // Load the file information into the rawPixelData array

    cout << "The r/place data set has been successfully loaded into memory!" << endl;


    if(argv[1] == (string)"-hashmap"){

        cout << "The r/place data set is being loaded into memory as a hashmap..." << endl;

        Hashmap cord_map(CORD);
        Hashmap userid_map(USERID);
        Hashmap color_map(COLOR);

        for(auto it = rawPixelData.begin(); it != rawPixelData.end(); it++){
            cord_map.insert(*it);
            userid_map.insert(*it);
            color_map.insert(*it);
        }

        cout << "The r/place data set has been successfully loaded as a hashmap!" << endl;

    } else if(argv[1] == (string)"-bplustree"){

        cout << "The r/place data set is being loaded into memory as a B+ Tree... (this might take a while)" << endl;

        bplusTree userid_tree;
        bplusTree color_tree;
        bplusTree coordinate_tree;
        for(auto it = rawPixelData.begin(); it != rawPixelData.end(); it++){
            userid_tree.insertID(*it);
            color_tree.insertColor(*it);
            coordinate_tree.insertCoordinates(*it);
        }

        cout << "The r/place data set has been successfully loaded as a B+ Tree!" << endl;
    }

    int userChoice = 0;
    string userString;
    while(true){
        cout << "1. Get information of encoded Reddit User ID" << endl;
        cout << "2. Get information of pixel coordinate" << endl;
        cout << "3. Get information of color type" << endl;
        cout << "4. Quit the program"  << endl;
        cout << "Enter number: " << endl;

        cin >> userChoice;

        switch (userChoice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                cout << "Quitting..." << endl;
                return 0;
        }
    }


    return 0;
}

