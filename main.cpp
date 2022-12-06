#include <iostream>
#include "CSVparse.h"
#include "bplustree.h"
#include "hashmap.h"

using namespace std;

int main(int argc, char **argv) {

    // Sanity check to ensure that the user isn't just running this binary without arguments
    if(argc < 2){
        cout << "Please ensure that you are running ./project3 data.csv" << endl;
        return 0;
    }

    cout << "Loading the r/place data set into memory... (this might take a while)" << endl;

    vector<pixelUpdate*> rawPixelData;

    pixelUpdateLoader(rawPixelData, argv[1]); // Load the file information into the rawPixelData array

    vector<pixelUpdate*> copy = rawPixelData;

    cout << "The r/place data set has been successfully loaded into memory!" << endl;

    //Hashmaps and trees declared outside of if statements so that they persist through the menu.
    Hashmap cord_map(CORD);
    Hashmap userid_map(USERID);
    Hashmap color_map(COLOR);

    bplusTree userid_tree;
    bplusTree color_tree;
    bplusTree coordinate_tree;

    cout << "The r/place data set is being loaded into memory as a B+ Tree... (this might take a while)" << endl;
    for(auto it = copy.begin(); it != copy.end(); it++){
        userid_tree.insertID(*it);
        color_tree.insertColor(*it);
        coordinate_tree.insertCoordinates(*it);
    }
    cout << "The r/place data set has been successfully loaded as a B+ Tree!" << endl;

    cout << "The r/place data set is being loaded into memory as a hashmap..." << endl;

    for(auto it = rawPixelData.begin(); it != rawPixelData.end(); it++){
        cord_map.insert(*it);
        userid_map.insert(*it);
        color_map.insert(*it);
    }

    cout << "The r/place data set has been successfully loaded as a hashmap!" << endl;



    int userChoice = 0;
    string userString;
    while(true){
        cout << "1. Get information of encoded Reddit User ID" << endl;
        cout << "2. Get information of pixel coordinate" << endl;
        cout << "3. Get information of color type" << endl;
        cout << "4. Quit the program"  << endl;
        cout << "Enter number: " << endl;

        cin >> userChoice;
        string searchUserID;
        pixelUpdate *returnedPixelUpdate;
        vector<pixelUpdate> *returnedPixelUpdateList;

        switch (userChoice) {
            case 1: //When the user is providing a userID to search
                cout << "1. Get first pixel edit (coordinates and color)" << endl;
                cout << "2. Get last pixel edit (coordinates and color)" << endl;
                cout << "3. Get number of pixels edited" << endl;
                cout << "4. Print all edits made by this user" << endl;
                cout << "5. Go back" << endl;

                cin >> userChoice;
                if (userChoice == 1) {
                    cout << "Please enter the userID" << endl;
                    cin >> searchUserID;

                    returnedPixelUpdate = userid_map.getUserFirst(searchUserID);

                    if (returnedPixelUpdate == nullptr)
                        cout << "No results found" << endl;
                    else
                        returnedPixelUpdate->printPixelUpdate();
                }
                else if(userChoice == 2){
                    cout << "Please enter the userID" << endl;
                    cin >> searchUserID;

                    returnedPixelUpdate = userid_map.getUserLast(searchUserID);

                    if(returnedPixelUpdate == nullptr)
                        cout << "No results found" << endl;
                    else
                        returnedPixelUpdate->printPixelUpdate();
                }

                else if(userChoice == 3){}

                else if(userChoice == 4) {
                    cout << "Please enter the userID" << endl;
                    cin >> searchUserID;

                    returnedPixelUpdateList = userid_map.getUserAll(searchUserID);

                    if (returnedPixelUpdate == nullptr)
                        cout << "No results found" << endl;
                    else {

                        for (auto iter: *returnedPixelUpdateList)
                            iter.printPixelUpdate();
                    }
                }

                break;
            case 2:
                break;
            case 3:

                cout << "Enter color: " << endl;
                cin >> userString;

                cout << endl << "This color was placed " << color_map.getBucketSize(userString) << " times." << endl;

                returnedPixelUpdate = color_tree.search(userString);

                cout << "This color was first placed by " << returnedPixelUpdate->userID << endl;
                cout << "Coordinates: " << returnedPixelUpdate->coords << endl;

                break;
            case 4:
                cout << "Quitting..." << endl;
                return 0;
        }
    }
}

