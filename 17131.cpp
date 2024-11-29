#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <map>
#define TYPE long long 
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
#define TYPE2 pair<int,int>
#define PRIME 1000000007
using namespace std;
bool compare(TYPE2 a, TYPE2 b){
    if (a.second > b.second) return true;
    else{
        if (a.second == b.second && a.second < b.second) return true;
        else return false;
    }
}
struct segtree{
    int n;
    vector<int> v;
    segtree(int size) : n(size), v(4*size, 0) {}
    int f(int a, int b) {
        TYPE temp = a+b;
        return (int)(temp%PRIME);
    }
    void init(vector<int>& arr, int node, int start, int end){
        if (start==end){
            v[node] = arr[start];
        }
        else{
            int mid = (start+end)/2;
            init(arr, 2*node, start, mid);
            init(arr, 2*node + 1, mid+1, end);
            v[node] = v[2*node] + v[2*node + 1];
        }// not used so not modified
    }
    TYPE query(int node, int start, int end, int left, int right){
        if (left > right) return 0; //ad-hoc
        if (right<start || end<left){
            return 0;
        }
        if (left <= start && end <= right){
            return v[node];
        }
        int mid = (start+end)/2;
        TYPE lsum = query(node*2, start, mid, left, right);
        TYPE rsum = query(1+node*2, mid+1, end, left, right);
        return f(lsum,rsum);
    }
    void update(int node, int start, int end, int index, int diff){
        if (index < start || end < index){
            return;
        }
        if (start==end){
            v[node] = f(v[node], diff);
            return;
        }
        int mid = (start+end)/2;
        update(2*node, start, mid, index, diff);
        update(2*node+1, mid+1, end, index, diff);
        v[node] = f(v[2*node], v[2*node + 1]);
    }
};
int main(){
    FASTIO;
    int n;
    cin >> n;
    vector<pair<int,int>> stars;
    map<int,int> x_zip;
    vector<int> x_coord;
    for(int i = 0; i < n; ++i){
        int temp1, temp2;
        cin >> temp1 >> temp2;
        stars.push_back(make_pair(temp1, temp2));
        x_coord.push_back(temp1);
    }
    sort(x_coord.begin(), x_coord.end());
    sort(stars.begin(), stars.end(), compare);
    //stars.erase(unique(stars.begin(), stars.end()), stars.end()); // == for pair not defined, is it okay?
    x_coord.erase(unique(x_coord.begin(), x_coord.end()), x_coord.end());
    segtree t = segtree(x_coord.size());
    for(int i = 0; i < x_coord.size(); ++i){
        x_zip[x_coord[i]] = i;
    }
    TYPE res = 0;
    vector<int> update_list;
    int prev_y = stars[0].second;
    for(int i = 0; i < stars.size(); ++i){
        int x = stars[i].first;
        int y = stars[i].second;
        //cout << "coords " << x << ' ' << y << endl;
        int zip_x = x_zip[x];
        if (y!=prev_y) {
            for(int j = 0; j < update_list.size(); ++j){
                t.update(1,0,x_coord.size()-1, update_list[j], 1);
            }
            prev_y = y;
        }
        else {
            update_list.push_back(zip_x);
        }
        //t.update(1, 0, x_coord.size()-1, zip_x, 1);
        TYPE debug = (t.query(1, 0, x_coord.size()-1, 0, zip_x - 1) * t.query(1, 0, x_coord.size()-1, zip_x+1, x_coord.size()-1)); 
        //cout << t.query(1, 0, x_coord.size()-1, 0, zip_x - 1) << ' ' << t.query(1, 0, x_coord.size()-1, zip_x+1, x_coord.size()-1) << endl;
        res += debug;
        res %= PRIME;
        
        
    }
    cout << res << endl;
    return 0;
}