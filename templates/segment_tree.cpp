#include <iostream>
#include <vector>
#define ll long long
using namespace std;

struct BottomUpSegTree { //https://heejayaa.tistory.com/45
    vector<ll> tree; int n;
    BottomUpSegTree(int n) : tree(2*n), n(n) {}
    ll f(int a, int b) {return a+b;}
    void init() {for(int i = n-1;i>0;i--) tree[i] = f(tree[i<<1],tree[i<<1|1]);}
    void update(int idx, int val){
        for(tree[idx+=n]=val;idx>1;idx>>=1) tree[idx>>1] = f(tree[idx], tree[idx^1]);
    }
    ll query(int l, int r){
        ll res = 0; // this is f-dependency
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if (l&1) res = f(tree[l++], res);
            if (!(r&1)) res = f(tree[r--], res);
        }
        return res;
    }
}; // bottom-up method

struct TopDownSegTree {
    private:
    vector<ll> tree; int n;
    TopDownSegTree(int size) : tree(2*size), n(size) {}
    void init(vector<int>& a, int node, int start, int end) {
        if (start==end){
            tree[node] = a[start]; 
        }
        else{
            int mid = (start+end)/2;
            init(a, 2*node, start, mid);
            init(a, 2*node+1, mid+1, end);
            tree[node] = tree[node*2] + tree[2*node+1];
        }
    }
    void update(int node, int start, int end, int index, int val){
        if (index < start || end < index) return;
        if (start==end){
            tree[node] = val; //two version exists, one is adding diff, one is replacing diff.
            return;
        }
        int mid = (start+end)/2;
        update(2*node, start, mid, index, val);
        update(2*node+1, mid+1, end, index, val);
        tree[node]=tree[2*node]+tree[2*node+1];
        return;
    }
    ll query(int node, int start, int end, int left, int right){
        if (end < left || right < start) return 0;
        if (left <= start && end <= right) return tree[node];
        int mid = (start+end)/2;
        ll lsum = query(2*node, start, mid, left, right);
        ll rsum = query(2*node + 1, mid+1, end, left, right);        
        return lsum+rsum;
    }
    public:
    void init(vector<int>& a){
        init(a, 1, 0, tree.size());
    }
    void update(int index, int val){
        update(1, 0, tree.size(), index, val);
    }
    ll query(int start, int end){
        return query(1, 0, tree.size(), start, end);
    }
};