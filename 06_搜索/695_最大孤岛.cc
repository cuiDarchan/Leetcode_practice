/*
 * 题目描述： 给定一个二维的 0-1 矩阵，其中 0 表示海洋， 1 表示陆地。单独的或相邻的陆地可以形成岛
   屿，每个格子只与其上下左右四个格子相邻。求最大的岛屿面积。
 */

#include <vector>
#include <stack>
#include <utility>
#include <iostream>
using std::vector;
using std::pair;

/// 法一： 使用stack
int MaxIslandArea(vector<vector<int>> &grid){
    int m = grid.size();
    int n = m? grid[0].size(): 0;
    int local_area = 0, area = 0, x, y;
    // trick: 孤岛上下左右顺时针索引正好为(-1,0),(0,1),(1,0),(0,-1),
    vector<int> direction = {-1, 0, 1, 0, -1};
    for(int i = 0; i<m; ++i){
        for(int j = 0; j<n;++j){
            if(grid.at(i).at(j)){
                grid[i][j] = 0;
                local_area = 1;
                // 栈 等效于递归
                std::stack<pair<int , int >> island;
                island.push({i,j});
                while(!island.empty()){
                    auto top = island.top();
                    island.pop();
                    for(int d = 0; d < 4; ++d){
                        x = top.first + direction[d];
                        y = top.second + direction[d+1];
                        if(x >= m || x< 0 || y>=n || y<0) continue;
                        if(grid[x][y]){
                            grid[x][y] =0; //别忘记，作用类似于标记数组，但是实际修改了原始输入
                            island.push({x,y});
                            local_area++;
                        }
                    }
                }
                area = std::max(local_area, area);
            }
        }
    }
    return area;
}

/// 法二: 递归算法 主函数+辅函数
// 辅函数：递归第一种写法, 目的当前坐标(x,y)上下左右所能达到求最大面积
int DFS(vector<vector<int>> &grid, const int& x, const int& y){
    if(!grid[x][y]) return 0;
    grid[x][y] = 0; //**修改标记
    int area = 1, l, r;
    vector<int> direction = {-1, 0, 1, 0, -1};
    for(int i=0; i<4; ++i){
        l = x + direction[i];
        r = y + direction[i+1];
        if(l < grid.size() && l>=0 && r <grid[0].size() && r>=0){
            area += DFS(grid, l, r);
        }
    }
    return area;
}

// 主函数
int MaxIslandArea2(vector<vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) return 0;
  int max_area = 0;
  int m = grid.size(), n = grid[0].size();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j]) {
        max_area = std::max(max_area, DFS(grid, i, j));
      }
    }
  }
  return max_area;
}



/// 法三： 递归算法2 主函数+辅函数
// 辅函数：递归第二种写法
// 先判断是否越界，再对各个方向求面积，再加
int DFS2(vector<vector<int>> &grid, const int& x, const int& y){
    if(x >= grid.size() || x<0 || y>=grid[0].size() || y<0 || grid[x][y] == 0) return 0;
    grid[x][y] = 0; // **别忘了标记
    return 1 + DFS2(grid, x-1, y) + DFS2(grid, x, y+1) + DFS2(grid, x+1, y) + DFS2(grid, x, y-1);
}

// 主函数
int MaxIslandArea3(vector<vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) return 0;
  int max_area = 0;
  int m = grid.size(), n = grid[0].size();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j]) {
        max_area = std::max(max_area, DFS2(grid, i, j));
      }
    }
  }
  return max_area;
}

int main() {
  vector<vector<int>> test = {{1, 0, 1, 1, 0, 1, 0, 1},
                              {1, 0, 1, 1, 0, 1, 1, 1},
                              {0, 0, 0, 0, 0, 0, 0, 1}};
  auto test2 = test;
  auto test3 = test;
  auto res = MaxIslandArea(test);
  std::cout << "Test1 , res: " << res << std::endl;
  res = MaxIslandArea2(test2);
  std::cout << "Test2 , res: " << res << std::endl;
  res = MaxIslandArea3(test3);
  std::cout << "Test3 , res: " << res << std::endl;
  return 0;
}