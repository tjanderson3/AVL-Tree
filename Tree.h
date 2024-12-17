//
// Created by tdoga on 10/5/2023.
//

#ifndef UNTITLED13_TREE_H
#define UNTITLED13_TREE_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Node.h"
using namespace std;
//main avl tree class
class Tree{
private: //mainly helper functions
    Node* root;
    int getBalance(Node* node);
    int getHeight(Node* node);
    Node* insert(Node* node, string _id, string name);
    Node* rightRotation(Node* node);
    Node* leftRotation(Node* node);
    Node* idSearch(Node* node, string _id);
    void nameSearch(Node *node, string name, vector<string>& list);
    void preOrder(Node *node, vector<string>& list);
    void inOrder(Node* node, vector<string>& list);
    void postOrder(Node *node, vector<string>& list);
    void destructor(Node* node);
    Node* inOrderSuccessor(Node* node);
    Node* remove(Node* node, string _id);
    void removeInOrderHelp(Node* node, int N, int& pos);
    int countNodes(Node* node);
public: //called by user
    Tree();
    Tree(Node* _root);
    ~Tree();
    int getNodeCount();
    void printLevelCount();
    void userRemove(string id);
    void removeInOrder(int N);
    bool nameExists(string name);
    bool idExists(string id);
    void userInsert(string id, string name);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printName(string id);
};

Tree::Tree(){
    root = nullptr;
}
Tree::Tree(Node* _root){
    root = _root;
    root->height=1;
}
//constructors and destructors
void Tree::destructor(Node *node) {
    if(node == nullptr){
        return;
    }
    destructor(node->left);
    destructor(node->right);
    delete node;
}
Tree::~Tree() {
    destructor(root);
}
//node counter for in order removal
int Tree::countNodes(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    // Recursively count nodes in the left and right subtrees
    int leftCount = countNodes(node->left);
    int rightCount = countNodes(node->right);
    // Add 1 for the current node
    return 1 + leftCount + rightCount;
}
int Tree::getNodeCount() {
    return (countNodes(root));
}
//for level count
void Tree::printLevelCount() {
    if(root == nullptr){
        cout << 0 << endl;
    }
    cout << getHeight(root) << endl;
}
void Tree::userInsert(string id, string name) {
    root = insert(root, id, name);
}
void Tree::userRemove(string id) {
    root = remove(root, id);
}
void Tree::removeInOrder(int N) {
    int pos = 0;
    removeInOrderHelp(root, N, pos);
}//check if name exists and print accordingly
bool Tree::nameExists(string name) {
    if(root == nullptr){
        cout << "unsuccessful" << endl;
        return false;
    }
    vector<string> list;
    nameSearch(root, name, list);
    if(list.empty()){
        cout << "unsuccessful" << endl;
        return false;
    }
    else{
        for(const auto & i : list){
            cout << i << endl;
        }
        return true;
    }
}//check if id exists does not print
bool Tree::idExists(string id) {
    if(root == nullptr){
        return false;
    }
    Node* temp = idSearch(root, id);
    if(temp == nullptr){
        return false;
    }
    else{
        return true;
    }
}//this prints the name given id
void Tree::printName(string id){
    if(root == nullptr){
        return;
    }
    Node* temp = idSearch(root, id);
    if(temp == nullptr){
        return;
    }
    else{
        cout << temp->name << endl;
        return;
    }
}
//all print ...order functions use helpers that utilize pass by reference vectors
void Tree::printInOrder() {
    vector<string> list;
    inOrder(root, list);
    if(list.empty()){
        cout << endl;
    }
    else if((int)list.size() == 1){
        cout << list[0] << endl;
    }
    else{
        for(int i =0; i < (int)list.size()-1; i++){
            cout << list[i] << ", ";
        }
        cout << list[(int)list.size()-1] << endl;
    }
}
void Tree::printPreOrder(){
    vector<string> list;
    preOrder(root, list);
    if(list.empty()){
        cout << endl;
    }
    else if((int)list.size() == 1){
        cout << list[0] << endl;
    }
    else{
        for(int i =0; i < (int)list.size()-1; i++){
            cout << list[i] << ", ";
        }
        cout << list[(int)list.size()-1] << endl;
    }
}
void Tree::printPostOrder(){
    vector<string> list;
    postOrder(root, list);
    if(list.empty()){
        cout << endl;
    }
    else if((int)list.size() == 1){
        cout << list[0] << endl;
    }
    else{
        for(int i =0; i < (int)list.size()-1; i++){
            cout << list[i] << ", ";
        }
        cout << list[(int)list.size()-1] << endl;
    }
}
//for removal
Node* Tree::inOrderSuccessor(Node *node) {
    while(node->left != nullptr){
        node = node->left;
    }
    return node;
}

