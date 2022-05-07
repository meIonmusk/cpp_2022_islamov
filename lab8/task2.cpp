#include <iostream>
#include <algorithm>
#include <fstream>

unsigned min_len(int* arr, unsigned n){
    std::sort(arr, arr + n);
    auto len1 = arr[1] - arr[0];
    auto len = (n > 2) ? arr[2] - arr[0] : len1;
    for (unsigned i = 3; i < n; i++){
        auto len2 = len;
        len = std::min(len1, len) + arr[i] - arr[i - 1];
        len1 = len2;
    }
    return len;
}

int main(){
    int arr[100] = {0};
    unsigned n = 0;
    std::string a;
    std::getline(std::cin, a);
    std::ofstream fout("data.txt");
    fout << a;
    fout.close();
    std::ifstream fin("data.txt");
//    unsigned i = 0;
    while (fin >> arr[n])
        n++;
    fin.close();
    std::cout << min_len(arr, n);
    return 0;
}