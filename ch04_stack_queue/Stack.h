//
//  Stack.h
//  DataStruct-Algo_Deng
//

#ifndef Stack_h
#define Stack_h

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack{
private:
    int _size;
    int _capacity;
    T* _elem;
    
    // 扩容操作
    void expand(){
        if(_size < _capacity) return;
        if(_capacity < 3) _capacity = 3;
        
        T* oldElem = _elem;
        _capacity <<= 1;
        _elem = new T[_capacity];
        
        for(int i = 0; i < _size; i++){
            _elem[i] = oldElem[i];
        }
        
        delete[] oldElem;
    }
    
public:
    Stack(int c = 10){
        _capacity = c;
        _size = 0;
        _elem = new T[_capacity];
    }
    
    // 析构函数
    ~Stack() {
        delete[] _elem;
    }
    
    int size() const { return _size; }
    bool empty() const { return _size == 0; }
    
    // 入栈
    void push(T const& e){
        expand();
        _elem[_size++] = e;
    }
    
    // 出栈
    T pop() {
        if(empty()){
            cout << "Stack is empty!" << endl;
            return T();  // 返回类型为 T 的默认值(非引用类函数)
        }
        
        return _elem[--_size];
    }
    
    // 返回栈顶元素，不弹出
    // 引用 & 表示可直接对元素进行操作/修改
    T& top(){
        if(empty()){
            throw runtime_error("Stack is empty!");
        }
        
        return _elem[_size - 1];
    }
    
};

#endif /* Stack_h */




