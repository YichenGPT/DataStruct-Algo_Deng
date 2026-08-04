//
//  main.cpp
//  DataStruct-Algo_Deng
//

#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    GraphMatrix<char, int> g;

    int A = g.insertVertex('A');
    int B = g.insertVertex('B');
    int C = g.insertVertex('C');
    int D = g.insertVertex('D');
    int E = g.insertVertex('E');

    g.insertEdge(1, 1, A, B);
    g.insertEdge(1, 1, A, C);
    g.insertEdge(1, 1, B, D);
    g.insertEdge(1, 1, C, D);
    g.insertEdge(1, 1, D, E);

    cout << "BFS: ";
    g.bfs(A);
    cout << endl;

    cout << "DFS: ";
    g.dfs(A);
    cout << endl;

    return 0;
}
