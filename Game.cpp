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


void createPlayground(char arr[m][n], char fillSymbol){
    std::vector<std::string> firstColumn = {" ","A","B","C","D","E","F"};
    std::vector<std::string> firstRow = {" ","1","2","3","4","5","6"};   

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0)
            {
                arr[0][j] = static_cast<int>(firstRow[j][0]);
            }
            else {
                if (j == 0){
                    arr[i][0] = static_cast<int>(firstColumn[i][0]);
                }
                else {
                    arr[i][j] = fillSymbol;
                }
            }
        }
    }
}


void copyArray(char source[m][n], char destination[m][n]){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            destination[i][j] = source[i][j];
        }
    }
}


// Function to generate a random integer in the range [min, max]
int getRandomInt(int min, int max){
    std::random_device rd;  // Create a random device
    std::mt19937 gen(rd()); // Create a Mersenne Twister pseudo-random number generator
    std::uniform_int_distribution<int> distribution(min, max); // Create a uniform distribution
    return distribution(gen); // Generate and return a random integer
}


void placeBombs(char arr[m][n]){
    int idx{0};
    while (idx < nr_bombs){
        int random_m = getRandomInt(1, m-1);
        int random_n = getRandomInt(1, n-1);
        if (arr[random_m][random_n] != bomb){
            arr[random_m][random_n] = bomb;
            idx++;
        }
    }
}


int checkNeighbors(char v){ 
    // counter for field
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


void placeNumbers(char sol[m][n]){
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
}


void gameState(char arr[m][n]){
    printField(arr);
}


void getInputs(char* inp1, char* inp2){
    std::string userInput;
    std::getline(std::cin, userInput);
    
    if (userInput.length() == 2) { //#TODO: check also if numbers and alphabet is in the right range
        *inp1 = (userInput)[0];
        *inp2 = (userInput)[1];
    } else {
        std::cout << "\n** ERROR ** Please enter only two characters ** ERROR **\n" << std::endl;
        *inp1 = '\0';
        *inp2 = '\0';
    }
}


void move(char arr1[m][n], char arr2[m][n]){  
    char input1, input2;
    std::cout << "please enter position in the form e.g. A1" << std::endl;
    getInputs(&input1, &input2);
    std::cout << "First character: " << input1 << std::endl;
    std::cout << "First character: " << input2 << std::endl;
}


void game()
{
    // std::cout << "select a field (A-F for rows, 1-6 for columns)" << std::endl;
    char playground[m][n];
    char solution[m][n];

    createPlayground(playground, 'X');
    createPlayground(solution, ' ');
    
    placeBombs(solution);
    placeNumbers(solution);

    while (true){
        gameState(playground);
        move(playground, solution);
    }

    // delete[] playground;
    std::cout << "done ..." << std::endl;
}

// #TODO: increase playground