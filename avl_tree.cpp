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

class avl_tree{
private:
    avl_node* root;
    
    
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
    long long count(avl_node* n){return n==NULL? 0: n->count;}
    
    
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
    
    avl_node* min_value_node(avl_node* n){
        if(n==NULL){
            return NULL;
        }
        if(n->left_child == NULL){
            return n;
        }
        else{
            return min_value_node(n->left_child);
        }
    }
    
    avl_node* max_value_node(avl_node* n){
        if(n==NULL){
            return NULL;
        }
        if(n->right_child == NULL){
            return n;
        }
        else{
            return max_value_node(n->right_child);
        }
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
        
        node->size = size(node->left_child) + size(node->right_child) + node->count;
        node->height = 1 + max(height(node->left_child),height(node->right_child));
        
        long long node_bal = balance(node);
        
        if(node_bal > 1 && key < node->left_child->key){
            return  right_rotate(node);
        }
        
        if(node_bal > 1 && key > node->left_child->key){
            node->left_child = left_rotate(node->left_child);
            return  right_rotate(node);
        }
        
        if(node_bal < -1 && key > node->right_child->key){
            return  left_rotate(node);
        }
        
        if(node_bal < -1 && key < node->right_child->key){
            node->right_child = right_rotate(node->right_child);
            return  left_rotate(node);
        }
        
        return node;
    }
    
    
    
    avl_node* delete_node(avl_node* n, avl_tree_dt key){
        //if key  is not present delete node will default to this
        if(n==NULL){
            return n;
        }
        
        if(key < n->key){
            n->left_child = delete_node(n->left_child, key);
        }
        else if(key > n->key){
            n->right_child = delete_node(n->right_child, key);
        }
        else{
            if(n->count>1){
                n->count--;
                n->size--;
                return n;
            }
            else{
                //node can have 0,1,2 children
                
                //0 , 1 children case
                if(n->left_child == NULL || n->right_child == NULL){
                    avl_node* temp = n->left_child ? n->left_child : n->right_child;
                    //0 children case
                    if(temp == NULL){
                        temp = n;
                        n = NULL;
                    }
                    //1 children case
                    else{
                        *n = *temp;
                    }
                    delete temp;
                }
                //2 childre casw
                else{
                    avl_node* successor = min_value_node(n->right_child);
                    n->key = successor->key;
                    n->count = successor->count;
                    successor->count = 1;
                    //this will eliminate the succesor node because alll its data has been swapped into node n
                    n->right_child = delete_node(n->right_child, n->key);
                }
            }
        }
        
        if(n==NULL){
            return n;
        }
        n->height = max( height(n->right_child) , height(n->left_child) ) + 1;
        n->size = size(n->left_child) + size(n->right_child) + n->count;
        
        long long bal = balance(n);
        //left left case
        if(bal > 1 && balance( n->left_child) >=0 ){
            return right_rotate(n);
        }
        //left right
        if(bal > 1 && balance(n->right_child) < 0 ){
            n->left_child = left_rotate(n->left_child);
            return right_rotate(n);
        }
        //right left case
        if(bal < -1 && balance( n->right_child) > 0 ){
            n->right_child = right_rotate(n->right_child);
            return left_rotate(n);
        }
        //right right case
        if(bal < -1 && balance(n->right_child) <= 0 ){
            return left_rotate(n);
        }
        
        return n;
        
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
            cout<<"its height is "<<n->height;
            cout<<" .|||. ";
            parent(n->left_child);
            parent(n->right_child);
        }
    }
    
    void levels(avl_node* n, int level, int& max_levl){
        if(n!=NULL){
            if(level > max_levl){
                max_levl = level;
            }
            //cout<<n->key<<" "<<level<<"\n";
            levels(n->left_child,level+1, max_levl);
            levels(n->right_child,level+1, max_levl);
        }
    }
    void erase_tree(avl_node* n){
        if(n!=NULL){
            erase_tree(n->left_child);
            erase_tree(n->right_child);
            delete n;
        }
    }
    
    bool find(avl_node* n , avl_tree_dt key){
        if(n==NULL){
            return false;
        }
        else{
            if(n->key < key){
                find(n->right_child,key);
            }
            else if(n->key > key){
                find(n->left_child,key);
            }
            return true;
        }
    }
    
    avl_node* find_by_rank(avl_node* n, long long rank){
        if(size(n) >= rank){
            if(rank <= size(n->left_child) ){
                return find_by_rank(n->left_child,rank);
            }
            else if(rank <= size(n->left_child) + count(n) ){
                return n;
            }
            else{
                return find_by_rank(n->right_child, rank - size(n->left_child) - count(n) );
            }
                    
        }
        else{
            return NULL;
        }
    }
    
public:
    avl_tree(){
        root = NULL;
        //max_levl = 0
    }
    ~avl_tree(){
        erase_tree(root);
    }
    void Insert(avl_tree_dt key){
        root = insert(root,key);
    }
    void Delete(avl_tree_dt key){
        root = delete_node(root,key);
    }
    avl_tree_dt Min(){
        avl_node* temp = min_value_node(root);
        return temp->key;
    }
    avl_tree_dt Max(){
        avl_node* temp = max_value_node(root);
        return temp->key;
    }
    void Print_parents(){
        parent(root);
    }
    void Pre_order(){
        pre_order(root);
    }
    bool Find(avl_tree_dt key){
        return find(root,key);
    }
    avl_tree_dt Find_by_rank(long long rank){
        avl_node* temp = find_by_rank(root,rank);
        return temp->key;
    }
    //returns lower medium
    avl_tree_dt Find_median(){
        avl_node* temp = find_by_rank(root,root->size/2);
        return temp->key;
    }
    void Print_max_levels(){
        int x = 0;
        levels(root,1,x);
        cout<<x<<" is the max level \n";
    }
};


int main(){
    avl_tree bst;
    srand(1);
    bst.Insert(10);
    bst.Print_parents();
    bst.Delete(10);
    bst.Print_parents();
    int t = 10000000;
    int x = 0;
    while (t--) {
        x = rand();
        bst.Insert(x);
        //x++;
        //bst.Insert(x);
        if(x%4==0){
            bst.Delete(x);
        }
    }
    //cout<<bst.Find_by_rank(1)<<" "<<bst.Find_by_rank(2)<<" "<<bst.Find_median()<<"\n";
    bst.Print_max_levels();
    //cout<<max_levl<<" is the max level \n"
    //bst.print_parents();
    return 0;
}

