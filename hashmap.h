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
        return nullptr;
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

    vector<pixelUpdate*> *getUserAll(string userID){
        if(keyType != USERID)
            return nullptr;
        unsigned int userHash = hash(userID);

        vector<pixelUpdate*> *result = new vector<pixelUpdate*>;

        for(auto iter : buckets.at(userHash)){
            if(iter->userID == userID)
                result->push_back(iter);
        }
        return result;
    }

    unsigned int getUserCount(string userID){
        if(keyType != USERID)
            return -1;
        unsigned int userHash = hash(userID);

        unsigned int result = 0;

        for(auto iter : buckets.at(userHash)){
            if(iter->userID == userID)
                result++;
        }
        return result;
    }

    unsigned int getColorCount(string color){
        return buckets.at(hashColor(color)).size();
    }

    void insert(pixelUpdate* temp){
        nodeCount++;

        if(keyType == CORD){
            buckets.at(hash(temp->coords)).push_back(temp);
        } else if(keyType == USERID) {
            buckets.at(hash(temp->userID)).push_back(temp);
        } else if(keyType == COLOR) {
            buckets.at(hashColor(temp->color)).push_back(temp);
        }

    }

    /*unsigned int hash(unsigned int x, unsigned int y){
        return (x ^ (y << 1)) % bucketCount;
    }*/

    vector<pixelUpdate*> *getPixelCoordAll(string pixelCoord){
        if(keyType != CORD)
            return nullptr;
        vector<pixelUpdate*> *result = new vector<pixelUpdate*>;

        unsigned int coordHash = hash(pixelCoord);

        for(auto iter : buckets.at(coordHash)){
            if(iter->coords == pixelCoord)
                result->push_back(iter);
        }
        return result;
    }

    unsigned int getPixelCoordCount(string pixelCoord){
        if(keyType != CORD)
            return -1;
        unsigned int result = 0;

        unsigned int coordHash = hash(pixelCoord);

        for(auto iter : buckets.at(coordHash)){
            if(iter->coords == pixelCoord)
                result++;
        }
        return result;
    }

    pixelUpdate *getPixelCoordFirst(string pixelCoord){
        if(keyType != CORD)
            return nullptr;

        unsigned int coordHash = hash(pixelCoord);

        for(auto iter : buckets.at(coordHash)){
            if(iter->coords == pixelCoord)
                return iter;
        }
        return nullptr;
    }

    pixelUpdate *getPixelCoordLast(string pixelCoord){
        if(keyType != CORD)
            return nullptr;

        unsigned int coordHash = hash(pixelCoord);

        pixelUpdate *tmp = nullptr;
        for(auto iter : buckets.at(coordHash)){
            if(iter->coords == pixelCoord)
                tmp = iter;
        }
        return tmp;
    }

    pixelUpdate *getPixelColorFirst(string pixelColor){
        if(keyType != COLOR)
            return nullptr;

        unsigned int coordHash = hashColor(pixelColor);

        for(auto iter : buckets.at(coordHash)){
            if(iter->color == pixelColor)
                return iter;
        }
        return nullptr;
    }

    pixelUpdate *getPixelColorLast(string pixelColor){
        if(keyType != COLOR)
            return nullptr;

        unsigned int coordHash = hashColor(pixelColor);

        pixelUpdate *tmp = nullptr;

        for(auto iter : buckets.at(coordHash)){
            if(iter->color == pixelColor)
                tmp = iter;
        }
        return tmp;
    }

    unsigned int getPixelColorCount(string pixelColor){
        //if(keyType != COLOR)
          //  return -1;
        unsigned int result = 0;

        unsigned int coordHash = hashColor(pixelColor);

        for(auto iter : buckets.at(coordHash)){
            if(iter->color == pixelColor)
                result++;
        }
        return result;
    }

    vector<pixelUpdate*> *getPixelColorAll(string pixelColor){
        //if(keyType != COLOR)
          //  return nullptr;
        vector<pixelUpdate*> *result = new vector<pixelUpdate*>;

        unsigned int coordHash = hashColor(pixelColor);

        for(auto iter : buckets.at(coordHash)){
            if(iter->color == pixelColor)
                result->push_back(iter);
        }
        return result;
    }

    unsigned int hash(string userID){

        int hash = 0;;

        int temp = userID.size();
        for(int i = 0; i < temp; i++){
            hash = 37*hash+userID.at(i);
        }

        if(hash < 0){
            hash += bucketCount;
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

    unsigned int getBucketSize(string key){
        if(keyType == COLOR){
            return buckets.at(hashColor(key)).size();
        } else if(keyType == USERID || keyType == CORD){
            return buckets.at(hash(key)).size();
        }
        return 0;
    }

};

#endif //DSAPROJECT3_HASHMAP_H
