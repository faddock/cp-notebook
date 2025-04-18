#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int rows, cols; cin >> rows >> cols;
    vector<vector<long long>> grid(rows, vector<long long>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }

    vector<pair<long long, pair<int,int>>> cells;
    cells.reserve(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells.emplace_back(grid[i][j], make_pair(i, j));
        }
    }
    sort(cells.begin(), cells.end());
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int total = rows * cols;

    for (int idx = 0; idx < total; idx++) {
        long long value = cells[idx].first;
        int x = cells[idx].second.first;
        int y = cells[idx].second.second;
        if (dp[x][y] == 0) dp[x][y] = 1;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] > value) {
                dp[nx][ny] = max(dp[nx][ny], dp[x][y] + 1);
            }
        }
    }
    int answer = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dp[i][j] > answer) answer = dp[i][j];
        }
    }
    cout << answer << endl;
    return 0;
}