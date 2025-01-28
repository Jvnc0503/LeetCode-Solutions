#include <random>

struct Node {
    int val;
    Node* next;
    Node* down;

    Node(int val = 0, Node* next = nullptr, Node* down = nullptr) : val(val), next(next), down(down) {}
};

class Skiplist {
    Node* head;
    int height = 1;
    int nums = 0;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist{0, 1};

public:
    Skiplist() : head(new Node()) {}

    bool search(int target) {
        Node* ptr = head;
        while (ptr) {
            while (ptr->next && ptr->next->val < target) {
                ptr = ptr->next;
            }
            if (ptr->next && ptr->next->val == target) {
                return true;
            }
            ptr = ptr->down;
        }
        return false;
    }

    int getLevel() {
        int level = 1;
        while (dist(mt) && level < height + 1) {
            ++level;
        }
        return level;
    }
    
    void add(int num) {
        int level = getLevel();
        if (level > height) {
            head = new Node(0, nullptr, head);
            ++height;
        }

        Node* ptr = head;
        Node* prev = nullptr;

        for (int i = height; i > 0; --i) {
            while (ptr->next && ptr->next->val < num) {
                ptr = ptr->next;
            }
            if (i <= level) {
                ptr->next = new Node(num, ptr->next, nullptr);
                if (prev) {
                    prev->down = ptr->next;
                }
                prev = ptr->next;
            }
            ptr = ptr->down;
        }
        ++nums;
    }
    
    bool erase(int num) {
        Node* ptr = head;
        bool found = false;

        while (ptr) {
            while (ptr->next && ptr->next->val < num) {
                ptr = ptr->next;
            }
            if (ptr->next && ptr->next->val == num) {
                Node* temp = ptr->next;
                ptr->next = ptr->next->next;
                delete temp;
                found = true;
            }
            ptr = ptr->down;
        }

        while (head->next == nullptr && head->down) {
            Node* temp = head;
            head = head->down;
            delete temp;
            --height;
        }

        if (found) {
            --nums;
        }

        return found;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */