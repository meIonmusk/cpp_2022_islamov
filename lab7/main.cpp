#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <fstream>
// сравнить время работы наивного бинарного поиска и самобалансирующегося
// std::shuffle для неповторяющихся случайных чисел
//using namespace std;

struct BinaryTree{
    int data;
    int height = 1;
    BinaryTree *left_branch = nullptr;
    BinaryTree *right_branch = nullptr;
};

int *create_data(unsigned n, bool shuffle = true){
    auto arr = new int [n];
    for (unsigned idx = 0; idx < n; idx++)
        arr[idx] = idx;

    if (shuffle) {
        unsigned seed = 0;
        std::shuffle(arr, arr + n, std::default_random_engine(seed));
    }

//    for (unsigned idx = 0; idx < n; idx++)
//        std::cout << arr[idx] << ' ';
//    std::cout << "\n\n";

    return arr;
}

void show_tree(BinaryTree* root, std::string space){
    if (root) {
        std::cout << space << root->data << '\n';
        show_tree(root->left_branch, "--" + space);
        show_tree(root->right_branch, "--" + space);
    }
    else
        std::cout << space << '\n';
}

void show_inc_tree(BinaryTree* root){
    if (root){
        show_inc_tree(root->left_branch);
        std::cout << root->data << '\n';
        show_inc_tree(root->right_branch);
    }
}

unsigned long simple_sort(int* data, unsigned n){
    auto tree = new BinaryTree* [n];
    auto root = new BinaryTree;

    auto time = clock();
    root -> data = data[0];
    tree[0] = root;
    for (unsigned idx = 1; idx < n; idx++){
        auto branch = new BinaryTree;
        tree[idx] = branch;
        branch -> data = data[idx];
        root = tree[0];
        while (true){
            if (branch -> data < root -> data){
                if (root -> right_branch)
                    root = root -> right_branch;
                else {
                    root -> right_branch = branch;
                    break;
                }
            } else{
                if (root -> left_branch)
                    root = root -> left_branch;
                else {
                    root -> left_branch = branch;
                    break;
                }
            }
        }
    }
    auto finish_time = clock();
//    show_tree(tree[0], "> ");
//    show_inc_tree(tree[0]);
//    std::cout << '\n';
    for (unsigned idx = 0; idx < n; idx++)
        delete tree[idx];
    delete [] tree;

    return (finish_time - time);
}

int diff(BinaryTree* root){
    int left_height = root->left_branch ? root->left_branch->height : 0;
    int right_height = root->right_branch ? root->right_branch->height : 0;
    return left_height - right_height;
}

void update_height(BinaryTree* root){
    if (!root)
        return;

    int left_height = root->left_branch ? root->left_branch->height : 0;
    int right_height = root->right_branch ? root->right_branch->height : 0;
    root->height = std::max(left_height, right_height) + 1;
}

BinaryTree* rotate_left(BinaryTree* root){
    auto root_right = root->right_branch;
    root->right_branch = root_right->left_branch;
    root_right->left_branch = root;
    update_height(root);
    update_height(root_right);
    return root_right;
}

BinaryTree* rotate_right(BinaryTree* root){
    auto root_left = root->left_branch;
    root->left_branch = root_left->right_branch;
    root_left->right_branch = root;
    update_height(root);
    update_height(root_left);
    return root_left;
}

BinaryTree* balance_tree(BinaryTree* root){
    update_height(root);
    if (diff(root) == 2){
        if (diff(root->left_branch) < 0)
            root->left_branch = rotate_left(root->left_branch);
        return rotate_right(root);
    }else if (diff(root) == -2){
        if (diff(root->right_branch) > 0)
            root->right_branch = rotate_right(root->right_branch);
        return rotate_left(root);
    }
    return root;
}

BinaryTree* insert(BinaryTree* root, BinaryTree* branch){
    if (!root)
        return branch;

    if (branch->data > root->data)
        root->left_branch = insert(root->left_branch, branch);
    else
        root->right_branch = insert(root->right_branch, branch);

    return balance_tree(root);
}

unsigned balanced_sort(int* data, unsigned n) {
    auto tree = new BinaryTree *[n];
    auto root = new BinaryTree;

    auto time = clock();
    root->data = data[0];
    tree[0] = root;
    for (unsigned idx = 1; idx < n; idx++) {
        auto branch = new BinaryTree;
        tree[idx] = branch;
        branch->data = data[idx];
        root = insert(root, branch);
    }
    auto finish_time = clock();
//    show_tree(root, "");
//    show_inc_tree(root);
//    std::cout << '\n';
    for (unsigned idx = 0; idx < n; idx++)
        delete tree[idx];
    delete[] tree;

    return (finish_time - time);
}


void fout(std::string file_name, unsigned n, double time){
    std::ofstream file_out(file_name, std::ios_base::app);
    file_out << n << ' ' << time << '\n';
    file_out.close();
}

void fclear(std::string file_name){
    std::ofstream file(file_name, std::ios_base::out);
    file.close();
}

void fclear_all(){
    fclear("balance_shuffled.txt");
    fclear("simple_shuffled.txt");
    fclear("balance.txt");
    fclear("simple.txt");
}

int main() {
//    fclear_all();
//    return 0;
    int* data;
    for (unsigned idx = 2000; idx < 3000; idx++) {
        data = create_data(idx, true);
        fout("balance_shuffled.txt", idx, balanced_sort(data, idx));
        fout("simple_shuffled.txt", idx, simple_sort(data, idx));

        data = create_data(idx, false);
        fout("balance.txt", idx, balanced_sort(data, idx));
        fout("simple.txt", idx, simple_sort(data, idx));
    }
    delete [] data;

    return 0;
}

