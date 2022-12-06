//
// Created by Chase Hap on 11/2/22.
//

using namespace std;

#ifndef DSAPROJECT3_PIXELUPDATE_H
#define DSAPROJECT3_PIXELUPDATE_H

#include <string>

class pixelUpdate{
public:

    void printPixelUpdate(string mod = ""){
        cout << "Date and Time: " << dateTime << endl;
        if(mod != "userid")
            cout << "UserID responsible: " << userID << endl;
        if(mod != "color")
            cout << "Color: " << color << endl;
        if(mod != "coordinates")
            cout << "Coordinates: " << pixelX << ", " << pixelY << endl << endl;
    }

    //Primary Constructor
    pixelUpdate(string dateTime, unsigned int timeSinceStart, string userID, string color, int pixelX, int pixelY, string coords){
        this->dateTime = dateTime;
        this->timeSinceStart = timeSinceStart;
        this->userID = userID;
        this->color = color;
        this->pixelX = pixelX;
        this->pixelY = pixelY;
        this->coords = coords;
    }

    //Copy Constructor (Please use this to replicate elements when creating new datastructures!!!)
    pixelUpdate(const pixelUpdate *old){
        this->dateTime = old->dateTime;
        this->timeSinceStart = old->timeSinceStart;
        this->userID = old->userID;
        this->color = old->color;
        this->pixelX = old->pixelX;
        this->pixelY = old->pixelY;
    }

    // for testing b+ tree
    pixelUpdate(string userID){
        this->userID = userID;
    }

    unsigned int timeSinceStart, pixelX, pixelY;
    string userID, dateTime, color, coords;

};

#endif //DSAPROJECT3_PIXELUPDATE_H