int Tree::getHeight(Node *node) {
    if(node==nullptr){
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (1+ max(leftHeight, rightHeight));
}
//updates height recursively, getbalance uses this
int Tree::getBalance(Node* node) {
    if(!node->left && !node->right){
        return 0;
    }
    else{
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return (leftHeight - rightHeight);
    }
}
//main insertion function
Node* Tree::insert(Node* node, string id, string name) {
    if(node == nullptr){
        return new Node(name, id);
    }
    //^ base case, once traveling through tree will eventually find a spot for insertion, followed by recursive calls
    else if(stoi(id) > stoi(node->id)){
        node->right = insert(node->right, id, name);
    }
    else{
        node->left = insert(node->left, id, name);
    }
    node->height = getHeight(node);
    //balance and update height
    if(getBalance(node) < -1){
        if(getBalance(node->right) < 0){
            node = leftRotation(node);
        }
        else{
            node = rightRotation(node);
            node = leftRotation(node);
        }
    }
    else if(getBalance(node) > 1){
        if(getBalance(node->left) > 0){
            node = rightRotation(node);
        }
        else{
            node = leftRotation(node);
            node = rightRotation(node);
        }
    }
    return node;
}
Node* Tree::remove(Node *node, string _id) {
    if(node == nullptr){
        return node;
    }
    //base case followed by main recursive calls
    if(stoi(_id) < stoi(node->id)){
        node->left = remove(node->left, _id);
    }
    else if(stoi(_id) > stoi(node->id)){
        node->right = remove(node->right, _id);
    }
    else{//one and no child cases
        if(node->left == nullptr){
            Node* temp = node->right;
            if(node == root){
                root = temp;
            }
            delete node;
            return temp;
        }
        else if(node->right == nullptr){
            Node* temp = node->left;
            if(node == root){
                root = temp;
            }
            delete node;
            return temp;
        }
        else{//two child case
            Node* temp = inOrderSuccessor(node->right);

            // Copy the inorder successor's content to this node
            node->id = temp->id;
            node->name = temp->name;

            // Delete the inorder successor
            node->right = remove(node->right, temp->id);
        }
    }
    node->height = getHeight(node);
    return node;
}
void Tree::removeInOrderHelp(Node *node, int N, int &pos) {
    if(node == nullptr){
        return;
    }
    removeInOrderHelp(node->left, N, pos);
    if(pos == N){
        userRemove(node->id);
    }
    pos++;
    removeInOrderHelp(node->right, N, pos);
}
//basic rotation  functions
Node* Tree::rightRotation(Node *node) {
    Node* newRoot = node->left;
    Node* grandChild = node->left->right;
    newRoot->right = node;
    node->left = grandChild;
    node->height = getHeight(node);
    newRoot->height = getHeight(newRoot);
    if(node == root){
        root = newRoot;
    }
    return newRoot;
}
Node* Tree::leftRotation(Node *node) {
    Node* newRoot = node->right;
    Node* grandChild = node->right->left;
    newRoot->left = node;
    node->right = grandChild;
    node->height = getHeight(node);
    newRoot->height = getHeight(newRoot);
    if(node == root){
        root = newRoot;
    }
    return newRoot;
}
Node* Tree::idSearch(Node *node, string _id) {
    if(node == nullptr || node->id == _id){
        return node;
    }
    else if(stoi(_id) < stoi(node->id)){
        return idSearch(node->left, _id);
    }
    else{
        return idSearch(node->right, _id);
    }
}//helper functions used for search
void Tree::nameSearch(Node *node, string name, vector<string>& list){
    if(node == nullptr){
        return;
    }
    if(node->name == name){
        list.push_back(node->id);
    }
    nameSearch(node->left, name, list);
    nameSearch(node->right, name, list);
}
void Tree::preOrder(Node *node, vector<string>& list) {
    if(node == nullptr){
        return;
    }
    list.push_back(node->name);
    preOrder(node->left, list);
    preOrder(node->right, list);
}
void Tree::inOrder(Node* node, vector<string>& list){
    if(node == nullptr){
        return;
    }
    inOrder(node->left, list);
    list.push_back(node->name);
    inOrder(node->right, list);
}
void Tree::postOrder(Node *node, vector<string> &list) {
    if(node == nullptr){
        return;
    }
    postOrder(node->left, list);
    postOrder(node->right, list);
    list.push_back(node->name);
}





#endif //UNTITLED13_TREE_H
