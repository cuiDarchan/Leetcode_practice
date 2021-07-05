#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    if(intervals.empty()) return 0;
    // 保留内部区间尾数越小的值，这样留给其他区间更多空间，升序
    sort(intervals.begin(), intervals.end(),
         [](vector<int> &a, vector<int> &b) { return a[1] < b[1]; });
    int removed = 0, size = intervals.size();
    int prev = intervals[0][1];
    for (int i = 1; i < size; i++) {
      if (intervals[i][0] < prev) {
        ++removed;
      } else {
        prev = intervals[i][1];
      }
    }
    return removed;
  }
};

int main() {
  vector<vector<int>> test = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
  Solution s;
  std::cout << "Test result: " << s.eraseOverlapIntervals(test) << std::endl;
  return 0;
}