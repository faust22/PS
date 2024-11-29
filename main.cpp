#include <iostream>
#include <vector>
#define ll long long
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
#define PRIME 1000000007
using namespace std;
int N, M, K;

template<typename T1>
ostream& operator<<(ostream& os, const vector<T1>& v) {
    for(int i = 0; i < v.size(); ++i){
        os << v[i] << ' ';
    }os << '\n';
    return os;
}

struct SegTree { //https://heejayaa.tistory.com/45
    vector<ll> tree; int n;
    SegTree(int n) : tree(2*n), n(n) {}
    ll f(int a, int b) {return ((ll)a*b)%PRIME;}
    void init() {for(int i = n-1;i>0;i--) tree[i] = f(tree[i<<1],tree[i<<1|1]);}
    void update(int idx, int val){
        for(tree[idx+=n]=val;idx>1;idx>>=1) tree[idx>>1] = f(tree[idx], tree[idx^1]);
    }
    ll query(int l, int r){
        ll res = 1;
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if (l&1) res = f(tree[l++], res);
            if (!(r&1)) res = f(tree[r--], res);
        }
        return res;
    }
};
int main() {
    FASTIO;
    cin >> N >> M >> K;
    SegTree t = SegTree(N);
    for(int i = 0 ; i < N; ++i){
        int temp;
        cin >> t.tree[i+N];
    }
    t.init();
    //cout << t.tree << endl;
    for(int i = 0; i < M+K; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        if (a==1){
            t.update(b-1, c);
        }
        else {
            cout << t.query(b-1, c-1) << '\n';
        }
    }
    return 0;
}