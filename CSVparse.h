//
// Created by Cole on 11/3/2022.
//

#ifndef DSAPROJECT3_CSVPARSE_H
#define DSAPROJECT3_CSVPARSE_H

#include <vector>

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
    time += (stoi(timeStr, ));
}

void pixelUpdateLoader(){
    ifstream csv("./CSVData/example.csv");

    string line;

    while(getline(csv, line)){
        vector<string> pixelDataRAW = stringToVector(line, ',');

        for(auto it = pixelDataRAW.begin(); it != pixelDataRAW.end(); it++){
            cout << it->c_str() << endl;
        }

        int timeSinceStart = timeInSecondsCalculator(pixelDataRAW.at(0));

    }

}

#endif //DSAPROJECT3_CSVPARSE_H
