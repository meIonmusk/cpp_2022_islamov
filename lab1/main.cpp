#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

class Game{
protected:
    int n;
    int m;
    int count;
    int** field;
    int* positions;
    long long seed;
    std::default_random_engine rnd_eng;

    void move(){
//        show_field();
        for (int i = 0; i < count; i++) {
            auto y = positions[2 * i];
            auto x = positions[2 * i + 1];

            if (field[y][x] + field[y + 1][x] + field[y][x + 1] + field[y - 1][x] + field[y][x - 1] > 1)
                field[y][x] = 2;
        }

        int step[2] = {-1, 1};
        for (int i = 0; i < count; i++) {
            auto y = positions[2 * i];
            auto x = positions[2 * i + 1];
            if (field[y][x] != 2) {
                int dy = rand(-1, 1, rnd_eng);
                int dx = rand(0, 1, rnd_eng);
                int y_1 = y + dy;
                int x_1 = x + (1-abs(dy))*step[dx];

                if (field[y_1][x_1]){
                    field[y][x] = 2;
                    field[y_1][x_1] = 2;
                }
                else{
                    positions[2*i] = y_1;
                    positions[2*i+1] = x_1;
                    field[y][x] = 0;
                    field[y_1][x_1] = 1;
                }
            }
        }
    }

    static long long set_seed(long long seed_ = 0){
        auto current_time =
                std::chrono::system_clock::now().time_since_epoch();

        return (seed_)?
                seed_ :
                std::chrono::duration_cast<std::chrono::microseconds>(current_time).count();
    }

    static int rand(int a, int b, std::default_random_engine &rnd_eng){
        std::uniform_int_distribution<int> dstr(a, b);
        return dstr(rnd_eng);
    }

    void set_field(){
        auto sizey = n + 2;
        auto sizex = m + 2;
        for (int i = 0; i < sizey; i++)
            for (int j = 0; j < sizex; j++)
                field[i][j] = 0;
        for (int i = 0; i < sizey; i++){
            field[i][0] = 2;
            field[i][sizex - 1] = 2;
        }
        for (int i = 0; i < sizex; i++) {
            field[0][i] = 2;
            field[sizey - 1][i] = 2;
        }

    }

    void show_field(){
        for (int i = 0; i < n+2; i++){
            for (int j = 0; j < m+2; j++){
                cout << field[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void set_dislocations(){
        if (count == 1){
            positions[0] = (n + 2) / 2;
            positions[1] = (m + 2) / 2;
            field[positions[0]][positions[1]] = 1;
        }
        else
            for (int i = 0; i < count; i++) {
                do {
                    positions[2*i] = rand(1, n, rnd_eng);
                    positions[2*i+1] = rand(1, m, rnd_eng);
                } while (field[positions[2*i]][positions[2*i+1]]);

                field[positions[2*i]][positions[2*i+1]] = 1;
            }
    }

    bool check(){
        bool flag = false;
        for (int i = 1; i < n+2; i++) {
            for (int j = 1; j < m+2; j++){
                if (field[i][j] == 1) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                break;
        }
        return flag;
    }

public:
    Game(int n_ = 5, int m_ = 5, int count_ = 2, long long seed_ = 0){
        if (count_ > n_ * m_)
            count_ = n_ * m_;
        n = n_;
        m = m_;
        count = count_;
        seed = set_seed(seed_);
        std::default_random_engine rnd_eng_(seed);
        rnd_eng = rnd_eng_;
        field = new int *[n+2];
        for (int i = 0; i < n+2; i++)
            field[i] = new int [m+2];
        positions = new int [2*count];
        set_field();
        set_dislocations();
    }

    long long start(){
        long long steps = -1;
        while (check()){
            move();
            if (steps > 5000000)
                break;
            steps++;
        }
//        show_field();
        return steps;
    }

    auto get_seed() const{
        return seed;
    }

    auto get_m() const{
        return m;
    }

    auto get_n() const{
        return n;
    }

    auto get_count() const {
        return count;
    }

    ~Game(){
        for (int i = 0; i < n+2; i++)
            delete[] field[i];
        delete [] field;
        delete [] positions;
    }
};

class LineGame: public Game
{
protected:
    void move(){
//        show_field();
        for (int i = 0; i < count; i++) {
            auto y = positions[2 * i];
            auto x = positions[2 * i + 1];

            if (field[y][x] + field[y][x + 1] + field[y][x - 1] > 1)
                field[y][x] = 2;
        }

        int step[2] = {-1, 1};
        for (int i = 0; i < count; i++) {
            auto y = positions[2 * i];
            auto x = positions[2 * i + 1];
            if (field[y][x] != 2) {
                int dx = rand(0, 1, rnd_eng);
                int x_1 = x + step[dx];

                if (field[y][x_1]){
                    field[y][x] = 2;
                    field[y][x_1] = 2;
                }
                else {
                    positions[2 * i + 1] = x_1;
                    field[y][x] = 0;
                    field[y][x_1] = 1;
                }
            }
        }
    }

public:
    LineGame(int m_, int count_)
            : Game(1, m_, count_)
    {
    }

    long long start(){
        long long steps = -1;
        while (check()){
            move();
            if (steps > 5000000)
                break;
            steps++;
        }
//        show_field();
        return steps;
    }
};

void task1(){
    for (int i = 2; i < 1002; i+=25) {
        Game a{i, i, 1};
        ofstream file_out("task1_stat", ios_base::app);

        file_out << "seed: " << a.get_seed() << "; size_of_field: " << a.get_n() << "x" << a.get_m()
                 << "; num_of_dislocations: " << a.get_count() << "; steps: " << a.start() << "\n";
        file_out.close();
    }
}

void task2() {
    for (int i = 2; i < 1002; i+=10) {
        auto max = (i/5 > 1)? i/5 : 1;
        for (int count = 1; count < i; count+=max){
            Game a{i, i, count};
            ofstream file_out("task2_stat", ios_base::app);

            file_out << "seed: " << a.get_seed() << "; size_of_field: " << a.get_n() << "x" << a.get_m()
                     << "; num_of_dislocations: " << a.get_count() << "; steps: " << a.start() << "\n";
            file_out.close();
        }

    }
}

void task3(){
    for (int i = 2; i < 2102; i+=50) {
        LineGame a{ i, 1};
        ofstream file_out("task3_stat", ios_base::app);

        file_out << "seed: " << a.get_seed() << "; size_of_field: " << a.get_n() << "x" << a.get_m()
                 << "; num_of_dislocations: " << a.get_count() << "; steps: " << a.start() << "\n";
        file_out.close();
    }
}

int main(){
    task2();
    task1();
    task3();
    return 0;
}
