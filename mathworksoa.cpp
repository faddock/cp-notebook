#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minOperations(vector<int>& source, vector<int>& target) {
    int n = source.size();
    vector<int> required(n);
    for (int i = 0; i < n; ++i) {
        required[i] = target[i] - source[i];
        if (required[i] < 0) {
            return -1;
        }
    }
    int sum_min = 0;
    for (int j = 0; j < n - 1; ++j) {
        sum_min += max(required[j] - required[j + 1], 0);
    }
    if (sum_min > required[0]) {
        return -1;
    }
    return sum_min + required.back();
}

int main() {
    int n;
    cout << "Enter the size of the arrays: ";
    cin >> n;

    vector<int> source(n), target(n);

    cout << "Enter the elements of the source array: ";
    for (int i = 0; i < n; ++i) {
        cin >> source[i];
    }

    cout << "Enter the elements of the target array: ";
    for (int i = 0; i < n; ++i) {
        cin >> target[i];
    }

    int result = minOperations(source, target);

    if (result == -1) {
        cout << "It is impossible to transform the source array into the target array." << endl;
    } else {
        cout << "Minimum number of operations required: " << result << endl;
    }

    return 0;
}