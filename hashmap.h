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
        bucketCount = 2000;

        buckets.resize(bucketCount);
    }

    void insert(pixelUpdate* temp){
        nodeCount++;

        if(keyType == CORD){
            buckets.at(hash(temp->pixelX, temp->pixelY)).push_back(temp);
        } else if(keyType == USERID) {

        } else if(keyType == COLOR) {

        }

    }

    unsigned int hash(unsigned int x, unsigned int y){
        return x ^ y;
    }

    unsigned int hash(string userID){
        return 0;
    }

    unsigned int hashColor(string color){
        return 0;
    }

};

#endif //DSAPROJECT3_HASHMAP_H
