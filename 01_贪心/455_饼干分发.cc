#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        std::sort(g.begin(),g.end()); // 默认升序
        std::sort(s.begin(),s.end());
        int child = 0, cookie = 0;
        while(child < g.size() && cookie < s.size()){
            if(g[child] <= s[cookie]) ++child;
            ++cookie;
        }
        return child;
    }   
};

int main(){
    vector<int> g = {1,2,3,4,5,6,7};
    vector<int> s = {2,3,4,5,6,5,4};
    
    Solution solution;
    int res = solution.findContentChildren(g,s);
    std::cout << "result:" << res<< std::endl;
    return 0;
}