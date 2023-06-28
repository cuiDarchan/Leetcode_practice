
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

ListNode* reverseList(ListNode* head) {
  if (head == nullptr) return nullptr;
  ListNode *cur = head->next, *prev = head;
  prev->next = nullptr;
  while (cur) {
    // 先记住第三个节点
    ListNode* next = cur->next;
    // 打断，重新指向前一个
    cur->next = prev;
    // prev cur 后移一位
    prev = cur;
    cur = next;
  }
  return prev;
}

int main(){
    std::vector<int> input;
    ListNode* head = new ListNode(1), *p = head;
    input.push_back(1);
    for(int i=2 ;i<6; ++i){
        p->next = new ListNode(i);
        input.push_back(i);
        p = p->next;
    }
    std::cout << "input: ";
    for(int i =0; i<input.size();++i){
        std::cout << input[i] << ",";
    }
    std::cout << std::endl;

    auto reverse_head = reverseList(head);
    std::cout << "reverse: ";
    while(reverse_head){
        std::cout << reverse_head->val << ",";
        reverse_head = reverse_head->next;
    }
    std::cout << std::endl;

    /// 结果
    // input: 1,2,3,4,5
    // reverse: 5,4,3,2,1
    return 0;
}