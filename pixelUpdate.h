//
// Created by Chase Hap on 11/2/22.
//

using namespace std;

#ifndef DSAPROJECT3_PIXELUPDATE_H
#define DSAPROJECT3_PIXELUPDATE_H

class pixelUpdate{
public:
    pixelUpdate(string date){
    }

    int dateTime, pixelX, pixelY;
    string userID;

    pixelUpdate *next = nullptr;
};

#endif //DSAPROJECT3_PIXELUPDATE_H
