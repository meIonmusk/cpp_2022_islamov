#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

struct Activity{
    unsigned index;
    unsigned time;
    unsigned value;
};

bool activity_productivity_compare(Activity const &lha, Activity const &rha){
    return lha.value * rha.time > rha.value * lha.time;
}

bool activity_index_compare(Activity const &lha, Activity const &rha){
    return lha.index < rha.index;
}

int main() {
    unsigned n = 0;
    unsigned limit = 0;
    double effect = 0;

    cin >> n;
    auto arr_activity = new Activity [n];

    for (unsigned idx = 0; idx < n; idx++) {
        cin >> arr_activity[idx].time >> arr_activity[idx].value;
        arr_activity[idx].index = idx;
    }

    std::sort(arr_activity, arr_activity + n, activity_productivity_compare);
    cin >> limit;

    for (unsigned idx = 0; idx < n; idx++){
        unsigned time = arr_activity[idx].time;
        if (time > limit)
            arr_activity[idx].time = limit;
        effect += static_cast<double>(arr_activity[idx].value) * arr_activity[idx].time / time;
        limit -= arr_activity[idx].time;
    }

    std::sort(arr_activity, arr_activity + n, activity_index_compare);

    cout << '{';
    for (unsigned i = 0; i < n; i++)
        cout << arr_activity[i].time << ' ';
    cout << "} " << effect;

    delete [] arr_activity;

    return 0;
}
