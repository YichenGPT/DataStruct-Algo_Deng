//
//  GraphAlgorithms.h
//  DataStruct-Algo_Deng
//

#pragma once

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

namespace graphalgo{

inline constexpr int INF = numeric_limits<int>::max() / 4;

// prim 算法
/*
 1. 从树外选择 lowCost 最小的顶点 u
 2. 用新加入的 u 更新其他顶点的 lowCost
 */
inline int prim(const vector<vector<int>>& graph, int start){
    int n = static_cast<int>(graph.size());
    
    vector<int> lowCost(n, INF);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);
    
    /*
     inMST[v]: v 是否已经进入生成树
     lowCost[v]: v到当前生成树集合 U 的最小边权
     parent[v]: 这条最小边来自 U 中的哪个顶点
     */
    
    lowCost[start] = 0;
    int totalWeight = 0;
    
    for(int count = 0; count < n; count++){
        int u = -1;
        
        for(int v = 0; v < n; v++){
            if(!inMST[v] &&
               (u == -1 || lowCost[v] < llowCost[u])){
                u = v;
            }
        }
        
        if(u == -1 || lowCost[u] == INF){
            return -1;
        }
        
        inMST[u] = true;
        totalWeight += lowCost[u];
        
        if(parent[u] != -1){
            cout << parent[u] << " - " << u << " : " << lowCost[u] << '\n';
        }
        
        for(int v = 0; v < n; v++){
            if(!inMST[v] &&
               graph[u][v] < lowCost[v]){
                lowCost[v] = graph[u][v];
                parent[v] = u;
            }
        }
        
        return totalWeight;
    }
    
}
}





