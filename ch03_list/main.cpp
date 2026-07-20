//
//  main.cpp
//  DataStruct-Algo_Deng
//

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

template <typename T>
void printList(List<T> const& list, string const& message){
    cout << message << "[";
    
    ListNode<T>* p = list.first();
    
    for(int i = 0; i < list.size(); i++){
        cout << p->data;
        
        if(i < list.size() - 1){
            cout << ", ";
        }
        
        p = p->succ;
    }
    
    cout << "]" << endl;
}

int main(){
    List<int> list;
    
    cout << boolalpha;
    cout << "Empty: " << list.empty() << endl;
    
    // Insertion
    list.insertAsFirst(2);
    list.insertAsFirst(1);
    list.insertAsLast(3);
    list.insertAsLast(4);
    
    printList(list, "After Insertion: ");
    cout << "Size: " << list.size() << endl;
    
    // Removal
    ListNode<int>* target = list.first()->succ;
    int removed = list.remove(target);
    
    cout << "Removed: " << removed << endl;
    printList(list, "After Removal: ");
    cout << "Size: " << list.size() << endl;
    
    // Unordered Search
    ListNode<int> *found = list.find(3);
    
    if(found != nullptr){
        cout << "find(3): " << found->data << endl;
    }else{
        cout << "find(3): not found" << endl;
    }
    
    ListNode<int>* missing = list.find(10);
    
    if(missing == nullptr){
        cout << "find(10): not found" << endl;
    }
    
    // Ordered Search
    ListNode<int>* position = list.search(2);
    
    cout << "search(2): " << position->data << endl;
    
    // Unordered Deduplicate
    list.insertAsLast(3);
    list.insertAsLast(4);
    
    printList(list, "Before Deduplicate: ");
    
    int removedDuplicates = list.deduplicate();
    
    cout << "Removed Deduplicates: " << removedDuplicates << endl;
    
    printList(list, "After Deduplicate: ");
    
    //Ordered Uniquify
    List<int> ordered;
    
    ordered.insertAsLast(1);
    ordered.insertAsLast(1);
    ordered.insertAsLast(2);
    ordered.insertAsLast(2);
    ordered.insertAsLast(2);
    ordered.insertAsLast(2);
    ordered.insertAsLast(4);
    ordered.insertAsLast(4);
    
    printList(ordered, "Before Uniquify: ");
    
    int removedOrdered = ordered.uniquify();
    
    cout << "Removed Ordered Deduplicates: " << removedOrdered << endl;
    
    printList(ordered, "After Uniquify: ");
    
    // Insertion Sort
    List<int> unsorted;

    unsorted.insertAsLast(5);
    unsorted.insertAsLast(2);
    unsorted.insertAsLast(4);
    unsorted.insertAsLast(2);
    unsorted.insertAsLast(1);
    unsorted.insertAsLast(3);

    printList(unsorted, "Before Insertion Sort: ");

    unsorted.insertionSort();

    printList(unsorted, "After Insertion Sort: ");
    
    // Reverse
    printList(unsorted, "Before Reverse: ");
    
    unsorted.reverse();
    
    printList(unsorted, "After Reverse: ");
    
    unsorted.reverse();
    
    printList(unsorted, "After 2nd Reverse: ");
    
    return 0;
}



