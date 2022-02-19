#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

class Game{
private:
    void move(){
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
                }
            }
        }

        update_field();

        for (int i = 0; i < count; i++) {
            auto y = positions[2 * i];
            auto x = positions[2 * i + 1];

            if (field[y][x] + field[y + 1][x] + field[y][x + 1] + field[y - 1][x] + field[y][x - 1] > 1)
                field[y][x] = 2;
        }
    }

protected:
    int n;
    int m;
    int count;
    int** field;
    int* positions;
    long long seed;
    std::default_random_engine rnd_eng;


    static long long set_seed(){
        auto current_time =
                std::chrono::system_clock::now().time_since_epoch();
        return
                std::chrono::duration_cast<std::chrono::seconds>(current_time).count();
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

        for (int i = 0; i < sizex; i++) {
            field[0][i] = 2;
            field[sizex - 1][i] = 2;
        }
        for (int i = 0; i < sizey; i++){
            field[i][0] = 2;
            field[i][sizey - 1] = 2;
        }
    }

    void update_field(){
        for (int i = 1; i < n+1; i++)
            for (int j = 1; j < m+1; j++){
                if (field[i][j] != 2)
                    field[i][j] = 0;
            }
        for (int i = 0; i < count; i++){
            if (field[positions[2*i]] [positions[2*i+1]] != 2)
                field[positions[2*i]] [positions[2*i+1]] = 1;
        }
    }

    void set_dislocations(){
        for (int i = 0; i < count; i++) {
            do {
                positions[2*i] = rand(1, n-1, rnd_eng);
                positions[2*i+1] = rand(1, m-1, rnd_eng);
            } while (field[positions[2*i]][positions[2*i+1]]);

            field[positions[2*i]][positions[2*i+1]] = 1;
        }
        for (int i = 0; i < 2*count; i++)
            cout << positions[i];
        cout << "\n";
        for (int i = 0; i < n+2; i++){
            for (int j = 0; j < m+2; j++){
                cout << field[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool check(){
        bool flag = false;
        for (int i = 1; i < n+2; i++) {
            for (int j = 1; j < n+2; j++){
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
    Game(int n_, int m_, int count_){
        if (count_ > n_ * m_)
            count_ = n_ * m_;
        n = n_;
        m = m_;
        count = count_;
        seed = set_seed();
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
            if (steps > 100000)
                break;
            steps++;
        }
        for (int i = 0; i < n+2; i++){
            for (int j = 0; j < m+2; j++){
                cout << field[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
        return steps;
    }

    long long get_seed() const{
        return seed;
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
                else
                    positions[2*i+1] = x_1;
            }
        }

        set_field();

        for (int i = 0; i < count; i++) {
            auto y = positions[2 * i];
            auto x = positions[2 * i + 1];

            if (field[y][x] + field[y][x + 1] + field[y][x - 1] > 1)
                field[y][x] = 2;
        }
    }

public:
    LineGame(int m_, int count_)
        : Game(1, m_, count_)
        {
        }
};

void task1(){
    for (int i = 2; i < 10; i++) {
//        auto current_time =
//                std::chrono::system_clock::now().time_since_epoch();
//        auto seed =
//                std::chrono::duration_cast<std::chrono::seconds>(current_time).count();
//        std::default_random_engine rnd_eng(seed);

        Game a{i, i, 1};
        ofstream file_out("task1_stat", ios_base::app);

        file_out << "seed: " << a.get_seed() << "; size_of_field: " << i << "x" << i << "; num_of_dislocations: " << 1 << "; steps: " << a.start() << "\n";
        file_out.close();
    }
}

void task3(){
    for (int i = 2; i < 10; i++) {
        LineGame a{ i, 1};
        ofstream file_out("task3_stat", ios_base::app);

        file_out << "seed: " << a.get_seed() << "; size_of_field: " << i << "x" << i << "; num_of_dislocations: " << 1 << "; steps: " << a.start() << "\n";
        file_out.close();
    }
}

//
//int rand(std::default_random_engine &rnd_eng,
//         std::uniform_int_distribution<int> &dstr){
//    return dstr(rnd_eng);
//}
int main(){
    task1();
//    auto current_time =
//            std::chrono::system_clock::now().time_since_epoch();
//    auto seed =
//            std::chrono::duration_cast<std::chrono::seconds>(current_time).count();
//    std::default_random_engine rnd_eng(seed);
//
//
//    for (int i = 0; i < 10; i++){
//        std::uniform_int_distribution<int> dstr(1, 10);
//        cout << rand(rnd_eng, dstr);}
////        cout << dstr(rnd_eng);}

    return 0;
}