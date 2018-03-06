//
//  fenwick_tree.cpp
//  supports all commutative ops
//  supports range sum/ range updates
//
//  Created by Edgar Monis on 03/02/18.
//
#include<iostream>
#include<vector>
#include<stdlib.h>  //for rand testing purpose

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define fenwick_tree_dt long long
using namespace std;

class BIT{
public:
    //initialise in O(n)
    BIT(vector<fenwick_tree_dt> arr){
        tree = vector<fenwick_tree_dt>(arr.size()+1,0);
        for(long long idx = 0; idx < arr.size(); idx++ ){
            tree[idx+1] = arr[idx];
        }
        for(long long idx = 1; idx < tree.size(); idx++ ){
            long long temp = (idx&-idx) + idx;
            if(temp < tree.size() ){
                tree[temp] +=tree[idx];
            }
        }
    }
    //only works for range sum with updates
    fenwick_tree_dt prefix_query(long long idx){
        fenwick_tree_dt result = 0;
        for(++idx; idx > 0; idx -= idx&-idx){
            result+=tree[idx];
        }
        return result;
    }
    //this operation will not give correct values for range updates
    fenwick_tree_dt range_query(long long from, long long to){
        return prefix_query(to) - prefix_query(from-1);
    }
    //gives correct for range updates
    fenwick_tree_dt point_query(long long idx){
        return prefix_query(idx) - prefix_query(idx-1);
    }
    //updates the value by add
    void update(long long idx , fenwick_tree_dt add){
        for(++idx; idx < tree.size(); idx+=idx & -idx){
            tree[idx] +=add;
        }
    }

private:
    vector<fenwick_tree_dt> tree;
};
//class BIT_range{
//private:
//    BIT tree;
//    BIT range_tree;
//public:
//    BIT_range(vector<fenwick_tree_dt vec){
//        tree(vec);
//        vector<fenwick_tree_dt vec1(vec.size(),0);
//        range_tree(vec1);
//    }
//    void range_update(long long from, long long to,fenwick_tree_dt add){
//        range_tree.update(from, add);
//        range_tree.update(to+1, -add);
//    }
//    void point_update(long long idx, fenwick_tree_dt add){
//        tree.update(idx,add);
//    }
//    fenwick_tree_dt point_query(long long idx){
//        return tree.point_query(idx)+range_tree.prefix_query(idx);
//    }
//};


int main(){
//    vector<long long> mem;
//    REP(i,11){
//        mem.push_back(i);
//    }
//    BIT bit(mem);
//    cout<<bit.point_query(1);
//    cout<<bit.prefix_query(9);
//    bit.update(1,11);
//
//    cout<<bit.point_query(1);
//    cout<<bit.prefix_query(9);
return 0;
}
