/*
 * 题目描述：
   给定一个链表，如果有环路，找出环路的开始点的值。
 */

#include <vector>
#include <iostream>

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int value): val(value), next(nullptr){}
};

ListNode *detectCycle(ListNode *head) {
  ListNode *slow = head, *fast = head;
  // 此写法有问题， while(fast != slow)， 因为会先判断二者是否相等，不进入循环
  do {
    if (fast == nullptr || fast->next == nullptr) return nullptr;
    fast = fast->next->next;
    slow = slow->next;
  } while (fast != slow);
  // 当确实存在环的时候，让快指针指向head
  fast = head;
  while (fast != slow) {
    fast = fast->next;
    slow = slow->next;
  }
  return fast;
}

int main(){
  // 新建带环一个链表，值分别为3204，在pos=1的位置
  std::vector<int> nums = {3,2,0,4};
  int size = nums.size();
  ListNode *head = new ListNode(0);// 搞一个空节点
  ListNode *cur = head;
  for(int i=0; i<size; ++i){
    cur->next = new ListNode(nums.at(i));// 采用尾部插入法
    cur = cur->next;
    if(i == 3){
      cur->next = head->next->next;
    }
  }
  auto pos = detectCycle(head->next);
  std::cout << "pos value: " << pos->val << std::endl;
  return 0;
}