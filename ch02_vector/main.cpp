//
// ch02_vector/main.cpp
//  DataStruct-Algo_Deng
//


#include <iostream>
#include "Vector.h"
using namespace std;

// 辅助函数: 打印 Vector 内容
template <typename T>
void printVector(const Vector<T>& v, const string& msg){
    cout << msg << "[";
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << "\t";
    }
    cout << "]" << endl;
}


int main() {
    Vector <int> v(3);
    
    cout << "Test Begin!" << endl;
    
    // 测试 1
    cout << "Test Input & expand()" << endl;
    v.push_back(1);
    v.push_back(5);
    v.push_back(2);
    v.push_back(3);
    v.push_back(3);
    v.push_back(7);
    v.push_back(2);
    
    printVector(v, "After push_back(): ");
    cout << "v_size = " << v.size() << endl;
    
    // 测试 2
    cout << "Test mergeSort()" << endl;
    v.mergeSort(0, v.size());
    printVector(v, "After mergeSort(): ");
    
    // 测试 3
    cout << "Test uniquify()" << endl;
    int removedCount = v.uniquify();
    cout << "Removed " << removedCount << " duplicated elements." << endl;
    printVector(v, "After uniquify():  ");
    
    // 测试 4
    cout << "Test binSearch()" << endl;
    int target = 5;
    int rank = v.binSearch(&v[0], target, 0, v.size());
    cout << "Target: " << target << " | Found at rank: " << rank << endl;
    if (rank >= 0 && rank < v.size() && v[rank] == target) {
        cout << "Search SUCCESS! v[" << rank << "] is " << v[rank] << endl;
    } else {
        cout << "Search FAILED or Target NOT exact match. (binSearch returns the last element <= target)" << endl;
    }

    
    return 0;
}
