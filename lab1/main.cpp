#include <iostream>
#include <cstdlib>
//#include <random>

//std::default_random_engine rnd_eng(56);
//std::uniform_real_distribution<double> dstr(1.0,4.0);

//bool maybe(double prob){
//    return dstr(rnd_eng) <= prob;
//}

using namespace std;
/* 1. квадрат с 1 дислокацией. Вывести график времени установления от размера поля.
 * 2. квадрат с n дислокациями. Вывести зависимость времени установления от соотношения размера поля и кол-ва дислокаций.
 * 3. проверка одномерного случая.*/

void field(int** m, int n, int const* pos, int count) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = 0;

    for (int i = 0; i < n; i++){
        m[0][i] = 2;
        m[n-1][i] = 2;
        m[i][0] = 2;
        m[i][n-1] = 2;
    }
    for (int i = 0; i < count; i++)
        m[pos[2*i]] [pos[2*i+1]] = 1;
}

void move(int** m, int n, int* pos, int count){
    for (int i = 0; i < count; i++)
        if (m[pos[2*i]][pos[2*i+1]]+m[pos[2*i]+1][pos[2*i+1]]+m[pos[2*i]][pos[2*i+1]+1]+m[pos[2*i]-1][pos[2*i+1]]+m[pos[2*i]][pos[2*i+1]-1] > 1)
            m[pos[2*i]][pos[2*i+1]] = 2;
    int step[2] = {-1, 1};
    for (int i = 0; i < count; i++) {
        if (m[pos[2*i]][pos[2*i+1]] != 2) {
            int p1 = rand() % 3 - 1;
            int p2 = rand() % 2;
            int p_1 = pos[2*i] + p1;
            int p_2 = pos[2*i+1] + (1-abs(p1))*step[p2];
//            pos[2*i] += p1;
//            pos[2*i+1] += (1-abs(p1))*step[p2];
            if (m[p_1][p_2]){
                m[pos[2*i]][pos[2*i+1]] = 2;
                m[p_1][p_2] = 2;
            }
            else{
                pos[2*i] = p_1;
                pos[2*i+1] = p_2;
            }
        }
    }
    field(m, n, pos, count);
    for (int i = 0; i < count; i++)
        if (m[pos[2*i]][pos[2*i+1]]+m[pos[2*i]+1][pos[2*i+1]]+m[pos[2*i]][pos[2*i+1]+1]+m[pos[2*i]-1][pos[2*i+1]]+m[pos[2*i]][pos[2*i+1]-1] > 1)
            m[pos[2*i]][pos[2*i+1]] = 2;
}

bool chek(int** m, int n){
    bool flag = false;
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < n-1; j++){
            if (m[i][j] == 1) {
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }
    return flag;
}

int game(int p, int count) {
    unsigned steps = 0;
//    int p = 5;
    int n = p + 2;
//    int count = 2;
    int** m = new int *[n];
    for (int i = 0; i < n; i++)
        m[i] = new int [n];

    int* pos = new int [count];
    for (int i = 0; i < count; i++) {
        do {
            pos[2 * i] = rand() % p + 1;
            pos[2 * i + 1] = rand() % p + 1;
        } while (m[pos[2*i]][pos[2*i+1]]);
//        while (m[pos[2*i]][pos[2*i+1]]) {
//            pos[2 * i] = rand() % p + 1;
//            pos[2 * i + 1] = rand() % p + 1;
//        }
        m[pos[2*i]][pos[2*i+1]] = 1;
    }
    field(m, n, pos, count);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << m[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
    while (chek(m, n)){
        move(m, n, pos, count);
        steps++;
        if (steps > 10000)
            break;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << m[i][j] << " ";
        std::cout << "\n";
    }

    for (int i = 0; i < n; i++)
        delete[] m[i];
    delete [] m;
    delete [] pos;
    std::cout << steps;
    return 0;
}

int main(){
    auto seed = time(nullptr);
    srand(seed);
    int p = 5;
    int count = 2;
    for (int i = 0; i < 5; i++)
        game(p, count);
    return 0;
}