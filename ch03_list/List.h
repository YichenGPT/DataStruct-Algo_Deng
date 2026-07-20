//
//  List.h
//  DataStruct-Algo_Deng
//


#ifndef List_h
#define List_h

#include <iostream>

template <typename T>

// 双向链表 A <-> B

struct ListNode{
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;
    
    // 构造函数: 无参数方式创建节点
    ListNode() : pred(nullptr), succ(nullptr) {}
    
    // pred <- e -> succ
    ListNode(
             T const& e,
             ListNode<T>* p = nullptr,
             ListNode<T>* s = nullptr
             ) : data(e), pred(p), succ(s) {}
    
    // 前插(成员函数) pred <- e -> this
    ListNode<T>* insertAsPred(T const& e){
        ListNode<T>* node = new ListNode<T> (e, pred, this);
        
        pred->succ = node; // this->pred->succ
        pred = node; // this->pred = node; 成员变量可以省略 this->
        
        return node;
    }
    
    // 后插 this <- e -> succ
    ListNode<T>* insertAsSucc(T const& e){
        ListNode<T>* node = new ListNode<T>(e, this, succ);
        
        succ->pred = node; // this->succ->pred
        succ = node;
        
        return node;
    }
};

template <typename T>
class List{
private:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;
    
    void init(){
        header = new ListNode<T>;
        trailer = new ListNode<T>;
        
        header->succ = trailer;
        trailer->pred = header;
        
        _size = 0;
    }
    
public:
    List(){
        init();
    }
    
    int size() const {
        return _size;
    }
    
    bool empty() const {
        return _size == 0;
    }
    
    ListNode<T>* first() const {
        return header->succ;
    }
    
    ListNode<T>* last() const {
        return trailer->pred;
    }
    
    // 首插 & 尾插
    ListNode<T>* insertAsFirst(T const& e) {
        _size++;
        return header->insertAsSucc(e);
    }
    
    ListNode<T>* insertAsLast(T const& e) {
        _size++;
        return trailer->insertAsPred(e);
    }
    
    // 删除节点 pred <-> p <-> succ
    T remove(ListNode<T>* p){
        T e = p->data;
        
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        
        delete p;
        _size--;
        
        return e;
    }
    
    // 析构函数
    ~List() {
        while (_size > 0) {
            remove(header->succ);
        }
        delete header;
        delete trailer;
    }
    
    // 无序查找 (平均复杂度: O(n) )
    ListNode<T>* find(T const& e) const {
        ListNode<T>* p = trailer->pred;
        
        while(p != header){
            if(p->data == e){
                return p;
            }
            p = p->pred;
        }
        
        return nullptr;
    }
  
    // 有序查找( list 升序排列)
    // 返回不大于 e 的最靠右节点
    ListNode<T>* search(T const& e) const {
        ListNode<T>* p = trailer->pred;
        
        while(p != header && p->data > e){
            p = p->pred;
        }
        return p;
    }
    
    // 无序去重 (find_update() + deduplicate() )
    ListNode<T>* find_update(T const& e, int n, ListNode<T>* p) const {
        while (n-- > 0){
            p = p->pred;
            
            if(p->data == e) return p;
        }
        return nullptr;
    }
    // find(e) = find_update(e, _size, trailer)

    // 复杂度 O(n^2)
    // 每个循环 O(1) 内部对当前节点的检查不多于(i - 1)次: 1 + 2 + ... + (n-1) ~ O(n^2)
    int deduplicate(){
        if(_size < 2) return 0;
        
        int oldSize = _size;
        ListNode<T>* p = first();
        int r = 1;
        
        while((p = p->succ) != trailer){
            // 判断当前节点与前序节点有无重复
            ListNode<T>* q = find_update(p->data, r, p);
            
            if(q != nullptr){
                remove(q); // 删除前序中的重复着
            }else{
                r++; // 前序扩大
            }
        }
        
        return oldSize - _size;
    }
        
    // 有序去重 O(n)
    int uniquify(){
        if(_size < 2) return 0;
        
        int oldSize = _size;
        ListNode<T>* preserve = first();
        ListNode<T>* inspect;
        
        // 为 inspect 赋值; 防止 remove 导致的内存缺失
        while((inspect = preserve->succ) != trailer){
            // 循环内复杂度 O(1); 比较相邻两节点
            if(inspect->data == preserve->data){
                remove(inspect);
            }else{
                preserve = inspect;
            }
        }
        return oldSize - _size;
    }
        
    // 辅助函数 (修正 _size )
    ListNode<T>* insertAfter(ListNode<T>* p, T const& e) {
        _size++;
        return p->insertAsSucc(e);
    }
    
    ListNode<T>* insertBefore(ListNode<T>* p, T const& e) {
        _size++;
        return p->insertAsPred(e);
    }
    
    // 插入排序
    // 复杂度: 顺序(只进行外循环) ~ O(n); 逆序(算术级数) ~ O(n^2)
    void insertionSort(){
        if(_size < 2) return;
        
        ListNode<T>* current = first()->succ;
        
        while(current != trailer) {
            ListNode<T>* next = current->succ;
            ListNode<T>* position = current->pred;
            
            // 找到不大于 current 的最右侧节点
            while(position != header && position->data > current->data){
                position = position->pred;
            }
            
            if(position->succ != current){
                insertAfter(position, current->data);
                remove(current);
            }
            // current 被删, next 提前占位
            current = next;
        }
    }

    // 链表反转: 复杂度 O(n)
    // from: A <-> B <-> C to: C <-> B <-> A
    void reverse(){
        if(_size < 2) return;
        
        ListNode<T>* current = header;
        
        while(current != nullptr){
            ListNode<T>* next = current->succ;
            
            current->succ = current->pred;
            current->pred = next;
            
            current = next;
        }
        
        // 边界处理: header & trailer
        ListNode<T>* temp = header;
        header = trailer;
        trailer = temp;
    }
    
};


#endif /*List_h*/


