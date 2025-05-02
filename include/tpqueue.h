// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
 private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    
    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Вставка элемента в очередь
    void push(const T& item) {
        Node* newNode = new Node(item);
        if (!head || comparePriorities(item, head->data)) {
            // вставляем в начало
            newNode->next = head;
            head = newNode;
        } else {
            // ищем позицию для вставки
            Node* current = head;
            while (current->next && comparePriorities(current->next->data, item)) {
                current = current->next;
            }
            // вставляем после current
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Извлечение элемента из очереди
    T pop() {
        if (!head) {
            throw std::out_of_range("Очередь пуста");
        }
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        return data;
    }

    bool empty() const {
        return head == nullptr;
    }

private:
    bool comparePriorities(const T& first, const T& second) {
        return first.prior > second.prior;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
