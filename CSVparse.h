//
// Created by Cole on 11/3/2022.
//

#ifndef DSAPROJECT3_CSVPARSE_H
#define DSAPROJECT3_CSVPARSE_H

#include <vector>
#include <thread>
#include "pixelUpdate.h"

using namespace std;

// This is a function I wrote to help parse strings
// I have been using it since programming 2
// This function takes a string and splits it into a vector of strings seperated by a delimiter
vector<string> stringToVector(string str, char delim){
    vector<string> ret;
    string temp;

    for(auto i = 0; i < str.size(); i++){
        if(str[i] != delim){
            temp += str[i];
        } else {
            ret.push_back(temp);
            temp.clear();
        }
    }

    ret.push_back(temp);

    return ret;
}

int timeInSecondsCalculator(string timeStr){
    int time = 0;

    time += (stoi(timeStr.substr(9,  9)) - 4) * 86400; //Days
    time += stoi(timeStr.substr(11,  12)) * 3600; //Hours
    time += stoi(timeStr.substr(14,  15)) * 60; //Minutes
    time += stoi(timeStr.substr(17,  18)); //Seconds

    return time;
}

void pixelUpdateLoader(){
    ifstream csv("./CSVData/2022_place_canvas_history.csv");

    string line;

    vector<pixelUpdate*> *pixelUpdatesRAW = new vector<pixelUpdate*>;

    //Throws out the titles from the original csv.
    getline(csv, line);

    while(getline(csv, line)){
        vector<string> pixelDataRAW = stringToVector(line, ',');

        /*
        for(auto it = pixelDataRAW.begin(); it != pixelDataRAW.end(); it++){
            cout << it->c_str() << endl;
        }
         */

        //Calculates how long in seconds it has been since the start.
        int timeSinceStart = timeInSecondsCalculator(pixelDataRAW.at(0));

        pixelDataRAW.at(3) = pixelDataRAW.at(3).substr(1, pixelDataRAW.at(3).size());
        pixelDataRAW.at(4) = pixelDataRAW.at(4).substr(0, pixelDataRAW.at(4).size() - 1);

        pixelUpdatesRAW->push_back(new pixelUpdate(pixelDataRAW.at(0), timeSinceStart, pixelDataRAW.at(1), pixelDataRAW.at(2), stoi(pixelDataRAW.at(3)), stoi(pixelDataRAW.at(4))));

    }

    //Call data structure creators here using pixelUpdatesRaw, which contains all of the pixel data in a single vector:

    //B+ Trees:


    //Hash Maps:

    cout << "done" << endl;
}

#endif //DSAPROJECT3_CSVPARSE_H
