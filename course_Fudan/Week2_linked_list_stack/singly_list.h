#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>

namespace fudan_ds::lec03 {

struct Node {
    int data;
    Node* next;
};

using LinkList = Node*;

inline bool initList(LinkList& list) {
    list = new Node{0, nullptr};
    return true;
}

// 判断含哨兵节点的单链表是否为空
inline bool empty(LinkList list) {
    assert(list != nullptr);    // 确认 list 为哨兵节点
    return list->next == nullptr;
}

// "头插法" 创建链表; O(1)
inline void pushFront(LinkList list, int value) {
    assert(list != nullptr);
    
    LinkList p = new Node;
    p->data = value;
    
    p->next = list->next;
    list->next = p;
}

// "尾插法" 创建链表; O(n)
inline void pushBack(LinkList list, int value) {
    assert(list != nullptr);
    LinkList tail = list;
    while(tail->next != nullptr){
        tail = tail->next;
    }
    
    LinkList p = new Node{value, nullptr};
    tail->next = p;
}

// 删除第 1 个节点, 并把被删掉的数据存入 removed; O(1)
inline bool popFront(LinkList list, int& removed) {
    assert(list != nullptr);
    
    if(list->next == nullptr) return false;
    
    LinkList to_remove = list->next;
    removed = to_remove->data;
    list->next = to_remove->next;
    
    delete to_remove; return true;
}

// O(n)
inline std::size_t size(LinkList list) {
    assert(list != nullptr);

    std::size_t result = 0;
    for (Node* current = list->next; current != nullptr; current = current->next) {
        ++result;
    }
    return result;
}

// O(n)
inline void printList(LinkList list, std::ostream& out = std::cout) {
    assert(list != nullptr);

    out << '[';
    for (Node* current = list->next; current != nullptr; current = current->next) {
        out << current->data;
        if (current->next != nullptr) {
            out << ", ";
        }
    }
    out << ']';
}

// O(n)
inline void destroyList(LinkList& list) {
    Node* current = list;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    list = nullptr;
}

}



