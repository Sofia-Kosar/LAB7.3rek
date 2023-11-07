#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void Create(int** a, const int size, const int Low, const int High, int row, int col) {
    if (row == size) return;
    if (col == size) {
        Create(a, size, Low, High, row + 1, 0);
        return;
    }

    a[row][col] = Low + rand() % (High - Low + 1);
    Create(a, size, Low, High, row, col + 1);
}

void Input(int** a, const int size, int row, int col) {
    if (row == size) return;
    if (col == size) {
        Input(a, size, row + 1, 0);
        return;
    }

    cout << "a[" << row << "][" << col << "] = ";
    cin >> a[row][col];
    Input(a, size, row, col + 1);
    if (col == 0) cout << endl;
}

void Print(int** a, const int Count, int row, int col) {
    if (row == Count) return;
    if (col == Count) {
        cout << endl;
        Print(a, Count, row + 1, 0);
        return;
    }

    cout << setw(4) << a[row][col];
    Print(a, Count, row, col + 1);
}

bool IsLocalMin(int** a, const int Count, int row, int col, int nbRow, int nbCol, int localMin) {
    if (nbRow > row + 1) return localMin == a[row][col];

    if (nbCol <= col + 1) {
        if (nbRow >= 0 && nbRow < Count && nbCol >= 0 && nbCol < Count) {
            if (a[nbRow][nbCol] < localMin) localMin = a[nbRow][nbCol];
        }
        return IsLocalMin(a, Count, row, col, nbRow, nbCol + 1, localMin);
    }

    return IsLocalMin(a, Count, row, col, nbRow + 1, 0, localMin);
}

void GetElementsCountRecursive(int** a, const int Count, int row, int col, int& result) {
    if (row == Count) return;
    if (col == Count) {
        GetElementsCountRecursive(a, Count, row + 1, 0, result);
        return;
    }

    int localMin = a[row][col];
    if (IsLocalMin(a, Count, row, col, row - 1, col - 1, localMin)) {
        result++;
    }

    GetElementsCountRecursive(a, Count, row, col + 1, result);
}

int GetElementsCount(int** a, const int Count, int row, int col) {
    int result = 0;
    GetElementsCountRecursive(a, Count, row, col, result);
    return result;
}

int GetAbsSumRecursive(int** a, const int Count, int row, int col, int& result) {
    if (row == Count) return 0;
    if (col == Count) return GetAbsSumRecursive(a, Count, row + 1, 0, result);

    if (col > row) {
        result += abs(a[row][col]);
    }

    return GetAbsSumRecursive(a, Count, row, col + 1, result);
}

int GetAbsSum(int** a, const int Count) {
    int result = 0;
    GetAbsSumRecursive(a, Count, 0, 0, result);
    return result;
}

int main() {
    int Low = 1;
    int High = 15;

    int size;
    cout << "Enter the size: ";
    cin >> size;

    int** a = new int* [size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    //Create(a, size, Low, High, 0, 0);
    Input(a, size, 0, 0);
    Print(a, size, 0, 0);

    int elementsCount = GetElementsCount(a, size, 0, 0);
    cout << "number of local minimums = " << elementsCount << endl;

    int absSum = GetAbsSum(a, size);
    cout << "sum of absolute values above the main diagonal = " << absSum << endl;

    for (int row = 0; row < size; row++)
        delete[] a[row];
    delete[] a;

    return 0;
}
