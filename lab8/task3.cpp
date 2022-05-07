#include <iostream>
#include <limits>

int64_t min_energy(int64_t *platforms, unsigned n){
    if (n <= 1)
        return 0;
    int64_t waste1 = 0;
    int64_t waste = abs(platforms[1] - platforms[0]);
    for (unsigned i = 2; i < n; i++) {
        int64_t waste2 = waste;
        waste = std::min(waste + llabs(platforms[i] - platforms[i - 1]),
                         waste1 + 3 * llabs(platforms[i] - platforms[i - 2]));
        waste1 = waste2;
    }
    return waste;
}

int main() {
    unsigned n;
    std::cin >> n;
    auto platforms = new int64_t [n];
    for (unsigned i = 0; i < n; i++)
        std::cin >> platforms[i];
    std::cout << min_energy(platforms, n);
    delete [] platforms;
    return 0;
}
