#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
#define TYPE long long
using namespace std;

struct segtree{
    int n;
    vector<int> v;
    segtree(int size) : n(size), v(4*size, 0) {}
    void init(vector<int>& arr, int node, int start, int end){
        if (start==end){
            v[node] = arr[start];
        }
        else{
            int mid = (start+end)/2;
            init(arr, 2*node, start, mid);
            init(arr, 2*node + 1, mid+1, end);
            v[node] = v[2*node] + v[2*node + 1];
        }
    }
    TYPE query(int node, int start, int end, int left, int right){
        if (right<start || end<left){
            return 0;
        }
        if (left <= start && end <= right){
            return v[node];
        }
        int mid = (start+end)/2;
        TYPE lsum = query(node*2, start, mid, left, right);
        TYPE rsum = query(1+node*2, mid+1, end, left, right);
        return lsum+rsum;
    }
    void update(int node, int start, int end, int index, int diff){
        if (index < start || end < index){
            return;
        }
        if (start==end){
            v[node] += diff;
            return;
        }
        int mid = (start+end)/2;
        update(2*node, start, mid, index, diff);
        update(2*node+1, mid+1, end, index, diff);
        v[node] = v[2*node] + v[2*node+1];
    }
};
bool compare(pair<int,int> a, pair<int, int> b){
    //(1,10) -> (2,10)
    //(2,10) -> (2, 5)
    if (a.first < b.first) return true;
    else {
        if (a.first==b.first && a.second > b.second) return true;
        else return false;
    }
}
int main(){
    FASTIO;
    int c, n;
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        vector<pair<int,int>> temp;
        vector<int> y_coord;
        map<int,int> y_zip;
        for(int j = 0; j < n; ++j){
            int temp1, temp2;
            cin >> temp1 >> temp2; //gonna zip coord of y
            temp.push_back(make_pair(temp1, temp2));
            y_coord.push_back(temp2);
        }
        sort(y_coord.begin(), y_coord.end());
        sort(temp.begin(), temp.end(), compare);
        y_coord.erase(unique(y_coord.begin(), y_coord.end()), y_coord.end());
        int temp3 = y_coord[y_coord.size()-1];
        for(int j = 0; j < y_coord.size(); ++j){
            y_zip[y_coord[j]] = j;
        }
        segtree s = segtree(y_coord.size());
        TYPE res = 0;
        for(int j = 0; j < temp.size(); ++j){
            int x = temp[j].first;
            int y = temp[j].second;
            //cout << x << ' ' << y << endl;
            int zip_y = y_zip[y];
            //cout << "query range " << zip_y << ' ' << y_zip[temp3] << endl;
            int n_of_isl = s.query(1, 0, y_coord.size()-1, zip_y, y_zip[temp3]);
            s.update(1,0,y_coord.size()-1, zip_y, 1);
            res += n_of_isl;
            //cout << "debug : " << n_of_isl << endl;
        }
        cout << res << endl;
    }   

    return 0;
}