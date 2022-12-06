//
// Created by dylan on 11/21/2022.
//

#ifndef DSAPROJECT3_BPLUSTREE_H
#define DSAPROJECT3_BPLUSTREE_H

#include <iostream>
#include <vector>
//#include <math.h>
#include "pixelUpdate.h"
#include "treeNode.h"

using namespace std;

//#ifndef DSAPROJECT3_BPLUSTREE_H
//#define DSAPROJECT3_BPLUSTREE_H

class bplusTree {
    Node* root = nullptr;
    int maxLeaves;
    void insertLeafNode(Node* ptr, unsigned long long inputHashData);
    void insertInnerNode(Node* ptr, hasherHelper inputHashData, Node* rightChild);

public:
    bplusTree();
    //~bplusTree();
    void insertID(pixelUpdate* pixel);
    void insertColor(pixelUpdate* pixel);
    void insertCoordinates(pixelUpdate* pixel);
    pixelUpdate* search(string searchData);
    void printbplusTree(Node* root);
    Node* getRoot();
};

bplusTree::bplusTree() {
    maxLeaves = 4;
}

void bplusTree::insertLeafNode(Node* ptr, unsigned long long inputHashData){
    int i = 0;
    while (i < ptr->nodeSize && ptr->hashKey.at(i) < inputHashData )
        i++;
    for (int j = ptr->nodeSize; j > i; j--) {
        ptr->hashKey.at(j) = ptr->hashKey.at(j-1);
    }
    ptr->hashKey.at(i) = inputHashData;
    ptr->nodeSize++;
}

void bplusTree::insertInnerNode(Node* ptr, hasherHelper inputHashData, Node* rightChild){
    int i = 0;
    while (i < ptr->nodeSize && inputHashData > ptr->hashKey.at(i))
        i++;
    for (int j = ptr->nodeSize; j > i; j--) {
        ptr->hashKey.at(j) = ptr->hashKey.at(j-1);
        ptr->childPtr[j+1] = ptr->childPtr[j];
    }
    ptr->hashKey.at(i) = inputHashData;
    ptr->nodeSize++;
    ptr->childPtr[i+1] = rightChild;
}

