#include <iostream>

unsigned long long task2(){
    unsigned long long n;
    unsigned long long sum = 0;
    unsigned long long deg = 2;
    unsigned i = 1;

    std::cin >> n;
    while (i < 62){
        sum += ((n / deg) - (n / (2 * deg))) * i;
        deg *= 2;
        i++;
    }
    return sum;
}

int main() {
    std::cout << task2();
    return 0;
}
