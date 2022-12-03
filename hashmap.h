//
// Created by Cole on 11/8/2022.
//

#ifndef DSAPROJECT3_HASHMAP_H
#define DSAPROJECT3_HASHMAP_H

#include <vector>
#include "pixelUpdate.h"

using namespace std;

class Hashmap {

    unsigned int nodeCount;
    unsigned int bucketCount;

    vector<vector<pixelUpdate*>> buckets;

public:

    Hashmap(){
        nodeCount = 0;
        bucketCount = 2000;

        buckets.resize(bucketCount);
    }

    void insert(pixelUpdate* temp){
        nodeCount++;

        buckets.at(hash(temp->pixelX, temp->pixelY)).push_back(temp);
    }

    unsigned int hash(unsigned int x, unsigned int y){
        return x ^ y;
    }

};

#endif //DSAPROJECT3_HASHMAP_H
