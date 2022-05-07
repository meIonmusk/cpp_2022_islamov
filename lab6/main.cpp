#include <iostream>

using namespace std;

unsigned min3(unsigned a, unsigned b, unsigned c){
    return min(min(a, b), c);
}

string track_trace(string trace, unsigned n, unsigned m){
    string trace_;
    unsigned i = n - 1;
    unsigned j = m - 1;
    while (trace[i * m + j] != '0'){
        trace_ += trace[i * m + j];
        int dj = trace[i * m + j] != '2';
        int di = trace[i * m + j] != '1';
        i -= di;
        j -= dj;
    }
    return trace_;
}

unsigned reverse_trans(string a, string b, unsigned n, unsigned m, unsigned M, long **memo, string &trace){
    unsigned f1 = (memo[n][m - 1] + 1) ? memo[n][m - 1] + 1: reverse_trans(a, b, n, m - 1, M, memo, trace) + 1;
    unsigned f2 = (memo[n - 1][m] + 1) ? memo[n - 1][m] + 1: reverse_trans(a, b, n - 1, m, M, memo, trace) + 1;
    unsigned c = a[n - 1] != b[m - 1];
    unsigned f3 = (memo[n - 1][m - 1] + 1) ? memo[n - 1][m - 1] + c: reverse_trans(a, b, n - 1, m - 1, M, memo, trace) + c;
    memo[n][m] = min3(f1, f2, f3);
    trace[n * M + m] = (memo[n][m] == f1) ? '1' : (memo[n][m] == f2) ? '2' : c ? '3' : '4'; // если первую строку преобразуем во вторую, то 1 - вставка 2 - удаление 3 - замена

    return memo[n][m];
}

unsigned forward_trans(string a, string b, string &trace){
    unsigned n = a.length() + 1;
    unsigned m = b.length() + 1;
    trace = "0";
    for (unsigned idx = 1; idx < m; idx++)
        trace += '1';
    auto **mem = new unsigned *[2];
    mem[0] = new unsigned [m];
    mem[1] = new unsigned [m];
    for (unsigned i = 0; i < m; i++)
        mem[0][i] = i;
    for (unsigned i = 1; i < n; i++) {
        mem[1][0] = i;
        trace += '2';
        for (unsigned j = 1; j < m; j++) {
            mem[1][j] = min3(mem[1][j - 1] + 1, mem[0][j] + 1, mem[0][j - 1] + (a[i - 1] != b[j - 1]));
            char c = (mem[1][j] == mem[1][j - 1] + 1) ? '1' : (mem[1][j] == mem[0][j] + 1) ? '2' : (a[i - 1] != b[j - 1]) ? '3' : '4'; // если первую строку преобразуем во вторую, то 1 - вставка 2 - удаление 3 - замена
            trace += c;
        }
        for (unsigned j = 0; j < m; j++)
            mem[0][j] = mem[1][j];
    }
    unsigned p = mem[1][m - 1];

    delete [] mem[0];
    delete [] mem[1];
    delete [] mem;
    return p;
}

int main() {
    string a;
    string b;
    string trace1 = "0";
    string trace2;
    cin >> a >> b;
    unsigned n = a.length() + 1;
    unsigned m = b.length() + 1;
    long **memo = new long *[n];

    for (unsigned i = 0; i < n; i++) {
        memo[i] = new long [m];
    }

    for (unsigned i = 1; i < n; i++)
        for (unsigned j = 1; j < m; j++)
            memo[i][j] = -1;
    memo[0][0] = 0;

    for (unsigned i = 1; i < n; i++)
        memo[i][0] = i;
    for (unsigned i = 1; i < m; i++)
        memo[0][i] = i;

    for (unsigned idx = 1; idx < m * n; idx ++)
        trace1 += (idx < m) ? '1' : (idx % m == 0) ? '2' : ' ';

    cout << reverse_trans(a, b, n - 1, m - 1, m, memo, trace1) << ' ' << track_trace(trace1, n, m) << '\n';
    cout << forward_trans(a, b, trace2) << ' ' << track_trace(trace2, n, m);

    for (unsigned i = 0; i < n; i++)
        delete [] memo[i];
    delete [] memo;
    return 0;
}
