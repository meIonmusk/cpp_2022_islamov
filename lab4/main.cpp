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

void input_list(ListPair *&head){
    int data = 1;

    while (data){
        std::cin >> data;
        if (data)
            add_head(head, data);
    }
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

void cycle_list(ListPair *&head){
    auto head_ = head;
    while (head_->tail != nullptr)
        head_ = head_->tail;

    head_->tail = head; // зацикливаю
}

void input_Flavius(ListPair *&head, int n){
    for (int i = 1; i <= n; i++)
        add_head(head, i);
}

void Flavius(ListPair *&head, int k){
//    if (head->tail == head)
//        return;
    if (k == 1){
        auto head_ = head;
        head = head->tail;
        while (head != head_){
            auto tail = head->tail;
            delete head;
            head = tail;
        }
        return;
    }

    while (head->tail != head) {
        for (int i = 0; i < k - 2; i++)
            head = head->tail;
        auto *tail = head->tail;
        head->tail = tail->tail;
        head = head->tail;
        delete tail;
    }
//    Flavius(head, k);
}

void free_list(ListPair *&head){
    while (head != nullptr){
        std::cout << head -> data << '\n';
        auto tail = head -> tail;
        delete head;
        head = tail;
    }
}

int main() {
    ListPair *head = nullptr;

    int k , n = 0;
    std::cin >> k >> n;

//    input_list(head);
    input_Flavius(head, n);
    reverse_list(head);
    cycle_list(head);

    Flavius(head, k);

//    free_list(head);

    std::cout << head->data;
    delete head;

    return 0;
}
