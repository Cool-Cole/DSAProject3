//
// Created by Chase Hap on 11/2/22.
//

using namespace std;

#ifndef DSAPROJECT3_PIXELUPDATE_H
#define DSAPROJECT3_PIXELUPDATE_H

#include <string>

class pixelUpdate{
public:

    //Primary Constructor
    pixelUpdate(string dateTime, unsigned int timeSinceStart, string userID, string color, int pixelX, int pixelY){
        this->dateTime = dateTime;
        this->timeSinceStart = timeSinceStart;
        this->userID = userID;
        this->color = color;
        this->pixelX = pixelX;
        this->pixelY = pixelY;
    }

    //Copy Constructor (Please use this to replicate elements when creating new datastructures!!!)
    pixelUpdate(const pixelUpdate *old){
        this->dateTime = old->dateTime;
        this->timeSinceStart = old->timeSinceStart;
        this->userID = old->userID;
        this->color = old->color;
        this->pixelX = old->pixelX;
        this->pixelY = old->pixelY;
        //this->next = old->next;
    }

    // for testing b+ tree
    pixelUpdate(string userID){
        this->userID = userID;
    }

    unsigned int timeSinceStart, pixelX, pixelY;
    string userID, dateTime, color;

    //pixelUpdate *next = nullptr;

};

#endif //DSAPROJECT3_PIXELUPDATE_H
