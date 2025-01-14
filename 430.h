/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        auto current = head;
        Node* next = nullptr;
        while (current) {
            next = current ->next;
            if (current->child) {
                current->next = current->child;
                current->child = nullptr;
                current->next->prev= current;
                current = flatten(current);
                while(current->next) {
                    current = current->next;
                }
                if (next){
                    current->next = next;
                    next->prev = current;
                }
            }
            current = next;
        }
        return head;
    }
};