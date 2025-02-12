/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (head && head->next) {
            auto current = head;
            ListNode* sorted = nullptr;
            while (current) {
                auto next = current->next;
                if (!sorted || sorted->val >= current->val) {
                    current->next = sorted;
                    sorted = current;
                } else {
                    auto temp = sorted;
                    while (temp->next && temp->next->val < current->val) {
                        temp = temp->next;
                    }
                    current->next = temp->next;
                    temp->next = current;
                }
                current = next;
            }
            return sorted;
        }
        return head;
    }
};