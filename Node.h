//
// Created by tdoga on 10/5/2023.
//

#ifndef UNTITLED13_NODE_H
#define UNTITLED13_NODE_H

#include <string>
using namespace std;
//simple node struct
struct Node{
    string name;
    string id;
    Node* left;
    Node* right;
    int height;
    Node(string _name, string _id) : name(_name), id(_id), left(nullptr), right(nullptr), height(1) {}
};

#endif //UNTITLED13_NODE_H
