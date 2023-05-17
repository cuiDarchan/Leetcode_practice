/*
 * 题目描述：
   给定一个二维的 0-1 矩阵，如果第 (i, j) 位置是 1，则表示第 i 个人和第 j 个人是朋友。已知
朋友关系是可以传递的，即如果 a 是 b 的朋友， b 是 c 的朋友，那么 a 和 c 也是朋友，换言之这
三个人处于同一个朋友圈之内。求一共有多少个朋友圈。
 */

#include <vector>
#include <iostream>
using std::vector;


// 辅函数: 递归实现，目的是修改visited数组
void DFS(vector<vector<int>>& grid, const int& i, vector<bool>& visited){
    visited[i] = true; // 标记为已访问
    for(int j=0; j<visited.size(); ++j){
        if(grid[i][j] == 1 && !visited[j]){
            DFS(grid, j, visited);
        }
    }
}


// 主函数
int FindCircleNum(vector<vector<int>>& grid){
    // 与695不同之处在于， 695题总共m*n个节点，每个节点需要验证上下左右四个边
    // 本题相当于只有n个节点，每个节点只有一条边
    int n = grid.size();
    if(!n) return 0;
    vector<bool> visited(n, false);// 标记数组，初始化代表每一个节点都没有被遍历过
    int count = 0;
    for(int i =0 ;i<n ;++i){
        // 如果并没有被遍历过，则开始
        if(!visited.at(i)){
            DFS(grid, i, visited);
            count++;
        }
    }
    return count;
}


int main(){
    vector<vector<int>> test = {{1, 1, 0},
                                {1, 1, 0},
                                {0, 0, 1}};
    auto res = FindCircleNum(test);
    std::cout << "test res: " << res << std::endl;
    return 0;
}