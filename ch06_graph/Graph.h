//
//  Graph.h
//  DataStruct-Algo_Deng
//

#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 定义新类型 VStatus
enum VStatus{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
};

template <typename Tv>
struct Vertex{
    Tv data;
    VStatus status;
    int dTime;
    int fTime;
    int parent; // 父亲顶点下标
    
    int inDegree;
    int outDegree;
    
    Vertex(Tv const& d)
        : data(d),
          inDegree(0),
          outDegree(0),
          status(UNDISCOVERED),
          dTime(-1),
          fTime(-1),
          parent(-1) {}
};

template <typename Te>
struct Edge{
    Te data;
    int weight;
    
    Edge(Te const& d, int w)
    : data(d), weight(w) {}
};

template <typename Tv, typename Te>
class GraphMatrix{
private:
    vector<Vertex<Tv>> V; // 顶点表: V[0] = A; V[1] = B; ...
    
    /*
     Edge<Te>* - 指向 1 条边的指针(便于用 nullptr 表示不存在的边)
     vector<Edge<Te>*> - 邻接矩阵的 1 行 eg. E[i]
     vector<vector<Edge<Te>*>> - 二维邻接矩阵
     
     其中 E[i][j] 表示 顶点V[i]到V[j]的边
     */
    vector<vector<Edge<Te>*>> E;
    int n;
    int e;

public:
    GraphMatrix() : n(0), e(0) {}
    
    ~GraphMatrix(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                delete E[i][j];
            }
        }
    }
    
    int vertexCount() const{
        return n;
    }
    
    int edgeCount() const{
        return e;
    }
    
    bool exists(int i, int j) const{
        return 0 <= i && i < n && 0 <= j && j < n && E[i][j] != nullptr;
    }
    
    // 插入新顶点 & 邻接矩阵行、列均扩充
    int insertVertex(Tv const& data){
        for(int i = 0; i < n; i++){
            E[i].push_back(nullptr); // 每行最终列 + 1
        }
        
        n++;
        // 矩阵 E 加入 1 个新的 vector - 增加 1 行(n个nullptr)
        E.push_back(vector<Edge<Te>*>(n, nullptr));
        V.push_back(Vertex<Tv>(data));
        
        return n - 1;
    }
    
    void insertEdge(Te const& data, int weight, int i, int j){
        if(exists(i, j)) return;
        
        // 申请存放 Edge<Te> 的内存 & 调用 Edge(d, w) 函数
        E[i][j] = new Edge<Te>(data, weight);
        e++;
        
        V[i].outDegree++;
        V[j].inDegree++;
    }
    
    // O(n)
    int firstNbr(int i) const{
        return nextNbr(i, n);
    }
    
    // O(n)
    int nextNbr(int i, int j) const{
        // 跳出循环: j 不合法 or 边存在(不存在将持续循环)
        while(-1 < j && !exists(i, --j));
        return j;
    }
    
    void reset(){
        for(int i = 0; i < n; i++){
            V[i].status = UNDISCOVERED;
            V[i].dTime = -1;
            V[i].fTime = -1;
            V[i].parent = -1;
        }
    }
    
    // Breadth-First Search (全图ver)
    void bfs(int s){
        reset();
        
        int clock = 0;
        int v = s;
        
        do{
            if(V[v].status == UNDISCOVERED){
                BFS(v, clock);
            }
            v = (v + 1) % n;
        }while(v != s); // v == s 时: 所有顶点均已遍历
    }
    
    // Depth-First Search (全图ver)
    void dfs(int s){
        reset();
        
        int clock = 0;
        int v = s;
        
        do{
            if(V[v].status == UNDISCOVERED){
                DFS(v, clock);
            }
            v = (v + 1) % n;
        }while(v != s);
    }
    
private:
    // BFS (单个连通域ver)
    void BFS(int v, int& clock){
        queue<int> q;
        
        V[v].status = DISCOVERED;
        q.push(v);
        
        while(!q.empty()){
            int x = q.front();
            q.pop();
            
            V[x].dTime = ++clock;
            cout << V[x].data << "\t";
            
            for(int u = firstNbr(x); u > -1; u = nextNbr(x, u)){
                if(V[u].status == UNDISCOVERED){
                    V[u].status = DISCOVERED;
                    V[u].parent = x;
                    q.push(u);
                }
            }
            V[x].status = VISITED;
            V[x].fTime = ++clock;
        }
    }

    // DFS (递归ver)
    void DFS(int v, int& clock){
        V[v].status = DISCOVERED;
        V[v].dTime = ++clock;
        
        cout << V[v].data << "\t";
        
        for(int u = firstNbr(v); u > -1; u = nextNbr(v, u)){
            if(V[u].status == UNDISCOVERED){
                V[u].parent = v;
                DFS(u, clock);
            }
            
        }
        V[v].status = VISITED;
        V[v].fTime = ++clock;
    }

};


