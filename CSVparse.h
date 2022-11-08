//
// Created by Cole on 11/3/2022.
//

#ifndef DSAPROJECT3_CSVPARSE_H
#define DSAPROJECT3_CSVPARSE_H

#include <vector>

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

#endif //DSAPROJECT3_CSVPARSE_H
