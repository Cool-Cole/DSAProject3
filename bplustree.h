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
    vector<Node*> childPtr;
    //Node **childPtr;
    Node* parentNodePtr;
    Node* nextLeafPtr;
    Node(pixelUpdate* pixel){
        pixelData = pixel;
        hashKey.resize(maxLeaves-1);
        childPtr.resize(maxLeaves);
    }
    Node(){
        hashKey.resize(maxLeaves-1);
        childPtr.resize(maxLeaves);
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
        ptr->childPtr[j+1] = ptr->childPtr[j];
    }
    ptr->hashKey.at(i) = inputHashData;
    ptr->nodeSize++;
    ptr->childPtr[ptr->nodeSize] = ptr->childPtr[ptr->nodeSize - 1];
    ptr->childPtr[i+1] = nullptr;
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
        //find leaf nodes
        while (!nodePtr->isLeaf) {
            for (int i = 0; i < nodePtr->nodeSize; i++) {
                if (inputHashData < nodePtr->hashKey.at(i)) {
                    nodePtr = nodePtr->childPtr.at(i);
                    break;
                }
                // when it reaches end of array of nodes, continue searching down right tree
                if (i == nodePtr->nodeSize - 1) {
                    nodePtr = nodePtr->childPtr.at(i + 1);
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
            //need to add new nodes since splitNode node is full
            Node* splitNode = new Node(inputPixel);
            Node* tempNode;
            splitNode->hashKey = nodePtr->hashKey;
            splitNode->hashKey.resize(maxLeaves);
            splitNode->childPtr.resize(maxLeaves+1);
            splitNode->childPtr = nodePtr->childPtr;
            splitNode->nodeSize = nodePtr->nodeSize;
            //reuse existing function to add node
            insertToHashKeyVector(splitNode, inputHashData);
            vector<unsigned long long> tempVector = splitNode->hashKey;
            //check if split is needed
            while(nodePtr->parentNodePtr != nullptr && ((splitNode->isLeaf && splitNode->nodeSize>maxLeaves) || (!splitNode->isLeaf && splitNode->nodeSize>maxLeaves-1))){
                nodePtr->nodeSize = nodePtr->nodeSize / 2;
                if(nodePtr->isLeaf){
                    //splitNode->hashKey.resize(maxLeaves);
                    //splitNode->childPtr.resize(maxLeaves + 1);
                    splitNode->isLeaf = true;
                    nodePtr->nextLeafPtr = splitNode;
                }
                else{
                    //splitNode->hashKey.resize(maxLeaves - 1);
                    //splitNode->childPtr.resize(maxLeaves);
                    splitNode->isLeaf = false;
                }
                nodePtr->childPtr.at(nodePtr->nodeSize) = nullptr;
                //adjust splitNode data
                splitNode->childPtr.at(splitNode->nodeSize) = nodePtr->childPtr.at(maxLeaves);
                splitNode->nodeSize = splitNode->nodeSize - nodePtr->nodeSize;
                for (int i = nodePtr->nodeSize, j = 0; i < tempVector.size(); i++, j++) {
                    splitNode->hashKey.at(j) = tempVector.at(i);
                    splitNode->childPtr.at(j) = splitNode->childPtr.at(i);
                }
                splitNode->childPtr.at(splitNode->nodeSize) = splitNode->childPtr.at(tempVector.size()-1);
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                //
                nodePtr = nodePtr->parentNodePtr;
                tempNode = new Node();
                tempNode->hashKey = nodePtr->hashKey;
                tempNode->childPtr = nodePtr->childPtr;
                tempNode->hashKey.resize(maxLeaves);
                tempNode->childPtr.resize(maxLeaves+1);
                tempNode->nodeSize = nodePtr->nodeSize;
                insertToHashKeyVector(tempNode, splitNode->hashKey.at(0));
                splitNode = tempNode;
                tempVector = splitNode->hashKey;
            }
            if(nodePtr->parentNodePtr == nullptr){
                if(nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves){
                    //adjust left node
                    nodePtr->nodeSize = nodePtr->nodeSize / 2;
                    nodePtr->nextLeafPtr = splitNode;
                    Node* parentPtr = new Node();
                    nodePtr->parentNodePtr = parentPtr;
                    //split the node
                    splitNode->nodeSize = splitNode->nodeSize - nodePtr->nodeSize;
                    for (int i = nodePtr->nodeSize, j = 0; i < tempVector.size(); i++, j++) {
                        splitNode->hashKey.at(j) = tempVector.at(i);
                        splitNode->childPtr.at(j) = splitNode->childPtr.at(i);
                    }
                    splitNode->childPtr.at(splitNode->nodeSize) = splitNode->childPtr.at(tempVector.size()-1);
                    splitNode->parentNodePtr = nodePtr->parentNodePtr;
                    //set data to parent node
                    insertToHashKeyVector(parentPtr, splitNode->hashKey.at(0));
                    parentPtr->nodeSize = 1;
                    parentPtr->childPtr[0] = nodePtr;
                    parentPtr->childPtr[1] = splitNode;
                    //change root
                    root = parentPtr;
                }
                else{
                    //adjust left node
                    nodePtr->nodeSize = nodePtr->nodeSize / 2;
                    Node* parentPtr = new Node();
                    nodePtr->parentNodePtr = parentPtr;
                    //split the node
                    splitNode->nodeSize = splitNode->nodeSize - nodePtr->nodeSize - 1;
                    for (int i = nodePtr->nodeSize+1, j = 0; i < tempVector.size(); i++, j++) {
                        splitNode->hashKey.at(j) = tempVector.at(i);
                        splitNode->childPtr.at(j) = splitNode->childPtr.at(i);
                    }
                    splitNode->childPtr.at(splitNode->nodeSize) = splitNode->childPtr.at(tempVector.size()-1);
                    splitNode->parentNodePtr = nodePtr->parentNodePtr;
                    //set data to parent node
                    insertToHashKeyVector(parentPtr, splitNode->hashKey.at(nodePtr->nodeSize));
                    parentPtr->nodeSize = 1;
                    parentPtr->childPtr[0] = nodePtr;
                    parentPtr->childPtr[1] = splitNode;
                    //change root
                    root = parentPtr;
                }
            }
        }
    }
}



#endif //DSAPROJECT3_BPLUSTREE_H
