#ifndef WTTT
#define WTTT

#include "BoardGame_Classes.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


template <typename T>
class WTTT_Board:public Board<T> {
public:
    WTTT_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};


class ui_wtt{
public:

void main();


};
template <typename T>
class WTTT_Player : public Player<T> {
    
public:
    WTTT_Player (string name, T symbol);
    void getmove(int& x, int& y);
};

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

template <typename T>
class WTTT_Random_Player : public RandomPlayer<T>{

public:
    WTTT_Random_Player (T symbol);
    void getmove(int& x, int& y) ;
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <string>
#include <map>

using namespace std;

map<string,bool> dicLines;
string winningWord;

template <typename T>
WTTT_Board<T>::WTTT_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;

    string line;
    fstream dic("dic.txt");
    while(getline(dic,line)){
        dicLines[line] = true;
    }
    dic.close();
}

template <typename T>
bool WTTT_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void WTTT_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n";
        for (int j = 0; j < this->columns; j++) {

            if(this->board[i][j] == 0){
                cout << "|  (" << i << "," << j << ")";
                cout << setw(0) << this->board[i][j] << "  ";
            }

            else {
                cout << "|" << setw(5) << this->board[i][j] << "    ";
            }

            if((j == 2 && i == 0) || (j == 2 && i == 1) || (j == 2 && i == 2)){
                cout << "|";
            }
        }
        cout << "\n-------------------------------";
    }
    cout << endl;
}

template <typename T>
bool WTTT_Board<T>::is_win() {
    for(int i = 0; i < this->rows; i++) {
        
        if(this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0) {
            std::string verticalLine = {this->board[0][i], this->board[1][i], this->board[2][i]};
            std::string reverseVerticalLine = {this->board[2][i], this->board[1][i], this->board[0][i]};
            if(dicLines.find(verticalLine) != dicLines.end()) {
                cout << "Word \"" << GREEN << verticalLine << RESET << "\" was made!\n";
                return true;
            }
            if(dicLines.find(reverseVerticalLine) != dicLines.end()){
                cout << "Word \"" << GREEN << reverseVerticalLine << RESET << "\" was made!\n";
                return true;
            }
        }

        
        if(this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) {
            std::string horizontalLine = {this->board[i][0], this->board[i][1], this->board[i][2]};
            std::string reverseHorizontalLine = {this->board[i][2], this->board[i][1], this->board[i][0]};
            if(dicLines.find(horizontalLine) != dicLines.end()) {
                cout << "Word \"" << GREEN << horizontalLine << RESET << "\" was made!\n";
                return true;
            }
            if(dicLines.find(reverseHorizontalLine) != dicLines.end()){
                cout << "Word \"" << GREEN << reverseHorizontalLine << RESET << "\" was made!\n";
                return true;
            }
        }
    }

    
    if(this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) {
        string diagonalLine1 = {this->board[0][0], this->board[1][1], this->board[2][2]};
        string reverseDiagonalLine1 = {this->board[2][2], this->board[1][1], this->board[0][0]};
        if(dicLines.find(diagonalLine1) != dicLines.end()) {
            cout << "Word \"" << GREEN << diagonalLine1 << RESET << "\" was made!\n";
            return true;
        }
        if(dicLines.find(reverseDiagonalLine1) != dicLines.end()){
            cout << "Word \"" << GREEN << reverseDiagonalLine1 << RESET << "\" was made!\n";
            return true;
        }
    }

    if(this->board[2][0] != 0 && this->board[1][1] != 0 && this->board[0][2] != 0) {
        string diagonalLine2 = {this->board[2][0], this->board[1][1], this->board[0][2]};
        string reverseDiagonalLine2 = {this->board[0][2], this->board[1][1], this->board[2][0]};
        if(dicLines.find(diagonalLine2) != dicLines.end()) {
            cout << "Word \"" << GREEN << diagonalLine2 << RESET << "\" was made!\n";
            return true;
        }
        if(dicLines.find(reverseDiagonalLine2) != dicLines.end()){
            cout << "Word \"" << GREEN << reverseDiagonalLine2 << RESET << "\" was made!\n";
            return true;
        }
    }

    return false;
}



template <typename T>
bool WTTT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}



template <typename T>
WTTT_Player<T>::WTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WTTT_Player<T>::getmove(int& x, int& y) {
    cout << '\n' << this->name << " Please enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;

    char Char;
    cout << '\n' << this->name << " Please enter the character you want to play: ";
    cin >> Char;

    this->symbol = Char;
}



template <typename T>
WTTT_Random_Player<T>::WTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void WTTT_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = alphabet[rand() % 26];
}







#endif
void ui_wtt::main(){
        char choice;
    
    Player<char>* players[2];
    WTTT_Board<char>* B = new WTTT_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to Word tic tac toe Game. :)\n";

    
    cout << "Enter Player 1 name: ";
    cin >> player1Name;


    while(true){

        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if(choice == '1'){
            players[0] = new WTTT_Player<char>(player1Name, 'X');
            break;
        }
        else if(choice == '2'){
            players[0] = new WTTT_Random_Player<char>('X');
            break;
        }

        cout << "Invalid choice for Player 1. Please enter a valid input.\n";
    }




    
    cout << "Enter Player 2 name: ";
    cin >> player2Name;



    while(true){

        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if(choice == '1'){
            players[1] = new WTTT_Player<char>(player2Name, 'O');
            break;
        }
        else if(choice == '2'){
            players[1] = new WTTT_Random_Player<char>('O');
            break;
        }
        cout << "Invalid choice for Player 2. Please enter a valid input.\n\n";

    }

    GameManager<char> WTTT_game(B, players);
    WTTT_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    


}

