//
//  Queue.h
//  DataStruct-Algo_Deng
//

#ifndef Queue_h
#define Queue_h

#include <iostream>
using namespace std;

template <typename T>
class Queue{
private:
    int _front; // 队首
    int _rear;  // 下一可插入的队尾下标(末元素下标 + 1)
    int _capacity;
    T* _elem;
    
public:
    Queue(int c = 10){
        _capacity = c;
        _front = 0;
        _rear = 0;
        _elem = new T[_capacity];
    }
    
    // 析构函数
    ~Queue(){
        delete[] _elem;
    }
    
    int size() const { return _rear - _front; }
    
    bool empty() const { return _rear == _front; } // return size() == 0;
    
    // _rear = 末元素下标 + 1 = 全体个数 = _capacity
    bool full() const { return _rear == _capacity; }
    
    // 入队
    void enqueue(T const& e){
        if(full()){
            cout << "Queue is full!" << endl;
            return;
        }
        
        _elem[_rear++] = e;
    }
    
    // 出队: FIFO - First In First Out!
    T dequeue(){
        if(empty()){
            cout << "Queue is empty!" << endl;
            return T();
        }
        // 先出队，再后移 _front
        return _elem[_front++];
    }
    
    // 查看队首元素，但不出队
    T& front(){
        if(empty()){
            cout << "Queue is empty!" << endl;
            return _elem[0];
        }
        
        return _elem[_front];
    }
    
};
    
#endif /* Queue_h */
