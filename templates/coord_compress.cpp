#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;

template <typename T1>
vector<T1> coord_compress(vector<T1> arr){
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    return arr;
}

template <typename T1>
map<int, T1> coord_compress_map(vector<T1> arr){
    map<int, T1> res;
    vector<T1> v = coord_compress(arr);
    for(int i = 0; i < v.size(); ++i){
        res[v[i]] = i;
    }
    return res;
}