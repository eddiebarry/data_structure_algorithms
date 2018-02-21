//
//  avl_tree.cpp
//
//  Created by Edgar Monis on 03/02/18.
//

#include<iostream>
//stdlib is included for debugging
#include<stdlib.h>
#define avl_tree_dt int

using namespace std;


struct avl_node{
    avl_tree_dt key;
    //pointer to left child
    avl_node* left_child;
    //pointer to right child
    avl_node* right_child;
    //height of node
    long long height;
    long long size;
    long long count;
};

avl_node* new_node(avl_tree_dt key){
    avl_node* new_node = new avl_node;
    //every node is inserted as a leaf node and then gets updated during rotation
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->key = key;
    new_node->height = 1;
    new_node->size = 1;
    new_node->count= 1;
    return new_node;
}

//helper functions required for insert
long long max(long long a, long long b){return a>b?a:b;}
long long height(avl_node* n){return n==NULL? 0:n->height;}
long long size(avl_node* n){return n==NULL? 0:n->size;}
long long balance(avl_node* n){return n==NULL? 0: height(n->left_child) - height(n->right_child);}


// guide for rotation
//     y                               x
//    / \     Right Rotation          /  \
//   x   T3   – – – – – – – >        T1   y
//  / \       < - - - - - - -            / \
// T1  T2     Left Rotation            T2  T3

avl_node* right_rotate(avl_node* y){
    avl_node* new_parent_y = y->left_child;
    avl_node* new_left_child_y = y->left_child->right_child;
    
    
    new_parent_y->right_child = y;
    y->left_child = new_left_child_y;
    //y gets new tree hence height changes same for y's new parent
    y->height = max( height(y->left_child),height( y->right_child) ) + 1;
    new_parent_y->height = max( height(new_parent_y->left_child) , height(new_parent_y->right_child) )+ 1;
    //same for size
    y->size= size(y->left_child) + size (y->right_child)+ y->count;
    new_parent_y->size = size(new_parent_y->left_child) + size(new_parent_y->right_child) + new_parent_y->count;
    //for recursive function
    return new_parent_y;
}
avl_node* left_rotate(avl_node* x){
    avl_node* new_parent_x = x->right_child;
    avl_node* new_right_child_x = x->right_child->left_child;
    
    new_parent_x->left_child = x;
    x->right_child = new_right_child_x;
    //x gets new tree hence height changes same for x's new parent
    x->height = max( height(x->left_child) , height(x->right_child) ) + 1;
    new_parent_x->height = max( height(new_parent_x->left_child) , height(new_parent_x->right_child) ) + 1;
    //updating sizes
    x->size= size(x->left_child) + size(x->right_child) + x->count;
    new_parent_x->size = size(new_parent_x->left_child) + size(new_parent_x->right_child) + new_parent_x->count;
    //for recursive function
    return new_parent_x;
    
}



avl_node* insert(avl_node* node, avl_tree_dt key){
    if(node == NULL){
        return new_node(key);
    }
    
    if(key < node->key){
        node->left_child = insert(node->left_child, key);
    }
    else if(key > node->key){
        node->right_child = insert(node->right_child, key);
    }
    else{
        node->count++;
    }
    
    node->size = node->size + 1;
    
    long node_bal = balance(node);
    
    if(node_bal > 1 && key < node->left_child->key){
        avl_node* temp =  right_rotate(node);
        node->height = 1 + max(height(node->left_child),height(node->right_child));
        return temp;
    }
    
    if(node_bal > 1 && key > node->left_child->key){
        node->left_child = left_rotate(node->left_child);
        avl_node* temp =  right_rotate(node);
        node->height = 1 + max(height(node->left_child),height(node->right_child));
        return temp;
    }
    
    if(node_bal < -1 && key > node->right_child->key){
        avl_node* temp = left_rotate(node);
        node->height = 1 + max(height(node->left_child),height(node->right_child));
        return temp;
    }
    
    if(node_bal < -1 && key < node->right_child->key){
        node->right_child = right_rotate(node->right_child);
        avl_node* temp =  left_rotate(node);
        node->height = 1 + max(height(node->left_child),height(node->right_child));
        return temp;
    }
    
    node->height = 1 + max( height(node->left_child) , height(node->right_child) );
    return node;
}





void pre_order(avl_node* n){
    if(n!=NULL){
        cout<<n->key<<"  ";
        pre_order(n->left_child);
        cout<<"  ";
        cout<<n->key<<"  ";
        pre_order(n->right_child);
    }
}

void parent(avl_node* n){
    if(n!=NULL){
        cout<<n->key<<" ("<<n->size<<") "<<" is p of "<<(n->left_child==NULL?-1 : n->left_child->key);
        cout<<" and "<<(n->right_child==NULL?-1 : n->right_child->key);
        cout<<" .|||. ";
        parent(n->left_child);
        parent(n->right_child);
    }
}
int max_levl = 0;
void levels(avl_node* n, int level){
    if(n!=NULL){
        if(level > max_levl){
            max_levl = level;
        }
        //cout<<n->key<<" "<<level<<"\n";
        levels(n->left_child,level+1);
        levels(n->right_child,level+1);
    }
}

int main(){
    avl_node* root = NULL;
//    root = insert(root, 10);
//    root = insert(root, 20);
//    cout<<root->size<<" "<<root->height<<" "<<root->key<<"\n";
//    root = insert(root, 30);
//    root = insert(root, 40);
//    root = insert(root, 50);
//    root = insert(root, 25);
//
//    int t = 1000000;
//    srand(1);
//    while(t--){
//        int x = rand()%1000;
//        //cout<<x<<" is to be inserted\n";
//        root = insert(root,x);
//        //parent(root);
//        //cout<<"\n\n\n\n";
//    }
//    parent(root);
//  levels(root,1);
//    cout<<max_levl<<" is the max level\n";
}