void bplusTree::insertID(pixelUpdate* pixel) {
    hash<string> hasher;
    unsigned long long inputHashData = hasher(pixel->userID);
    // for input is smaller int string, no hash
    //unsigned long long inputHashData = stoll(pixel->userID); // for testing
    // for debug
    /*if(inputHashData == 32){
        cout << "debug point" << endl;
    }*/
    if (root == nullptr) {
        //initialize data nodes
        root = new Node(pixel, maxLeaves);
        root->isLeaf = true;
        root->nodeSize = 1;
        root->hashKey.at(0) = inputHashData;
        root->hashKey.at(0).pixel = pixel;
    }
    else {
        Node* nodePtr = root;
        //find leaf nodes
        while (!nodePtr->isLeaf) {
            for (int i = 0; i < nodePtr->nodeSize; i++) {
                if (nodePtr->hashKey.at(i) > inputHashData) {
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
        //insert input data to the sorted key place
        insertLeafNode(nodePtr, inputHashData);
        //check if need to split nodeptr nodes if over the limit
        while((nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves) || (!nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves-1)) {
            if (nodePtr->isLeaf) {
                //handle split node
                Node *splitNode = new Node(pixel, maxLeaves);
                int splitIndex = maxLeaves / 2;
                splitNode->nodeSize = nodePtr->nodeSize - splitIndex;
                for (int i = splitIndex, j = 0; i < nodePtr->nodeSize; i++, j++) {
                    splitNode->hashKey.at(j) = nodePtr->hashKey.at(i);
                }
                splitNode->isLeaf = true;
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                // set nodeptr, links the leaf nodes together
                nodePtr->nextLeafPtr = splitNode;
                nodePtr->nodeSize = splitIndex;
                // handles parent
                if (nodePtr->parentNodePtr == nullptr) {
                    Node *newParent = new Node(maxLeaves);
                    newParent->hashKey.at(0) = splitNode->hashKey.at(0);
                    newParent->nodeSize = 1;
                    newParent->childPtr.at(0) = nodePtr;
                    newParent->childPtr.at(1) = splitNode;
                    newParent->isLeaf = false;
                    nodePtr->parentNodePtr = newParent;
                    splitNode->parentNodePtr = newParent;
                    root = newParent;
                } else {
                    insertInnerNode(nodePtr->parentNodePtr, splitNode->hashKey.at(0), splitNode);
                }
            }
                // else split non leaf node
            else {
                Node *splitNode = new Node(maxLeaves);
                int splitIndex = (maxLeaves - 1) / 2;
                splitNode->nodeSize = nodePtr->nodeSize - splitIndex - 1;
                for (int i = splitIndex + 1, j = 0; i < nodePtr->nodeSize; i++, j++) {
                    splitNode->hashKey.at(j) = nodePtr->hashKey.at(i);
                    splitNode->childPtr.at(j) = nodePtr->childPtr.at(i);
                }
                splitNode->childPtr.at(splitNode->nodeSize) = nodePtr->childPtr.at(nodePtr->nodeSize);
                //nodeptr resized to new left node size
                nodePtr->nodeSize = splitIndex;
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                // handles parent
                if (nodePtr->parentNodePtr == nullptr) {
                    Node *newParent = new Node(maxLeaves);
                    newParent->hashKey.at(0) = nodePtr->hashKey.at(splitIndex);
                    newParent->nodeSize = 1;
                    newParent->childPtr.at(0) = nodePtr;
                    newParent->childPtr.at(1) = splitNode;
                    nodePtr->parentNodePtr = newParent;
                    splitNode->parentNodePtr = newParent;
                    root = newParent;
                } else {
                    insertInnerNode(nodePtr->parentNodePtr, nodePtr->hashKey.at(splitIndex), splitNode);
                }
            }
            nodePtr = nodePtr->parentNodePtr;
        }
    }
}

//return root
Node* bplusTree::getRoot(){
    return root;
}

// Print the tree
void bplusTree::printbplusTree(Node* root) {
    Node* ptr = root;
    if (ptr != nullptr) {
        if(ptr->isLeaf){
            cout << "isLeaf = true" << endl;
        }
        else {
            cout << "isLeaf = false" << endl;
        }
        for (int i = 0; i < ptr->nodeSize; i++) {
            cout << ptr->hashKey.at(i).hashValue << " ";
        }
        cout << endl;
        if (!ptr->isLeaf) {
            for (int i = 0; i < ptr->nodeSize + 1; i++) {
                printbplusTree(ptr->childPtr.at(i));
            }
        }
    }
}

void bplusTree::insertColor(pixelUpdate* pixel) {
    hash<string> hasher;

    unsigned long long inputHashData = hasher(pixel->color);
    // for input is smaller int string, no hash
    //unsigned long long inputHashData = stoll(pixel->userID); // for testing
    // for debug
    /*if(inputHashData == 32){
        cout << "debug point" << endl;
    }*/
    if (root == nullptr) {
        //initialize data nodes
        root = new Node(pixel, maxLeaves);
        root->isLeaf = true;
        root->nodeSize = 1;
        root->hashKey.at(0) = inputHashData;
        root->hashKey.at(0).pixel = pixel;

    }
    else {
        Node* nodePtr = root;
        //find leaf nodes
        while (!nodePtr->isLeaf) {
            for (int i = 0; i < nodePtr->nodeSize; i++) {
                if (nodePtr->hashKey.at(i) > inputHashData) {
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
        //insert input data to the sorted key place
        insertLeafNode(nodePtr, inputHashData);
        //check if need to split nodeptr nodes if over the limit
        while((nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves) || (!nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves-1)) {
            if (nodePtr->isLeaf) {
                //handle split node
                Node *splitNode = new Node(pixel, maxLeaves);
                int splitIndex = maxLeaves / 2;
                splitNode->nodeSize = nodePtr->nodeSize - splitIndex;
                for (int i = splitIndex, j = 0; i < nodePtr->nodeSize; i++, j++) {
                    splitNode->hashKey.at(j) = nodePtr->hashKey.at(i);
                }
                splitNode->isLeaf = true;
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                // set nodeptr, links the leaf nodes together
                nodePtr->nextLeafPtr = splitNode;
                nodePtr->nodeSize = splitIndex;
                // handles parent
                if (nodePtr->parentNodePtr == nullptr) {
                    Node *newParent = new Node(maxLeaves);
                    newParent->hashKey.at(0) = splitNode->hashKey.at(0);
                    newParent->nodeSize = 1;
                    newParent->childPtr.at(0) = nodePtr;
                    newParent->childPtr.at(1) = splitNode;
                    newParent->isLeaf = false;
                    nodePtr->parentNodePtr = newParent;
                    splitNode->parentNodePtr = newParent;
                    root = newParent;
                } else {
                    insertInnerNode(nodePtr->parentNodePtr, splitNode->hashKey.at(0), splitNode);
                }
            }
                // else split non leaf node
            else {
                Node *splitNode = new Node(maxLeaves);
                int splitIndex = (maxLeaves - 1) / 2;
                splitNode->nodeSize = nodePtr->nodeSize - splitIndex - 1;
                for (int i = splitIndex + 1, j = 0; i < nodePtr->nodeSize; i++, j++) {
                    splitNode->hashKey.at(j) = nodePtr->hashKey.at(i);
                    splitNode->childPtr.at(j) = nodePtr->childPtr.at(i);
                }
                splitNode->childPtr.at(splitNode->nodeSize) = nodePtr->childPtr.at(nodePtr->nodeSize);
                //nodeptr resized to new left node size
                nodePtr->nodeSize = splitIndex;
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                // handles parent
                if (nodePtr->parentNodePtr == nullptr) {
                    Node *newParent = new Node(maxLeaves);
                    newParent->hashKey.at(0) = nodePtr->hashKey.at(splitIndex);
                    newParent->nodeSize = 1;
                    newParent->childPtr.at(0) = nodePtr;
                    newParent->childPtr.at(1) = splitNode;
                    nodePtr->parentNodePtr = newParent;
                    splitNode->parentNodePtr = newParent;
                    root = newParent;
                } else {
                    insertInnerNode(nodePtr->parentNodePtr, nodePtr->hashKey.at(splitIndex), splitNode);
                }
            }
            nodePtr = nodePtr->parentNodePtr;
        }
    }
}

void bplusTree::insertCoordinates(pixelUpdate* pixel) {
    hash<string> hasher;
    unsigned long long inputHashData = hasher(pixel->coords);
    // for input is smaller int string, no hash
    //unsigned long long inputHashData = stoll(pixel->userID); // for testing
    // for debug
    /*if(inputHashData == 32){
        cout << "debug point" << endl;
    }*/
    if (root == nullptr) {
        //initialize data nodes
        root = new Node(pixel, maxLeaves);
        root->isLeaf = true;
        root->nodeSize = 1;
        root->hashKey.at(0) = inputHashData;
        root->hashKey.at(0).pixel = pixel;
    }
    else {
        Node* nodePtr = root;
        //find leaf nodes
        while (!nodePtr->isLeaf) {
            for (int i = 0; i < nodePtr->nodeSize; i++) {
                if (nodePtr->hashKey.at(i) > inputHashData) {
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
        //insert input data to the sorted key place
        insertLeafNode(nodePtr, inputHashData);
        //check if need to split nodeptr nodes if over the limit
        while((nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves) || (!nodePtr->isLeaf && nodePtr->nodeSize>maxLeaves-1)) {
            if (nodePtr->isLeaf) {
                //handle split node
                Node *splitNode = new Node(pixel, maxLeaves);
                int splitIndex = maxLeaves / 2;
                splitNode->nodeSize = nodePtr->nodeSize - splitIndex;
                for (int i = splitIndex, j = 0; i < nodePtr->nodeSize; i++, j++) {
                    splitNode->hashKey.at(j) = nodePtr->hashKey.at(i);
                }
                splitNode->isLeaf = true;
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                // set nodeptr, links the leaf nodes together
                nodePtr->nextLeafPtr = splitNode;
                nodePtr->nodeSize = splitIndex;
                // handles parent
                if (nodePtr->parentNodePtr == nullptr) {
                    Node *newParent = new Node(maxLeaves);
                    newParent->hashKey.at(0) = splitNode->hashKey.at(0);
                    newParent->nodeSize = 1;
                    newParent->childPtr.at(0) = nodePtr;
                    newParent->childPtr.at(1) = splitNode;
                    newParent->isLeaf = false;
                    nodePtr->parentNodePtr = newParent;
                    splitNode->parentNodePtr = newParent;
                    root = newParent;
                } else {
                    insertInnerNode(nodePtr->parentNodePtr, splitNode->hashKey.at(0), splitNode);
                }
            }
                // else split non leaf node
            else {
                Node *splitNode = new Node(maxLeaves);
                int splitIndex = (maxLeaves - 1) / 2;
                splitNode->nodeSize = nodePtr->nodeSize - splitIndex - 1;
                for (int i = splitIndex + 1, j = 0; i < nodePtr->nodeSize; i++, j++) {
                    splitNode->hashKey.at(j) = nodePtr->hashKey.at(i);
                    splitNode->childPtr.at(j) = nodePtr->childPtr.at(i);
                }
                splitNode->childPtr.at(splitNode->nodeSize) = nodePtr->childPtr.at(nodePtr->nodeSize);
                //nodeptr resized to new left node size
                nodePtr->nodeSize = splitIndex;
                splitNode->parentNodePtr = nodePtr->parentNodePtr;
                // handles parent
                if (nodePtr->parentNodePtr == nullptr) {
                    Node *newParent = new Node(maxLeaves);
                    newParent->hashKey.at(0) = nodePtr->hashKey.at(splitIndex);
                    newParent->nodeSize = 1;
                    newParent->childPtr.at(0) = nodePtr;
                    newParent->childPtr.at(1) = splitNode;
                    nodePtr->parentNodePtr = newParent;
                    splitNode->parentNodePtr = newParent;
                    root = newParent;
                } else {
                    insertInnerNode(nodePtr->parentNodePtr, nodePtr->hashKey.at(splitIndex), splitNode);
                }
            }
            nodePtr = nodePtr->parentNodePtr;
        }
    }
}

pixelUpdate* bplusTree::search(string searchData) {;
    bool found = false;
    Node* nodePtr = root;
    hash<string> hasher;
    unsigned long long searchHashData = hasher(searchData);
    //unsigned long long searchHashData = stoll(searchData);
    while (!nodePtr->isLeaf) {
        for (int i = 0; i < nodePtr->nodeSize; i++) {
            if (nodePtr->hashKey.at(i) > searchHashData) {
                nodePtr = nodePtr->childPtr.at(i);
                break;
            }
            if (i == nodePtr->nodeSize - 1) {
                nodePtr = nodePtr->childPtr.at(i + 1);
                break;
            }
        }
    }
    for (int i = 0; i < nodePtr->nodeSize; i++) {
        if(nodePtr->hashKey.at(i) == searchHashData){
            return nodePtr->hashKey.at(i).pixel; // added this here so that we can look at what it finds
            //found = true;
            //break;
        }
    }/*
    if(found){
        cout << "User ID found " << endl;
    }
    else{
        cout << "No ID found" << endl;
    }*/
    return nullptr;
}
#endif //DSAPROJECT3_BPLUSTREE_H
