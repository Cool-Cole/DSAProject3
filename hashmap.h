//
// Created by Cole on 11/8/2022.
//

//temp

#ifndef DSAPROJECT3_HASHMAP_H
#define DSAPROJECT3_HASHMAP_H

#include <vector>
#include "pixelUpdate.h"

using namespace std;

enum flag {CORD, USERID, COLOR};

int getColorCountHashmap(string color){

}

class Hashmap {

    unsigned int nodeCount;
    unsigned int bucketCount;

    flag keyType;


    vector<vector<pixelUpdate*>> buckets;

public:

    Hashmap(flag key){

        keyType = key;

        nodeCount = 0;

        if(keyType == CORD){
            bucketCount = 2000;
        } else if(keyType == USERID){
            bucketCount = 2000;
        } else if(keyType == COLOR){
            bucketCount = 16;
        }

        buckets.resize(bucketCount);
    }

    pixelUpdate *getUserFirst(string userID){
        if(keyType != USERID)
            return nullptr;
        unsigned int userHash = hash(userID);

        for(auto iter : buckets.at(userHash)){
            if(iter->userID == userID)
                return iter;
        }
    }

    pixelUpdate *getUserLast(string userID){
        if(keyType != USERID)
            return nullptr;
        unsigned int userHash = hash(userID);

        pixelUpdate *tmp = nullptr;
        for(auto iter : buckets.at(userHash)){
            if(iter->userID == userID)
                tmp = iter;
        }

        return tmp;
    }

    unsigned int getColorCount(string color){
        return buckets.at(hashColor(color)).size();
    }

    void insert(pixelUpdate* temp){
        nodeCount++;

        if(keyType == CORD){
            buckets.at(hash(temp->pixelX, temp->pixelY)).push_back(temp);
        } else if(keyType == USERID) {
            buckets.at(hash(temp->userID)).push_back(temp);
        } else if(keyType == COLOR) {
            hashColor(temp->color);
        }

    }

    unsigned int hash(unsigned int x, unsigned int y){
        return (x ^ (y << 1)) % bucketCount;
    }

    unsigned int hash(string userID){

        unsigned int hash = 0;

        int temp = userID.size();
        for(int i = 0; i < temp; i++){
            hash += ((int)userID.at(i) << 3);
        }

        return hash % bucketCount;
    }

    unsigned int hashColor(string color){
        if(color == "#00CCC0"){
            return 0;
        } else if(color == "#94B3FF"){
            return 1;
        } else if(color == "#6A5CFF"){
            return 2;
        } else if(color == "#009EAA"){
            return 3;
        } else if(color == "#E4ABFF"){
            return 4;
        } else if(color == "#000000"){
            return 5;
        } else if(color == "#00756F"){
            return 6;
        } else if(color == "#00A368"){
            return 7;
        } else if(color == "#00CC78"){
            return 8;
        } else if(color == "#2450A4"){
            return 9;
        } else if(color == "#3690EA"){
            return 10;
        } else if(color == "#493AC1"){
            return 11;
        } else if(color == "#515252"){
            return 12;
        } else if(color == "#51E9F4"){
            return 13;
        } else if(color == "#6D001A"){
            return 14;
        }

         else {
            cout << "Unknown color: " + color << endl;
            exit(1);
        }
    }

};

#endif //DSAPROJECT3_HASHMAP_H
