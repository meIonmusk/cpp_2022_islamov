#include <iostream>

struct ListPair {
    int data;
    ListPair *tail;
};

/*void add_after(ListPair *&head, int data){
    auto new_element = new ListPair;
    new_element -> data = data;
    if (head == nullptr){
        head = new_element;
        return;
    }
    new_element -> tail = head -> tail;
    head -> tail = new_element;
}*/

void add_head(ListPair *&head, int data){
    auto new_element = new ListPair;
    new_element -> data = data;
    new_element -> tail = head;
    head = new_element;
}

void reverse_list(ListPair *&head){
    if (head != nullptr) {
        auto head_ = head;
        auto tail = head->tail;
        head->tail = nullptr;
        ListPair *tail_;
        while (tail != nullptr) {
            tail_ = tail->tail;
            tail->tail = head_;
            head_ = tail;
            tail = tail_;
        }
        head = head_;
    }
}


int main() {
    ListPair *head = nullptr;

    int data = 1;

    while (data){
        std::cin >> data;
        if (data)
            add_head(head, data);
    }

    reverse_list(head);

    while (head != nullptr){
        std::cout << head -> data << '\n';
        auto tail = head -> tail;
        delete head;
        head = tail;
    }

    return 0;
}
