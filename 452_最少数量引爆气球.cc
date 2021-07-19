#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int findMinArrowShots(vector<vector<int>> &points) {
    if (points.empty()) return 0;
    sort(points.begin(), points.end(),
         [](vector<int> &a, vector<int> &b) { return a[1] < b[1]; });

    int size = points.size();
    int res = 1;
    int pos = points[0][1];
    for (int i = 1; i < points.size(); i++) {
      if (points[i][0] > pos) {
        pos = points[i][1];
        res++;
      }
    }
    return res;
  }
};

int main() {
  vector<vector<int>> test = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
  Solution s;
  std::cout << "Test result: " << s.findMinArrowShots(test) << std::endl;
  return 0;
}