#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
#define MIN_COORD 1000000000
using namespace std;
int N;
vector<pair<int,int>> v;

bool compare(pair<int,int> a, pair<int,int> b){
    if (a.first < b.first) return true;
    else {
        if (a.first == b.first && a.second < b.second) return true;
        else return false;
    }
}

int main(){
    FASTIO;
    cin >> N;
    for(int i = 0; i < N; ++i){
        int a, b;
        cin >> a >> b;
        v.push_back(make_pair(a,b));
    }
    sort(v.begin(), v.end(), compare);
    int res = 0;
    int s = -MIN_COORD;
    int e = -MIN_COORD;
    for(int i = 0; i < v.size(); ++i){
        int ns = v[i].first;
        int ne = v[i].second;
        if (ns <= e) {
            e = max(e,ne);
        }
        else {
            res += (e-s);
            s = ns;
            e = ne;
        }
    }
    res += (e-s);
    cout << res << endl;
}