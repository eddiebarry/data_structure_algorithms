//
//  avl_tree.cpp
//
//  Created by Edgar Monis on 03/02/18.
//
#include<iostream>
#include<stdlib.h>  //for rand testing purpose
#define deque_dt int
using namespace std;
struct node{
    deque_dt key;
    node* head;
    node* tail;
};
class deque{
private:
    node* top;
    node* bottom;
    long long size;
public:
    deque(){
        size = 0;
        top=NULL;
        bottom=NULL;
    }
    ~deque(){
        while (top!=NULL) {
            node* temp = top;
            top=top->tail;
            delete temp;
        }
    }
    void push_front(deque_dt key){
        node* new_node = new node;
        new_node->key = key;
        if(top==NULL){
            new_node->tail=NULL;
            new_node->head=NULL;
            bottom = new_node;
        }
        else{
            top->head = new_node;
            new_node->tail = top;
            new_node->head = NULL;
        }
        top = new_node;
        size++;
    }
    void push_back(deque_dt key){
        node* new_node = new node;
        new_node->key = key;
        if(bottom==NULL){
            new_node->tail=NULL;
            new_node->head=NULL;
            top = new_node;
        }
        else{
            new_node->head = bottom;
            bottom->tail = new_node;
            new_node->tail=NULL;
        }
        bottom = new_node;
        size++;
    }
    void pop_front(){
        if(top!=NULL){
            node* temp = top;
            top = top->tail;
            if(top!=NULL){
                top->head = NULL;
            }
            delete temp;
            size--;
        }
    }
    void pop_back(){
        if(bottom!=NULL){
            node* temp = bottom;
            bottom = bottom->head;
            if(bottom!=NULL){
                bottom->tail = NULL;
            }
            delete temp;
            size--;
        }
    }
    deque_dt front(){
        deque_dt x;
        return top==NULL? x : top->key;
    }
    deque_dt back(){
        deque_dt x;
        return bottom==NULL? x: bottom->key;
    }
    void display(){
        node* temp = top;
        while (temp!=NULL) {
            cout<<temp->key<<" <--> ";
            temp=temp->tail;
        }
    }
    
};



int main(){
    deque de;
    int t = 200;
    int x = 0;
    srand(1);
    while(t--){
        x++;
        
        cout<<x<<"\n";
        //int x = rand();
        if(x%10==1){
            de.push_back(x);
        }
        else if(x%10==2){
            de.push_front(x);
        }
        else if(x%10==3){
            de.pop_front();
        }
        else if(x%10==4){
            de.pop_back();
            
            cout<<de.front()<<"\n";
            
            cout<<de.back()<<"\n";
        }
        else if(x%10==5){
            cout<<de.front()<<"\n";
        }
        else if(x%10==6){
            cout<<de.back()<<"\n";
        }
        else{
            de.push_back(x);
        }
        de.display();
        cout<<"\n";
    }
    de.push_back(100);
    de.display();
    return 0;
}
