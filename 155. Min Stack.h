template<typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {
    }

    Node(T data) : data(data) {
    }

    Node(Node<T> *next) : next(next) {
    }

    Node(T data, Node<T> *next) : data(data), next(next) {
    }
};

template<typename T>
class List {
    Node<T> *head;

public:
    List() : head(nullptr) {
    }

    ~List() {
        auto temp = head;
        while (temp) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
    }

    T front() {
        if (head) {
            return head->data;
        }
        return T();
    }

    void push_front(T data) {
        auto front = new Node<T>(data);
        front->next = head;
        head = front;
    }

    void pop_front() {
        if (head) {
            auto temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() {
        return head == nullptr;
    }

    T min() {
        if (head) {
            int min = head->data;
            auto temp = head;
            while (temp) {
                if (temp->data < min) {
                    min = temp->data;
                }
                temp = temp->next;
            }
            return min;
        }
        return T();
    }
};

class MinStack {
public:
    List<int> list;
    int *min;

    MinStack() : min(nullptr) {}
    
    ~MinStack() {
        delete min;
    }
    
    void push(int val) {
        list.push_front(val);
        if (min == nullptr) {
            min = new int;
            *min = val;
        } else if (val < *min) {
            *min = val;
        }
    }
    
    void pop() {
        if (!list.empty()) {
            if (list.front() == *min) {
                list.pop_front();
                if (list.empty()){
                    delete min;
                    min = nullptr;
                } else {
                    *min = list.min();
                }
            } else {
                list.pop_front();
            }
        }
    }
    
    int top() {
        return list.front();
    }
    
    int getMin() {
        if (min == nullptr) {
            return int();
        }
        return *min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */