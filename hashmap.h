//
// Created by Cole on 11/8/2022.
//

#ifndef DSAPROJECT3_HASHMAP_H
#define DSAPROJECT3_HASHMAP_H

#include <vector>
#include "pixelUpdate.h"

using namespace std;

enum flag {CORD, USERID, COLOR};

class Hashmap {

    unsigned int nodeCount;
    unsigned int bucketCount;

    flag keyType;


    vector<vector<pixelUpdate*>> buckets;

public:

    Hashmap(flag key){

        keyType = key;

        nodeCount = 0;

        if(key == CORD){
            bucketCount = 2000;
        } else if(key == USERID){
            bucketCount = 2000;
        } else if(key == COLOR){
            bucketCount = 16;
        }


        buckets.resize(bucketCount);
    }

    void insert(pixelUpdate* temp){
        nodeCount++;

        if(keyType == CORD){
            buckets.at(hash(temp->pixelX, temp->pixelY)).push_back(temp);
        } else if(keyType == USERID) {
            buckets.at(hash(temp->userID)).push_back(temp);
        } else if(keyType == COLOR) {

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
        return 0;
    }

};

#endif //DSAPROJECT3_HASHMAP_H
