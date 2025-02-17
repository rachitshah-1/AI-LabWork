#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> findSteppingNumbers(int n, int m) {

    // To store the stepping number 
    vector<int> result;

    // For traversal using BFS
    queue<int> q;

    // Queue dealing for 0-9
    for (int i = 0; i <= 9; ++i) {
        if (n <= i && i <= m) {
            // Single digit numbers to be included in the result
            result.push_back(i);
        }
        q.push(i);
    }

    //BFS traversal 
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        //Extracting the last digit
        int lastDigit = curr % 10;

        //Next possible stepping numbers
        int next1 = curr * 10 + lastDigit + 1;
        int next2 = curr * 10 + lastDigit - 1;

        //Checking new generated numbers and adding to result
        if (0 <= lastDigit + 1 && lastDigit + 1 <= 9 && n <= next1 && next1 <= m) {
            result.push_back(next1);
            q.push(next1);
        }
        if (0 <= lastDigit - 1 && lastDigit - 1 <= 9 && n <= next2 && next2 <= m) {
            result.push_back(next2);
            q.push(next2);
        }
    }

    return result;
}

int main() {
    // User input for the range
    int n, m;
    cout << "Enter n and m : \n";
    cin >> n >> m;
    
    //Finding the stepping numbers
    vector<int> steppingNumbers = findSteppingNumbers(n, m);

    //Printing the result
    cout << "Stepping numbers in range [" << n << ", " << m << "]: ";
    for (int num : steppingNumbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}