#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
#define TYPE long long 
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
using namespace std;
int N;

struct Events {
    int x;
    int y1; 
    int y2; //y1 < y2
    int type; // 1 or -1
    Events(int x, int y1, int y2, int type) : x(x), y1(y1), y2(y2), type(type) {}
    bool operator<(const Events& a) {
        return x < a.x;
    }
};

vector<Events> arr;
vector<int> y_lists;
vector<int> compress_y_revert;
map<int, int> compress_y;

template <typename T1>
vector<T1> coord_compress(vector<T1> arr){
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    return arr;
}
template<typename T1>
ostream& operator<<(ostream& os, const vector<T1>& v) {
    for(int i = 0; i < v.size(); ++i){
        os << v[i] << ' ';
    }os << '\n';
    return os;
}
template <typename T1>
pair<map<int, T1>, vector<T1>> coord_compress_map(vector<T1> arr){
    map<int, T1> res;
    vector<T1> v = coord_compress(arr);
    for(int i = 0; i < v.size(); ++i){
        res[v[i]] = i;
    }
    return make_pair(res,v);
}

struct TopDownSegTree {
    vector<ll> tree; int n; //tree[node] = total real len of turned on interval
    vector<ll> lazy; // lazy[i] = tree[n+i] ~ tree[n+i+1] range allocated number
    TopDownSegTree(int size) : tree(2*size), lazy(2*size), n(size) {}
    void update(int node, int start, int end, int left, int right, int val){
        if (right < start || end < left) return;
        if (left <= start && end <= right) {
            lazy[node] += val;
        }
        else {
            int mid = (start+end)/2;
            update(2*node, start, mid, left, right, val);
            update(2*node+1, mid+1, end, left, right, val);
        }
        if (lazy[node]>0) {
            tree[node] = compress_y_revert[end+1]-compress_y_revert[start];   
            //cout << "update " << tree[node] << ' ' << node << endl;
        }
        else {
            if (node < n) tree[node] = tree[2*node] + tree[2*node+1]; //has leaf
            else tree[node] = 0;
        }
        //cout << start << ' ' << end << ' ' << left << ' ' << right << endl;
        //cout << tree << endl;
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
};

int main(){
    FASTIO;
    cin >> N;
    int x1, x2, y1, y2;
    for(int i = 0; i < N; ++i){
        cin >> x1 >> x2 >> y1 >> y2;
        arr.push_back(Events(x1, y1, y2, 1));
        arr.push_back(Events(x2, y1, y2, -1));
        y_lists.push_back(y1);
        y_lists.push_back(y2);    
    }
    sort(arr.begin(), arr.end());
    
    auto temp = coord_compress_map(y_lists);
    compress_y = temp.first; // real coord -> compressed idx
    compress_y_revert = temp.second; //compressed idx -> real coord
    TopDownSegTree t = TopDownSegTree(compress_y_revert.size());
    // ex : compressed l[4] = 0 1 5 10 -> size 4 tree/ v[4] -> v[i] = l[i]~l[i+1] range on? => this means we only takes care of v[0]~ v['2'], not v['3']
    TYPE res = 0;
    int prev_x = 0;
    for(int i = 0; i < arr.size(); ++i){
        int x = arr[i].x;
        int y1 = arr[i].y1;
        int y2 = arr[i].y2; //refer line 90, must update range with y2-1
        int type = arr[i].type;
        
        int length = t.query(1, 0, (t.n)-1, 0, (t.n)-1);
        //cout << "length is " << length << endl;
        res += (x-prev_x)*length;
        t.update(1, 0, (t.n)-1, compress_y[y1], compress_y[y2]-1, type);
        //cout << "y1 and y2 " << y1 << ' ' << y2 << endl;
        //cout << compress_y[y1] << " " << compress_y[y2] << "compressed" << endl;
        prev_x = x;

        //cout << "===========================\n";
    }
    cout << res << endl;
    return 0;
}