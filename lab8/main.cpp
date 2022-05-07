#include <iostream>
#include <limits>

unsigned max_len_search(int *arr, unsigned n){
    auto elements = new int [n + 2];
    elements[0] = std::numeric_limits<int>::min();
    unsigned len = 1;
    for (int *e = elements + 1; e < elements + n + 2; e++)
        *e = std::numeric_limits<int>::max();

    for (int i = 0; i < n; i++)
        for (int j = 1; j <= i + 1; j++)
            if (arr[i] > elements[j - 1] and arr[i] < elements[j]) {
                elements[j] = arr[i];
                if (j > len)
                    len = j;
            }

    delete [] elements;
    return len;
}

int main() {
    unsigned n;
    std::cin >> n;
    auto arr = new int [n];
    for (unsigned i = 0; i < n; i++)
        std::cin >> arr[i];
    std::cout << max_len_search(arr, n);
    delete [] arr;
    return 0;
}