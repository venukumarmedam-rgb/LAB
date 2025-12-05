    #include <bits/stdc++
    .h>
    using namespace std;
    int board[50][50];
    bool issafe(int row, int col, int n) {
        for (int i = 0; i < row; ++i)
        if (board[i][col]) return false;
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i,
            if (board[i][j]) return false;
            for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i,
            if (board[i][j]) return false;
        return true; --j)++j)
    }
    void nqueen(int n, int row, int &solutions) {
        if (row == n) {
    ++solutions;
        cout << "Solution " << solutions << ":\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
        cout << (board[i][j] ? 'Q' : '
        .
    ') << ' ';
    cout << '\n';
    }
    cout << '\n';
    return;
    }
    for (int col = 0; col < n; ++col) {
    if (issafe(row, col, n)) {
    board[row][col] = 1;
    nqueen(n, row + 1, solutions);
    board[row][col] = 0;
    }
    }
    }
    int main() {
    int n;
    cout << "enter the value of n: ";
    cin >> n;
    for (int i = 0; i < 50; ++i)
    for (int j = 0; j < 50; ++j)
    board[i][j] = 0;
    int solutions = 0;
    nqueen(n, 0, solutions);
    cout << "Total solutions: " << solutions << '\n';
    return 0;
    }
