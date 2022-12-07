//
// Created by dylan on 11/24/2022.
//

#ifndef DSAPROJECT3_TREENODE_H
#define DSAPROJECT3_TREENODE_H

#include <iostream>
#include <vector>
#include <math.h>
#include "pixelUpdate.h"

using namespace std;

#include <iostream>
#include <vector>
#include <math.h>
#include "pixelUpdate.h"

using namespace std;

class hasherHelper{
public:

    unsigned long long hashValue;
    pixelUpdate* pixel = nullptr;

    hasherHelper operator= (unsigned long long temp){
        this->hashValue = temp;
        return *this;
    }

    hasherHelper operator= (hasherHelper temp){
        this->hashValue = temp.hashValue;
        this->pixel = temp.pixel;
        return *this;
    }

    bool operator> (hasherHelper temp){
        return (this->hashValue > temp.hashValue) ? true : false;
    }

    bool operator> (unsigned long long temp){
        return (this->hashValue > temp) ? true : false;
    }

    bool operator< (hasherHelper temp){
        return (this->hashValue < temp.hashValue) ? true : false;
    }

    bool operator< (unsigned long long temp){
        return (this->hashValue < temp) ? true : false;
    }

    bool operator== (hasherHelper temp){
        return (this->hashValue == temp.hashValue) ? true : false;
    }

    bool operator== (unsigned long long temp){
        return (this->hashValue == temp) ? true : false;
    }

};

class Node {
public:
    bool isLeaf;
    int nodeSize;
    pixelUpdate* pixelData;
    //vector<unsigned long long> hashKey;
    vector<hasherHelper> hashKey;
    vector<Node*> childPtr;
    //Node **childPtr;
    Node* parentNodePtr;
    Node* nextLeafPtr;
    //for inner nodes
    Node(int maxLeaves){
        //give one extra space for split cases
        hashKey.resize(maxLeaves+1);
        childPtr.resize(maxLeaves+2);
        isLeaf = false;
        for(int i=0; i<childPtr.size(); i++){
            childPtr.at(i) == nullptr;
        }
        parentNodePtr = nullptr;
        nextLeafPtr = nullptr;
    }
    //for leaf nodes
    Node(pixelUpdate* pixel, int maxLeaves){
        pixelData = pixel;
        hashKey.resize(maxLeaves+1);
        childPtr.resize(maxLeaves+2);
        //isLeaf = true;
        for(int i=0; i<childPtr.size(); i++){
            childPtr.at(i) = nullptr;
        }
        parentNodePtr = nullptr;
        nextLeafPtr = nullptr;
    }
};

#endif //DSAPROJECT3_TREENODE_H

