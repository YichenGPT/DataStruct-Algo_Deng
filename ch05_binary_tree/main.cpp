//
//  main.cpp
//  DataStruct-Algo_Deng
//

#include <iostream>
#include "BinTree.h"
using namespace std;

int main() {
    BinTree<char> tree;

    BinNode<char>* A = tree.insertAsRoot('A');
    BinNode<char>* B = tree.insertAsLC(A, 'B');
    BinNode<char>* C = tree.insertAsRC(A, 'C');
    BinNode<char>* D = tree.insertAsLC(B, 'D');
    BinNode<char>* E = tree.insertAsRC(B, 'E');
    BinNode<char>* F = tree.insertAsLC(C, 'F');
    BinNode<char>* G = tree.insertAsRC(C, 'G');

    cout << "Pre Recursive: ";
    tree.travPre_R(tree.root());
    cout << endl;

    cout << "In Recursive: ";
    tree.travIn_R(tree.root());
    cout << endl;

    cout << "Post Recursive: ";
    tree.travPost_R(tree.root());
    cout << endl;

    cout << "Pre Iterative: ";
    tree.travPre_I(tree.root());
    cout << endl;

    cout << "In Iterative: ";
    tree.travIn_I(tree.root());
    cout << endl;

    cout << "Post Iterative: ";
    tree.travPost_I(tree.root());
    cout << endl;

    return 0;
}
