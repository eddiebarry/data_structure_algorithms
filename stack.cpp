//
//  stack.cpp
//
//  Created by Edgar Monis on 03/02/18.
//  O(1) push/pop/empty
//  O(n) display
//  usefull for LIFO ops
//
// int can be changed to any type to make it versatile
#include <iostream>
#define stack_dt int

using namespace std;

/**
    define a node with stack_data_type as data and a tail pointer
**/
struct node{
    stack_dt data;
    node* tail;
};

/**
    the class will contain a pointer to the top
**/

class stack{
private:
    struct node* top;
public:
    
    stack(){
        top = NULL;
    }
    
    ~stack(){
        while(top!=NULL){
            cout<<"destructor is running\n";
            node* temp = top;
            top = top->tail;
            delete temp;
        }
    }
    
    bool empty(){
        return top = NULL;
    }
    
    void push(stack_dt val){
        node* new_node = new node;
        new_node->data = val;
        new_node->tail = NULL;
        if(top!=NULL){
            new_node->tail = top;
        }
        top = new_node;
    }
    
    stack_dt peek(){
        return top->data;
    }
    
    void pop(){
        node* temp = top;
        top = top->tail;
        delete temp;
    }
    
    void display(){
        node* temp = top;
        while(temp->tail!=NULL){
            cout<<temp->data<<" --> ";
            temp = temp->tail;
        }
        cout<<"\n";
    }
    
    unsigned long size(){
        unsigned long size = 0;
        node* temp = new node;
        temp = top;
        while(temp->tail!=NULL){
            size++;
            temp=temp->tail;
        }
        delete temp;
        return size;
    }
};

int main(){
    stack stk;
    cout<<stk.empty()<<"\n";
    stk.push(100);
    cout<<stk.peek()<<"\n";
    cout<<stk.size()<<"\n";
    cout<<stk.empty()<<"\n";
    //stk.display();
    stk.push(1000);
    cout<<stk.peek()<<"\n";
    cout<<stk.size()<<"\n";
    cout<<stk.empty()<<"\n";
    //stk.display();
    stk.pop();
    cout<<stk.peek()<<"\n";
    cout<<stk.size()<<"\n";
    cout<<stk.empty()<<"\n";
    //stk.display();
    stk.pop();
    cout<<stk.peek()<<"\n";
    cout<<stk.size()<<"\n";
    cout<<stk.empty()<<"\n";
    //stk.display();
    stk.pop();
}


//  Credits to jkeys and jaif on stack overflow for some much needed help
//  https://stackoverflow.com/questions/1085238/node-based-stack-class-need-peer-review
//  http://btechsmartclass.com/DS/U2_T3.html
//  https://proprogramming.org/c-program-to-implement-stack-using-linked-list/
//  https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
