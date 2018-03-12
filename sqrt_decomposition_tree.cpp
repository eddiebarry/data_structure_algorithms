//
//  sqrt_decomposition_tree.cpp
//
//  Created by Edgar Monis.
//  range max in O(srt(n))
//  update in O(srt(n))
//  0 indexed
//
//  update sqrt_dt with needed data type

#include <iostream>
#include <vector>
#include <math.h>
#define sqrt_dt long

using namespace std;

class sqrt_tree{
private:
    long num;
    long blk_sz;
    vector <sqrt_dt>  arr;
    vector <sqrt_dt>  sqr_arr;
public:
    sqrt_tree( vector<sqrt_dt> & vec){
        num = vec.size();
        blk_sz = sqrt(num);
        //initialising sqrt block
        int curr_block = -1;
        for(long i = 0; i < num; i++){
            if(i%blk_sz==0){
                curr_block++;
                sqr_arr.push_back( vec[i] );
            }
            arr.push_back( vec[i] );
            if(sqr_arr[curr_block] < vec[i] ){
                sqr_arr[curr_block] = vec[i] ;
            }
        }
    }
    pair<sqrt_dt, long >query(long l , long r){
        sqrt_dt  temp = arr[l];
        while(l<r && l%blk_sz!=0 && l!=0){
            if(arr[l]  > temp ){
                temp = arr[l];
            }
            l++;
        }
        while(l+blk_sz<=r){
            if(sqr_arr[l/blk_sz] >temp ){
                temp = sqr_arr[l/blk_sz];
            }
            l+=blk_sz;
        }
        while(l<=r){
            if(arr[l] >temp ){
                temp = arr[l];
            }
            l++;
        }
        return temp;
    }
    
    void update(long idx, sqrt_dt data){
        arr[idx] = data ;
        long start = (idx/blk_sz)*blk_sz;
        long end = start + blk_sz > num ? num : start + blk_sz;
        sqr_arr[idx/blk_sz] = arr[start];
        for(long i = start; i <end; i++){
            if(sqr_arr[idx/blk_sz] < arr[i] ){
                sqr_arr[idx/blk_sz] = arr[i];
            }
        }
    }
        
        
};
        
    
    int main(){
        int n = 100;
        vector<long>vec;
        for(int i = 0 ; i< 100; i++){
            vec.push_back(i);
        }
        sqrt_tree tr(vec);
        cout<<tr.query(0,99)<<" ia the max \n";
        tr.update(1,1000);
        cout<<" index has been updated\n";
    }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
//        sqr = num/sqrt(num);
//        for(auto x: vec){
//            arr.push_back(x);
//        }
//        for(long i = 0; i <sqr; i++){
//            sqr_arr.push_back(0);
//        }
//        if(sqr*sqr!=num){
//            sqr_arr.push_back(0);
//        }
//        //assigning mx to the sqrt cells
//        for(long i = 0; i < num; i++){
//            if(vec[i] > sqr_arr[i/sqr]){
//                sqr_arr[i/sqr] = vec[i];
//            }
//        }
//    }
//    void update(long idx, sqrt_dt a){
//        arr[idx] = a;
//        long start = (idx/sqr) *sqr;
//        long end   = start+sqr < num ? start + sqr : num;
//        for(long i = (idx/sqr) *sqr; i %sqr != 0; i++){
//            if(vec[i] > sqr_arr[i/sqr]){
//                sqr_arr[i/sqr] = vec[i];
//            }
//        }
//    }
    
