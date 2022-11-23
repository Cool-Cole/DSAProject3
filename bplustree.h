//
// Created by dylan on 11/21/2022.
//

#include <iostream>
#include <vector>
#include "pixelUpdate.h"

using namespace std;
int maxLeaves = 5;

#ifndef DSAPROJECT3_BPLUSTREE_H
#define DSAPROJECT3_BPLUSTREE_H

class Node {
public:
    bool isLeaf;
    int nodeSize;
    pixelUpdate* pixelData;
    vector<unsigned long long> hashKey;
    Node **childPtr;
    Node(pixelUpdate* pixel){
        pixelData = pixel;
        hashKey.resize(maxLeaves-1);
        childPtr = new Node *[maxLeaves];
    }
};

class bplusTree {
    Node* root;
    void insertToHashKeyVector(Node* ptr, unsigned long long inputHashData);

public:
    bplusTree();
    void insert(pixelUpdate* pixel);
    void search(pixelUpdate* pixel);
};

void bplusTree::insertToHashKeyVector(Node* ptr, unsigned long long inputHashData){
    int i = 0;
    while (inputHashData > ptr->hashKey.at(i) && i < ptr->nodeSize)
        i++;
    for (int j = ptr->nodeSize; j > i; j--) {
        ptr->hashKey.at(j) = ptr->hashKey.at(j-1);
    }
    ptr->hashKey.at(i) = inputHashData;
    ptr->nodeSize++;
    ptr->childPtr[ptr->nodeSize] = ptr->childPtr[ptr->nodeSize - 1];
    ptr->childPtr[ptr->nodeSize - 1] = nullptr;
}

void bplusTree::insert(pixelUpdate* inputPixel) {
    hash<string> hasher;
    unsigned long long inputHashData = hasher(inputPixel->userID);
    if (root == nullptr) {
        //initialize data nodes
        root = new Node(inputPixel);
        root->isLeaf = true;
        root->nodeSize = 1;
        root->hashKey.at(0) = inputHashData;
    }
    else {
        Node* nodePtr = root;
        Node* parentNodePtr;
        //find leaf nodes
        while (!nodePtr->isLeaf) {
            parentNodePtr = nodePtr;
            for (int i = 0; i < nodePtr->nodeSize; i++) {
                if (inputHashData < nodePtr->hashKey.at(i)) {
                    nodePtr = nodePtr->childPtr[i];
                    break;
                }
                // when it reaches end of array of nodes, x will be added to the end
                if (i == nodePtr->nodeSize - 1) {
                    nodePtr = nodePtr->childPtr[i + 1];
                    break;
                }
            }
        }
        // insert directly if there is still space at leaf node
        if (nodePtr->nodeSize < maxLeaves) {
            //insert input data to the sorted key place
            insertToHashKeyVector(nodePtr,inputHashData);
        }
        else{
            //need to add new nodes since leaf node is full
            Node* leaf = new Node(inputPixel);
            leaf->hashKey = nodePtr->hashKey;
            leaf->hashKey.resize(maxLeaves);
            //reuse existing function to add node
            insertToHashKeyVector(leaf,inputHashData);
            vector<unsigned long long> tempVector = leaf->hashKey;
            leaf->hashKey.resize(maxLeaves-1);
            nodePtr->nodeSize = maxLeaves / 2;
            leaf->nodeSize =  maxLeaves - nodePtr->nodeSize;
            nodePtr->childPtr[nodePtr->nodeSize] = leaf;
            leaf->childPtr[leaf->nodeSize] = nodePtr->childPtr[maxLeaves];
            nodePtr->childPtr[maxLeaves] = nullptr;
            leaf->isLeaf = true;
            //work in progress need to split the node somehow
        }
    }
}



#endif //DSAPROJECT3_BPLUSTREE_H
