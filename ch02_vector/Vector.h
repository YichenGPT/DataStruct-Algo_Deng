//
//  Vector.h
//  DataStruct-Algo_Deng
//


#ifndef Vector_h
#define Vector_h

#include <iostream>

template <typename T>
class Vector{
private:
    int _size;      // 记录当前元素个数
    int _capacity;  // 最大容纳量
    T* _elem;       // 指向新建数组首地址
    
public:
    // 构造Vector对象
    Vector(int c = 10){
        _capacity = c;
        _size = 0;
        _elem = new T[_capacity];
    }
    
    // 析构函数: 销毁对象，归还内存
    ~Vector() {
        delete[] _elem; //缓释内存
    }
    
    // 辅助接口
    int size() const { return _size; }
    T& operator[](int r) const { return _elem[r]; }
    
    
    
    // 算法1: 动态扩容
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
    
    // push_back 函数
    void push_back(T const& e) {
        expand();           // 插入前检查并动态扩容
        _elem[_size++] = e; // 在当前末尾插入元素，并让 size + 1
    }
    
    
    // 算法2: 有序向量去重[双指针]
    // 目标: 将连续的重复元素覆盖，并返回被删除的元素个数
    int uniquify(){
        if(_size < 2) return 0;
        
        int slow = 0, fast = 0;
        
        while(++fast < _size){
            if(_elem[slow] != _elem[fast]){
                _elem[++slow] = _elem[fast];
            }
        }
        _size = ++slow; //下标+1
        
        return fast - slow;
    }
    
    // 算法3: 二分查找(版本C)
    // 在有序向量的[lo, hi)区间内查找元素e
    int binSearch(T* A, T const& e, int lo, int hi) const {
        while (lo < hi){
            int mi = (lo + hi) >> 1;
            
            // [lo, hi) -> [lo, mi) U [mi+1, hi)
            (e < A[mi])? hi = mi : lo = mi + 1;
        }// 归纳可证明: 返回A[lo == hi]为第 1 个大于 e 的元素
        return --lo;
    }
    
    // 算法4: 归并排序(Merge Sort)
    
    // 辅助函数: 二路归并
    // 目标: 将各自排好序的[lo, mi) U [mi, hi)合并成有序区间
    void merge(int lo, int mi, int hi){
        T* A = _elem + lo; // 合并后的大数组
        
        int length_b = mi - lo;  T* B = new T[length_b]; // 新开辟前半部分
        for(int i = 0; i < length_b; i++) B[i] = A[i]; // 把原始数据复制到 B 内部
        
        int length_c = hi - mi;  T* C = _elem + mi; // 后半部分原地操作
        
        for(int a = 0, b = 0, c = 0; (b < length_b) || (c < length_c); ){
            // 约定: 数值相等时，下标小的优先
            if((b < length_b) && (!(c < length_c) || B[b] <= C[c])) A[a++] = B[b++];
            if((c < length_c) && (!(b < length_b) || C[c] < B[b])) A[a++] = C[c++];
        }
        delete[] B;
        
    }
    
    // 主函数 mergeSort
    // 递归地对 [lo, hi)进行排序
    void mergeSort(int lo, int hi){
        // 递归基: 考虑只剩 1 个或者 0 个的情况
        if(hi - lo < 2) return;
        
        int mi = (lo + hi) >> 1;
        
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        
        merge(lo, mi, hi);
        
    }
    
};

#endif /* Vector_h */
    
    
    
    
    
