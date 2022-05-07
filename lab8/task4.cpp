#include <iostream>
#include <string>

int all_traces(std::string *arr, unsigned n, std::string pos){
    int field[64];
    for (int & i : field)
        i = 1;
    for (unsigned i = 0; i < n; i++)
        field[(arr[i][1] - '1') * 8 + arr[i][0] - 'a'] = -1;
    for (int i = 6; i >= 0; i--)
        for (unsigned j = 0; j < 8; j++){
            auto f1 = (j > 0)? (field[8 * (i + 1) + j - 1] < 0) ? -field[8 * (i + 1) + j - 1] : 0 : 0;
            auto f3 = (j < 7)? (field[8 * (i + 1) + j + 1] < 0) ? -field[8 * (i + 1) + j + 1] : 0 : 0;
            auto f2 = (field[8 * (i + 1) + j] > 0) ? field[8 * (i + 1) + j] : 0;
            field[8 * i + j] = field[8 * i + j] * (f1 + f2 + f3);
        }

    return field[(pos[0] - 'a') + 8 * (pos[1] - '1')];
}


int main(){
    unsigned n;
    std::cin >> n;
    auto arr = new std::string [n];
    for (unsigned i = 0; i < n; i++)
        std::cin >> arr[i];
    std::string pos;
    std::cin >> pos;
    std::cout << all_traces(arr, n, pos);
    delete [] arr;
    return 0;

}