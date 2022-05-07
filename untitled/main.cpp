#include <iostream>
#include <algorithm>
#include <functional>

struct Cats{
    int pos;
    int len;
};

bool cats_pos_compare(Cats const &lcat, Cats const &rcat){
    return lcat.pos < rcat.pos;
}


int task1(){
    int len = 30;
    int n = 0;
    int l = 0;
    int pos = -1;

    std::cin >> n;
    auto cats = new Cats [n + 2];
    cats[0].pos = 0;
    cats[0].len = 0;

    for (int i = 1; i < n + 1; i++)
        std::cin >> cats[i].pos >> cats[i].len;

    cats[n + 1].pos = len;
    cats[n + 1].len = 0;

    std::cin >> l;

    std::sort(cats, cats + n + 2, cats_pos_compare);

    for (int i = 1; i < n + 2; i++)
        if (cats[i].pos - cats[i - 1].pos - cats[i - 1].len >= l) {
            pos = cats[i - 1].pos + cats[i - 1].len;
            delete [] cats;
            return pos;
        }
    delete [] cats;
    return pos;
}

int main() {
    std::cout << task1();
    return 0;
}
