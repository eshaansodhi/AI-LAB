//Name - Eshaan Sodhi
//Roll - 22075032
//Branch - CSE
//Course - B.Tech
//Year - 2nd
//The following code is a solution to the N-Queens problem using the Hill Climbing Algorithm.
//The only input is the size of the board
//It returns even a problem with n=100 with minimum 30 seconds during test runs
//Small problems take less than 1 second
//However, the time taken is a bit random and depends on the initial board generated
// Input -> n
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <bitset>
#define Eshaan Sodhi
#include <numeric>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <set>
#include <cassert>
#include <cstring>
#include <complex>
#include <climits>
#include <functional>
#include <random>
#include <valarray>
#include <iterator>
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;

int n=100000;
unsigned long long cnt =0;
set <vector<vector<int>>> stateUsed;

vector<vector<int>> makeAMove(vector<vector<int>> board,pair<int,int> old,pair<int,int>neww);
vector<vector<int>> generateBoard(int n);
int numAttacks(vector<vector<int>> board);
vector<vector<int>> bestMove(vector<vector<int>> board);
void print(vector<vector<int>> board);


void amountQueens(vector<vector<int>> board){//prints the amount of queens in the board
    int queens = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==1){
                queens++;
            }
        }
    }
    printf("QUEENS -> %d\n",queens);
}
void print(vector<vector<int>> board){//prints the board
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

// makes a move on the board while checking if the move is valid
vector<vector<int>> makeAMove(vector<vector<int>> board,pair<int,int> old,pair<int,int>neww){
    vector<vector<int>> newboard = board;
    if(newboard[old.first][old.second]==0){
        return newboard;
    }else if(newboard[neww.first][neww.second]==1){
        return newboard;
    }
    newboard[old.first][old.second]=0;
    newboard[neww.first][neww.second]=1;
    return newboard;
}

// generates a random board such that each row and column has exactly one queen
// This function is used to generate the initial board
// It also checks if the board has already been generated before using a set
vector<vector<int>> generateBoard(int n){
    vector<vector<int>> board(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            board[i][j]=0;
        }
    }
    srand((unsigned) time(NULL));
    bool hash[n];
    for(int i=0;i<n;i++){
        hash[i]=false;
    }
    for(int i=0;i<n;i++){
        int x = rand()%n;
        while(hash[x]==true){
            x = rand()%n;
        }
        hash[x]=true;
        board[i][x]=1;
    }
    if(stateUsed.find(board)!=stateUsed.end()){
        board = generateBoard(n);
    }
    return board;
}

// Gives the number of attacks in the board , i.e. the number of pairs of queens that are attacking each other
int numAttacks(vector<vector<int>> board){
    int attacks = 0;
    int row[n];
    int col[n];
    int diag1[2*n-1];
    int diag2[2*n-1];
    for(int i = 0; i < n; i++){
        row[i] = 0;
        col[i] = 0;
    }
    for(int i = 0; i < 2*n-1; i++){
        diag1[i] = 0;
        diag2[i] = 0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==1){
                row[i]++;
                col[j]++;
                diag1[i+j]++;
                diag2[i-j+n-1]++;
            }
        }
    }
    for(int i=0;i<n;i++){
        attacks += max(0,row[i]-1);
        attacks += max(0,col[i]-1);
    }
    for(int i=0;i<2*n-1;i++){
        attacks += max(0,diag1[i]-1);
        attacks += max(0,diag2[i]-1);
    }
    return attacks;
}

// generates a random move on the board
// I tried using this function to get out of local minima but it didn't work well
vector <vector<int>> randomMove(vector<vector<int>> board){
    vector<vector<int>> newboard = board;
    int i = rand()%n;
    int j = rand()%n;
    int k = rand()%n;
    int l = rand()%n;
    while(newboard[i][j]==0){
        i = rand()%n;
        j = rand()%n;
    }
    while(newboard[k][l]==1){
        k = rand()%n;
        l = rand()%n;
    }
    newboard[i][j]=0;
    newboard[k][l]=1;
    return newboard;
}

// shifts the board to the left by a random amount
// Also tried this function to get out of local minima but it didn't work well
vector<vector<int>> shiftLeftBoard(vector<vector<int>> board){
    vector<vector<int>> newboard = board;
    srand((unsigned) time(NULL));
    int shift = rand()%n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j+shift<n){
                newboard[i][j]=board[i][j+shift];
            }else{
                newboard[i][j]=board[i][j+shift-n];
            }
        }
    }
    return newboard;
}

// finds the best move on the board and returns the board after making that move
// if there are multiple moves with the same number of attacks then it chooses one of them randomly
// This is the main function that is used to solve the problem
vector<vector<int>> bestMove(vector<vector<int>> board){
    vector<pair<int,vector<vector<int>>>> bestBoards;
    vector<vector<int>> best=board;
    int bestAttacks = numAttacks(board);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==1){
                for(int k=0;k<n;k++){
                    if(k!=j){
                        // Hill Climbing Implementation
                        vector<vector<int>> newboard = makeAMove(board,{i,j},{i,k});
                        int newAttacks = numAttacks(newboard);
                        if(newAttacks<bestAttacks){
                            bestAttacks = newAttacks;
                            best = newboard;
                        }else if(newAttacks==bestAttacks){
                            bestBoards.push_back({newAttacks,newboard});
                        }
                    }
                }
            }
        }
    }
    srand((unsigned) time(NULL));
    sort(bestBoards.begin(),bestBoards.end());
    // Encountered a local minima
    if(numAttacks(best)==numAttacks(board)){
        // best = randomMove(board);
        int size = 0;
        for(int i=0;i<bestBoards.size();i++){
            if(bestBoards[i].first==bestAttacks){
                size++;
            }
        }
        int x = rand()%size;
        best = bestBoards[x].second;
        // Keep track of the number of local minima encountered
        cnt++;
        // best = shiftLeftBoard(board);
        // cout<<"NO BETTER MOVE FOUND"<<endl;
    }
    return best;

}

int main(){
    cout<<"Enter the size of the board (any size)"<<endl;
    cin>>n;
    clock_t tStart = clock();
    if(n==2||n==3){
        cout<<"NO SOLUTION"<<endl;
        return 0;
    }
    vector<vector<int>> board = generateBoard(n);
    cout<<"INITIAL BOARD"<<endl;
    print(board);
    while(numAttacks(board)>0){
        board = bestMove(board);
    }
    cout<<"ANSWER FOUND!!"<<endl;
    cout<<"FINAL BOARD"<<endl;
    print(board);
    cout<<"LOCAL MINIMA COUNT -> "<<cnt<<endl;
    cout<<"ATTACKS -> "<<numAttacks(board)<<endl;
    cout<<"AMOUNT OF ";
    amountQueens(board);
    cout<<"Time taken: "<<setprecision(10)<<((double)(clock()-tStart)/CLOCKS_PER_SEC)<<" s"<<endl;
    // cout<<numAttacks(board);
}