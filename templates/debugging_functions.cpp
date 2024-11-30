#include <iostream>
    #include <vector>
    #include <utility>
    #include <string>
    #include <cmath>
    #include <cassert>
    #define TYPE pair<int, int>
    #define FASTIO cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false)
    using namespace std;
    // debuging functions
    template<typename T1, typename T2>
    ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
    template<typename T1>
    ostream& operator<<(ostream& os, const vector<T1>& v) {
        for(int i = 0; i < v.size(); ++i){
            os << v[i] << ' ';
        }os << '\n';
        return os;
    }
    void vector_printer(vector<int> &a){
        cout << "vector_printer debug\n";
        for (int i = 0; i < a.size(); ++i){
            cout << a[i] << ' ';
        }
        cout << endl;
    }
    void printSegmentTree(const std::vector<int>& segment_tree) {
        int n = segment_tree.size();
    
        // Calculate the height of the tree
        int height = std::ceil(std::log2(n + 1)); 
    
        for (int level = 0; level < height; ++level) {
            int start = (1 << level) - 1;                // Start index of the current level
            int end = std::min((1 << (level + 1)) - 2, n - 1); // End index of the current level
    
            // Calculate initial spacing and spacing between elements
            int spacing = (1 << (height - level)) - 1; // Spacing reduces as levels go deeper
            int between_spacing = (1 << (height - level + 1)) - 1;
    
            // Print initial spacing
            std::cout << std::string(spacing, ' ');
    
            // Print nodes in the current level
            for (int i = start; i <= end; ++i) {
                std::cout << segment_tree[i];
                if (i < end) {
                    // Print spacing between elements
                    std::cout << std::string(between_spacing, ' ');
                }
            }
            std::cout << "\n"; // Move to the next level
        }
    }
    // debuging functions
    