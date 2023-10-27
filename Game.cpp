#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Game.h"


const int m = 7, n=7;
const int nr_bombs{4};
const char bomb{'@'};

void printField(char arr[m][n])
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void createPlayground(char mat[m][n])
{
    char X{'X'} ;
    

    std::vector<std::string> firstColumn = {" ","A","B","C","D","E","F"};
    std::vector<std::string> firstRow = {" ","1","2","3","4","5","6"};   

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0)
            {
                mat[0][j] = static_cast<int>(firstRow[j][0]);
            }
            else {
                if (j == 0){
                    mat[i][0] = static_cast<int>(firstColumn[i][0]);
                }
                else {
                    mat[i][j] = X;
                }
            }
        }
    }
    // printField(mat);
}

void copyArray(char source[m][n], char destination[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

// Function to generate a random integer in the range [min, max]
int getRandomInt(int min, int max) {
    std::random_device rd;  // Create a random device
    std::mt19937 gen(rd()); // Create a Mersenne Twister pseudo-random number generator
    std::uniform_int_distribution<int> distribution(min, max); // Create a uniform distribution
    return distribution(gen); // Generate and return a random integer
}

void placeBombs(char sol[m][n])
{
    for (int i = 0 ; i < nr_bombs; i++) {
        int random_m = getRandomInt(1, m-1);
        int random_n = getRandomInt(1, n-1);
        sol[random_m][random_n] = bomb;
        std::cout << "bomb placed in: " << std::endl;
        std::cout << random_m << std::endl;
        std::cout << random_n << std::endl;
        
    }
    printField(sol);
    // std::cout << random_m << std::endl;
    // std::cout << random_n << std::endl;
    
}

int checkNeighbors(char v)
{ // counter for field
    char f{}; // in ASCII code the numbers start from 48
    int nb{};
    char neighbors[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    for (char i : neighbors){
        if (v == '@'){
            continue;
        } else if (i == v){
            f = ++i ;
        }
    }

    nb = static_cast<int>(f) - 48; // in ASCII code the numbers start from 48
    if (nb < 0){
        nb =0;
    } else {
        nb = nb -1; // drop counter
    }
    return nb;
}



void placeNumbers(char sol[m][n])
{
    int nb = {};
    char neighbors[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            
            // look at the borders of each element
            for (int k : {-1, 0, 1 }){
                for (int l : {-1, 0, 1 }){
                    if (k==0 && l==0){ // middle point irrelevant
                        continue;
                    // upper and left boundary
                    } else if ((i == 1 && k == -1) || (j == 1 && l == -1)){
                        continue;
                    // lower and right boundary
                    } else if ((i == m && k == 1) || (j == n && l == 1)){
                        continue;
                    // find neighbors
                    } else {
                        if (sol[i+k][j+l] == bomb){
                            nb = checkNeighbors(sol[i][j]);
                            // check if there is another bomb
                            if (sol[i][j] != bomb){ 
                                sol[i][j] = neighbors[nb]; 
                            }
                            
                        }
                        
                    }
                    
                }    
                
            } 
        }
    }
    std::cout << ' ' << std::endl;
    printField(sol);
    // std::cout << random_m << std::endl;
    // std::cout << random_n << std::endl;
    
}

void game()
{
    std::cout << "select a field (A-F for rows, 1-6 for columns)" << std::endl;
    char mat[m][n];
    createPlayground(mat);
    std::cout << ' ' << std::endl;
    char sol[m][n]; // make a copy for the solution
    copyArray(mat, sol);

    placeBombs(sol);
    placeNumbers(sol);
    std::cout << "done ..." << std::endl;
}

// #TODO:   1. don't place bombs in the same place
//          3. increase playground