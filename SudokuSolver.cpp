/*
Name - Eshaan Sodhi
Roll Number - 22075032

The following code is an implementation of the A* algorithm to solve a 9x9 sudoku puzzle.
The code takes the unsolved puzzle as input and returns the solved puzzle as output.
The code uses a priority queue to store the states and uses the heuristic function to calculate the heuristic value of the current state.
The heuristic function calculates the number of conflicts in the current state and returns the sum of conflicts.
The code then uses the priority queue to find the state with the minimum heuristic value and then adds all possible states to the priority queue.
The code then continues this process until the goal state is reached and returns the solved puzzle.
The code uses the following functions:
1. validMove - to check if a number can be placed at a given position
2. heuristic - to calculate the heuristic value of the current state
3. findEmpty - to find the empty cell in the puzzle
4. solve - to solve the puzzle using A* algorithm
The code also takes the input of the unsolved puzzle and prints the solved puzzle as output.

Sample input:
Input the unsolved puzzle :
Input 0 for empty space !
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1   
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9

another input:
Input the unsolved puzzle :
Input 0 for empty space !
0 2 0 0 0 0 8 0 0
0 0 0 0 6 0 0 7 5
0 0 0 0 0 0 0 9 0
0 1 0 0 0 0 0 0 7
0 0 6 0 0 0 0 5 0
0 0 0 2 0 0 4 0 0
0 0 0 8 0 0 0 0 3
0 0 0 0 1 0 0 0 0
9 0 0 0 0 0 0 0 0

harder input:
Input the unsolved puzzle :
Input 0 for empty space !
8 5 0 0 0 2 4 0 0
7 2 0 0 0 0 0 0 9
0 0 4 0 0 0 0 0 0
0 0 0 1 0 7 0 0 2
3 0 5 0 0 0 9 0 0
0 4 0 0 0 0 0 0 0
0 0 0 0 8 0 0 7 0
0 1 7 0 0 0 0 0 0
0 0 0 0 3 6 0 4 0

another input:
Input the unsolved puzzle :
Input 0 for empty space !
6 0 9 0 0 7 0 0 0
0 3 0 0 9 4 6 7 2
8 0 0 1 0 0 0 4 9
4 9 0 3 0 0 0 5 0
0 0 0 0 0 0 0 0 6
7 0 3 0 1 0 2 8 0
9 6 2 0 3 0 0 0 5
1 8 0 2 0 0 7 6 0
0 7 4 6 5 1 0 0 0

The reader may copy the above matrix and directly paste it in the terminal to input the unsolved puzzle.

If the un-commented heuristic function is not working, use the following heuristic function:
int heuristic() {
    // Heuristic function: simply counts the number of empty cells
    int count = 0;
    for (const auto& row : board) {
        count += count(row.begin(), row.end(), 0);
    }
    return count;
}
This heuristic function is also given in a comment in the code.

*/



#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <utility>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;



// Function to check if a number can be placed at a given position
bool validMove(int x, int y, vector <vector <int> > &v, int num){
    for(int i=0;i<9;i++){
        if(v[x][i]==num || v[i][y]==num){
            return false;
        }
    }
    int x1 = x/3;
    int y1 = y/3;
    for(int i=3*x1;i<3*x1+3;i++){
        for(int j=3*y1;j<3*y1+3;j++){
            if(v[i][j]==num){
                return false;
            }
        }
    }
    return true;
}

// Function to calculate the heuristic value of the current state
int heuristic(vector<vector<int>>& v) {
    int conflicts = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (v[i][j] == 0) { // Count conflicts only for empty cells
                int conflict_count = 0;
                for (int num = 1; num <= 9; num++) {
                    if (!validMove(i, j, v, num)) {
                        // If the number cannot be placed at the current cell, increment the conflict count
                        conflict_count++;
                    }
                }
                conflicts += conflict_count;
            }
        }
    }
    return conflicts;
}

/* Note - If the above heuristic function is not working, use the following heuristic function */
/*int heuristic() {
    // Heuristic function: simply counts the number of empty cells
    int count = 0;
    for (const auto& row : board) {
        count += count(row.begin(), row.end(), 0);
    }
    return count;
}*/

// Function to find the empty cell in the puzzle
pair <int, int> findEmpty(vector <vector <int> > &v){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(v[i][j]==0){
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Function to solve the puzzle using A* algorithm
vector <vector <int> > solve(vector <vector <int> > &v){
    // Using priority queue to store the states
    priority_queue <pair <int, vector <vector <int> > > > pq;
    // Push the initial state into the priority queue
    pq.push({-heuristic(v), v});
    while(!pq.empty()){
        // Get the state with the minimum heuristic value
        vector <vector <int> > cur = pq.top().second;
        pq.pop();
        // If the state is the goal state, return the state
        pair <int, int> p = findEmpty(cur);
        if(p.first==-1){
            return cur;
        }
        for(int i=1;i<=9;i++){
            //add all possible states to the priority queue
            if(validMove(p.first, p.second, cur, i)){
                cur[p.first][p.second] = i;
                pq.push({-heuristic(cur), cur});
                cur[p.first][p.second] = 0;
            }
        }
    }
    return v;
}

void printSudokuWithBoxes(vector<vector<int>>& sudoku) {
    // Iterate through each row
    for (int i = 0; i < 9; ++i) {
        // Print horizontal boundary line every third row
        if (i % 3 == 0 && i != 0) {
            cout << "---------------------" << endl;
        }
        // Iterate through each column
        for (int j = 0; j < 9; ++j) {
            // Print vertical boundary line every third column
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            // Print cell value or dash if cell is empty
            if (sudoku[i][j] != 0) {
                cout << sudoku[i][j] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

int main(){
    // use the function below to input the sudoku f choice (manual)
    cout<<"Input the unsolved puzzle : "<<endl;
    cout<<"Input 0 for empty space !"<<endl;
    vector <vector <int> > v(9);
    for(int i=0;i<9;i++){
        // cout<<"Enter row "<<i+1<<": ";
        for(int j=0;j<9;j++){
            int x;
            cin>>x;
            v[i].push_back(x);
        }
    }

    cout<<"Input is :"<<endl;
    printSudokuWithBoxes(v);
    clock_t start, end;
    start = clock();
    vector <vector <int> > ans = solve(v);
    end = clock();
    cout<<"The solved puzzle is :"<<endl;
    printSudokuWithBoxes(ans);
    cout<<"Time taken (in s) : "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;


    return 0;
}