//
//  main.cpp
//  DataStruct-Algo_Deng
//

#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

// 括号匹配
bool parenMatch(const string& exp){
    Stack<char> s;
    
    for(int i = 0; i < (int)exp.length(); i++){
        char c = exp[i];
        
        // 前括号入栈
        if(c == '(' || c == '[' || c == '{'){
            s.push(c);
        // 后括号 c 与出栈的前括号 left 进行配对
        }else if(c == ')' || c == ']' || c == '}'){
            if(s.empty()) return false;
            
            char left = s.pop();
            if( c == ')' && left != '(') return false;
            if( c == ']' && left != '[') return false;
            if( c == '}' && left != '{') return false;
        }
    }
    return s.empty();
}

// RPN 求值
int evalRPN(const string& exp){
    Stack<int> s;
    
    for(int i = 0; i < (int)exp.length(); i++){
        char c = exp[i];
        
        if(c = ' ') continue;
        if(c >= '0' && c <= '9'){
            s.push(c - '0');
        }else{
            int last = s.pop();
            int first = s.pop();
            
            switch (c){
                case '+': s.push(first + last); break;
                case '-': s.push(fisrt - last); break;
                case '*': s.push(first * last); break;
                case '/': s.push(first / last); break;
            }
        }
    }
}


int main(){
    // 栈测试
    cout << "Test Stack" << endl;
    
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    
    cout << "Stack top: " << s.top() << endl;
    
    // Fist In Last Out
    while(!s.empty()){
        cout << s.pop() << " ";
    }
    cout << endl;
    
    // 队列测试
    cout << "Test Queue: " << endl;
    
    Queue<int> q(5);
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    cout << "Queue front: " << q.front() << endl;
    cout << "Queue size: " << q.size() << endl;
    
    // First In First Out
    while(!q.empty()){
        cout << q.dequeue() << " ";
    }
    cout << endl;
    
    cout << "Test Queue Full" << endl;
    
    Queue<int> q2(3);
    
    q2.enqueue(10);
    q2.enqueue(20);
    q2.enqueue(30);
    q2.enqueue(40);
    
    while(!q2.empty()){
        cout << q2.dequeue() << " ";
    }
    cout << endl;
    
    cout << "Test Parentheses Matching" << endl;
    
    string exp1 = "({}[])";
    string exp2 = "{}(][)";
    
    cout << exp1 << ": " << (parenMatch(exp1)? "Matched" : "Not Matched") << endl;
    cout << exp2 << ": " << (parenMatch(exp2)? "Matched" : "Not Matched") << endl;
    
    cout << "Test RPN" << endl;
    
    string rpn = "6 7 2 * + 3 * 2 / 4 +" // [(6 + 7 * 2) * 3] / 2 + 4
    
    cout << rpn << "=" << evalRPN(rpn) << endl;
    
    return 0;
}
