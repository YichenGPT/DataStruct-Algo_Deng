//
//  BinTree.h
//  DataStruct-Algo_Deng
//

#pragma once

#include <iostream>
#include <stack>
using namespace std;

template <typename T>
struct BinNode{
    T data;
    BinNode<T>* parent;
    BinNode<T>* lc;
    BinNode<T>* rc;

    BinNode(
    T const& e, BinNode<T>* p = nullptr, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr
            ): data(e), parent(p), lc(l), rc(r) {}

    // 作为左孩子插入
    BinNode<T>* insertAsLC(T const& e){
        this->lc = new BinNode<T>(e, this); // 开辟 BinNode<T> 类型内存 + 调用 BinNode() 函数
        return this->lc;
    }

    // 作为右孩子插入(this 可省略)
    BinNode<T>* insertAsRC(T const& e){
        this->rc = new BinNode<T>(e, this);
        return this->rc;
    }
};


template <typename T>
class BinTree{
private:
    int _size;
    BinNode<T>* _root;

    // 递归释放整棵子树
    void release(BinNode<T>* x){
        if(x == nullptr) return;

        release(x->lc);
        release(x->rc);

        delete x;
    }

public:
    BinTree(): _size(0), _root(nullptr) {}

    ~BinTree() {
        release(_root);
    }

    int size() const{ return _size; }

    bool empty() const{ return _root == nullptr; }

    BinNode<T>* root() const{ return _root; }

    // 插入根节点
    BinNode<T>* insertAsRoot(T const& e){
        _size = 1;
        _root = new BinNode<T>(e);
        return _root;
    }

    // 插入左孩子
    BinNode<T>* insertAsLC(BinNode<T>* x, T const& e){
        _size++;
        return x->insertAsLC(e);
    }

    // 插入右孩子
    BinNode<T>* insertAsRC(BinNode<T>* x, T const& e){
        _size++;
        return x->insertAsRC(e);
    }

    // 1. 先序遍历 (递归ver) - 时间复杂度: O(n); 空间复杂度: O(h)
    void travPre_R(BinNode<T>* x) const{
        if(x == nullptr) return;

        cout << x->data << "\t";
        travPre_R(x->lc);
        travPre_R(x->rc);
    }

    // 2. 中序遍历 (递归ver)
    void travIn_R(BinNode<T>* x) const{
        if(x == nullptr) return;

        travIn_R(x->lc);
        cout << x->data << "\t";
        travIn_R(x->rc);
    }

    // 3. 后序遍历 (递归ver)
    void travPost_R(BinNode<T>* x) const{
        if(x == nullptr) return;

        travPost_R(x->lc);
        travPost_R(x->rc);
        cout << x->data << "\t";
    }

    // 4. 先序遍历 (迭代ver)
    void travPre_I(BinNode<T>* x) const{
        stack< BinNode<T>* > s;

        if(x != nullptr) s.push(x);

        while(!s.empty()){
            x = s.top();
            s.pop(); // void pop();

            cout << x->data << "\t";

            // First In Last Out
            if(x->rc != nullptr) s.push(x->rc);
            if(x->lc != nullptr) s.push(x->lc);
        }
    }

    // 5. 中序遍历 (迭代ver)
    void travIn_I(BinNode<T>* x) const{
        stack< BinNode<T>* > s;

        while(x != nullptr || !s.empty()){
            while(x != nullptr){
                s.push(x);
                x = x->lc;
            }

            x = s.top();
            s.pop();
            cout << x->data << "\t";
            x = x->rc;
        }
    }

    // 6. 后序遍历 (迭代ver)
    void travPost_I(BinNode<T>* x) const{
        stack< BinNode<T>* > s;
        BinNode<T>* lastVisited = nullptr;

        while(x != nullptr || !s.empty()){
            if(x != nullptr){
                s.push(x);
                x = x->lc;
            } else {
                BinNode<T>* node = s.top();
                if(node->rc != nullptr && lastVisited != node->rc){
                    x = node->rc;
                } else {
                    cout << node->data << "\t";
                    lastVisited = node;
                    s.pop();
                }
            }
        }
    }
};
