//
// Created by dylan on 11/24/2022.
//

//temp

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

class Node {
public:
    bool isLeaf;
    int nodeSize;
    pixelUpdate* pixelData;
    vector<unsigned long long> hashKey;
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
            childPtr.at(i) == nullptr;
        }
        parentNodePtr = nullptr;
        nextLeafPtr = nullptr;
    }
};

#endif //DSAPROJECT3_TREENODE_H

