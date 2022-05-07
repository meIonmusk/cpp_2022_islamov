#include <iostream>
using std::cout;
using std::endl;

const unsigned int N = 5;
const int left[N]  = {5, 4, 3, 2, 1}; // command code 1
const int right[N] = {1, 2, 3, 4, 5}; // command code 2
const int back[N]  = {1, 1, 1, 1, 1}; // command code 3
const int meow[N]  = {3, 2, 3, 2, 5}; // command code 4

void recognize(int* data_start, int* data_end, int* command, int** frame);
// Здесь ваша реализация функции. Можете писать свои вспомогательные функции, только не забудьте их тоже отправить.

void recognize(int* data_start, int* data_end, int* command, int** frame){
    *command = 0;
    for (int* i = data_start; i < data_end - N + 1; i++) {
        int idx = 0;
        auto j = i;
        while (*j == left[idx]) {
            idx++;
            j++;
            if (idx == N){
                *frame = i;
                *command = 1;
                return;
            }
        }
        j = i;
        idx = 0;

        while (*j == right[idx]) {
            idx++;
            j++;
            if (idx == N){
                *frame = i;
                *command = 2;
                return;
            }
        }
        j = i;
        idx = 0;

        while (*j == back[idx]) {
            idx++;
            j++;
            if (idx == N){
                *frame = i;
                *command = 3;
                return;
            }
        }
        j = i;
        idx = 0;

        while (*j == meow[idx]) {
            idx++;
            j++;
            if (idx == N){
                *frame = i;
                *command = 4;
                return;
            }
        }
    }
}

int main()
{
    const int L = 21;
    int mindstream[L] = {5, 4, 3};
    int command = -1;
    int* frame = mindstream;
    int* end = mindstream + L;
    while (command)
    {
        recognize(frame, end, &command, &frame);
        if (!command) break;
        switch(command)
        {
            case 1:
                cout << "left ";
                break;
            case 2:
                cout << "right ";
                break;
            case 3:
                cout << "back ";
                break;
            case 4:
                cout << "MEOOOOW ";
                break;
        }
        frame += N;
    }
    cout << endl;
//    cout << command;
    return 0;
}