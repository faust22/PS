#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define ll long long
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
#define PRIME 1000000007
using namespace std;
int N, M, K;
vector<pair<int,int>> v;

bool compare(pair<int,int> a, pair<int,int> b){
    if (a.first < b.first){
        return true;
    }
    else if (a.first == b.first && a.second < b.second){
        return true;
    }
    else return false;
}

ll subsolve(vector<pair<int,int>>& v){
    ll res = 0;
    //v should be sorted
    int s = -1;
    int e = -1;
    for(int i = 0; i < v.size(); ++i){
        int ns = v[i].first;
        int ne = v[i].second;
        if (ns <= e) {
            e = max(e, ne);
        }
        else {
            res += (e-s);
            s = ns;
            e = ne;
        }
    }
    res += (e-s);
    return res;
}
int main(){
    FASTIO;
    cin >> N >> M;
    for(int i = 0; i < N; ++i){
        int temp1, temp2;
        cin >> temp1 >> temp2;
        if (temp2 < temp1) v.push_back(make_pair(temp2, temp1));
    }
    sort(v.begin(), v.end(), compare);
    cout << (long long)M + 2*subsolve(v) << '\n';
    return 0;
}