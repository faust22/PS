#include <iostream>
#include <vector>
#define TYPE long long
using namespace std;

struct lazy_segtree {
    vector<int> v;
    vector<int> lazy;
    int IDENTITY = 0; // f=multiply? it will be 1, f=addition? it will be 0.
    int n;
    lazy_segtree(int size) : n(size) {
        v = vector<int>(4*n, 0); //you can tignten it
        lazy = vector<int>(4*n, 0);
    }
    TYPE f(TYPE a, TYPE b) {
        return a+b;
    }
    TYPE l_f(int start, int end, int diff){
        return (end-start+1)*diff;
    }//this is applying interval delayed value
    void update_lazy(int node, int start, int end){
        // must do
        // 1. clear lazy
        if (lazy[node] != 0) {
            v[node] = f(v[node], l_f(start, end, lazy[node]));
            if (start!=end){
                lazy[2*node] = f(lazy[2*node], lazy[node]);
                lazy[2*node+1] = f(lazy[2*node+1], lazy[node]);
            }// if node has sibilings
            lazy[node] = 0;
        }
    } // update_lazy guarantees The node has no lazy evaluation so you can use v[node] without doubt
    void update_range(int node, int start, int end, int left, int right, int diff){
        // must do
        // 1. clear lazy(propagate) & calc lazy
        // 2. calc v[node]
        // 3. recursively pass update
        update_lazy(node, start, end); // 1. clear lazy
        if (end<left || right<start) return;
        if (left <= start && end <= right){
            v[node] = f(v[node], l_f(start, end, diff)); // 2. calc v[node]
            if (start!=end){
                lazy[2*node] = f(lazy[2*node], diff); // 1-1. calc lazy
                lazy[2*node+1] = f(lazy[2*node+1], diff);
            }
            return;
        }
        update_range(2*node, start, (start+end)/2, left, right, diff); // 3. update pass
        update_range(2*node+1, 1+(start+end)/2, end, left, right, diff);
    }
    TYPE query(int node, int start, int end, int left, int right){
        update_lazy(node, start, end);
        if (end<left || right<start) return IDENTITY;
        if (left<=start && end<=right){
            return v[node];
        }
        TYPE lsum = query(2*node, start, (start+end)/2, left, right);
        TYPE rsum = query(2*node + 1, 1+(start+end)/2, end, left, right);
        return f(lsum,rsum);
    }
};