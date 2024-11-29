#include <iostream>
#include <vector>
#define MAX_N 1025
#define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
#define TYPE long long
using namespace std;
vector<vector<int>> yTree;
int N, M;
int arr[MAX_N][MAX_N];

void debug_seg_tree(vector<vector<int>>& tree){
    for(int i = 0; i < tree.size(); ++i){
        for(int j = 0; j < tree[0].size(); ++j){
            cout << tree[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void init_tree_build(vector<vector<int>>& tree){
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            tree[i+N-1][j+N-1] = arr[i][j];
        }
    }
    for(int i = N; i<2*N; ++i){
        for(int j = N-1; j>0; --j){
            tree[i][j] = tree[i][j*2]+tree[i][j*2+1];
        }
    }
    for(int i = N-1; i>0; --i){
        for(int j = 0; j < 2*N; ++j){
            tree[i][j] = tree[2*i][j] + tree[2*i+1][j];
        }
    }
}
void update(vector<vector<int>>& tree, int y, int x, int value){
    int x1 = x-1+N; int y1 = y-1+N; //why -1? BECAUSE input is [1~N] range
    tree[y1][x1] = value;
    while(x1>1){//base base case
        x1 /= 2;
        tree[y1][x1] = tree[y1][2*x1]+tree[y1][2*x1+1]; 
    }//tree[y1] is verified
    while(y1>1){//
        y1 /= 2;
        x1 = x-1+N;
        tree[y1][x1] = tree[y1*2][x1] + tree[y1*2+1][x1]; // base case
        while(x1>1){//WARNING : tree[y1=y1/2][x1] is not updated So you must update data upon this code
            x1 /= 2; // this only update after tree[y1=y1/2][x1=x1/2]
            tree[y1][x1] = tree[y1][2*x1]+tree[y1][2*x1+1];
        }
    }
}//change (x,y) idx to value and update
//y update { x update }

//must be y1<y2, x1<x2
TYPE query(vector<vector<int>>& tree, int x1, int y1, int x2, int y2){
    TYPE res = 0;
    int x1_recover = x1;
    int x2_recover = x2;
    for(y1+=N-1,y2+=N-1;y1<=y2;y1>>=1,y2>>=1){
        if (y1&1) {
            x1 = x1_recover, x2 = x2_recover;
            for(x1+=N-1,x2+=N-1;x1<=x2;x1>>=1,x2>>=1){
                if (x1&1) {
                    //cout << res << ' ' << y1 << ' ' << y2 << ' ' << x1 << ' ' << x2 << endl;
                    res += tree[y1][x1++];
                }
                if (!(x2&1)) {
                    //cout << res << ' ' << y1 << ' ' << y2 << ' ' << x1 << ' ' << x2 << endl;
                    res += tree[y1][x2--];
                }
                
            }
            y1++;
            //res += seg[y1++];
        }
        if (!(y2&1)) {
            x1 = x1_recover, x2 = x2_recover;
            for(x1+=N-1,x2+=N-1;x1<=x2;x1>>=1,x2>>=1){
                if (x1&1) {
                    //cout << res << ' ' << y1 << ' ' << y2 << ' ' << x1 << ' ' << x2 << endl;
                    res += tree[y2][x1++];
                }
                if (!(x2&1)) {
                    //cout << res << ' ' << y1 << ' ' << y2 << ' ' << x1 << ' ' << x2 << endl;
                    res += tree[y2][x2--];
                }
                //cout << res << endl;
            } 
            y2--;
            //res += seg[y2--];
        }
        
    }
    return res;
} //{solve y1~y2 solve{x1~x2}} 
int main(){
    cin >> N >> M;
    int h = 2*N;
    yTree.resize(h);
    vector<vector<int>> debug_segtree(h,vector<int>(h,0));
    for(int i = 0; i < h; ++i) yTree[i].resize(h);
    
    
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cin >> arr[i][j];
            //update(yTree, j, i, arr[i][j]);

        }
    }
    init_tree_build(debug_segtree);
    //debug_seg_tree(yTree);
    //debug_seg_tree(debug_segtree);
    for(int i = 0; i < M; ++i){
        int w;
        cin >> w;
        if (w){
            //query
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            //cout << query(yTree, x1, y1, x2, y2) << '\n';
            cout << query(debug_segtree, y1, x1, y2, x2) << '\n';
        }
        else {
            //update
            int x, y, c;
            cin >> x >> y >> c;
            update(yTree, y, x, c);
            //update(debug_segtree, x, y, c);
        }
    }
    return 0;
}

/*
feedback:
x,y loc of function confusing ( function(y,x) but input function(x,y))
if condition checking (wrote l&1 wrong as l^1)
loop base condition checking (2D segtree -> base base case & base case is different)
tree init must be handled seperately(if you update them N*N, N*N*(logN)^2 and boom)
*/