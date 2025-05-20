#ifndef pyramidttt
#define pyramidttt

#include "BoardGame_Classes.h"
#include<vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"



template<typename T>
class PTTT_Board:public Board<T> {
public:
    PTTT_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};


class ui_ptt{
public:

void main();


};
template <typename T>
class PTTT_Player : public Player<T> {
public:
    PTTT_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class PTTT_Random_Player : public RandomPlayer<T>{
protected:
    vector<pair<int,int>> index = {{0,2},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{2,4}};
public:
    PTTT_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
PTTT_Board<T>::PTTT_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool PTTT_Board<T>::update_board(int x, int y, T mark){

            if(x==0 && y == 2 && this->board[x][y] == 0){
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
            if(x==2 && y < 5 && y>=0 && this->board[x][y] == 0){
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
            if(x == 1 && y > 0 && y < 4 && this->board[x][y] == 0){
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
void PTTT_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n ";
        for (int j = 0; j < this->columns; j++) {

            if((j == 0 && i == 1) || (j == 0 && i == 0) || (j == 1 && i == 0) ||
               (j == 3 && i == 0) || (j == 4 && i == 1) || (j == 4 && i == 0) ){

                cout << "          ";
                continue;
            }

            if(this->board[i][j] == 0){
                cout << "| (" << i << "," << j << ")";
                cout << setw(1) << this->board[i][j] << "   ";
            }

            else if(this->board[i][j] == 'X') {
                cout << "|" << "    " << CYAN << this->board[i][j] << RESET << "    ";
            }

            else if(this->board[i][j] == 'O') {
                cout << "|" << "    " << RED << this->board[i][j] << RESET << "    ";
            }

            if((j == 2 && i == 0) || (j == 3 && i == 1) || (j == 4 && i == 2)){
                cout << "|";
            }
        }
    }
    cout << endl;
}

template<typename T>
bool PTTT_Board<T>::is_win() {

    if((this->board[2][0] == this->board[2][1] && this->board[2][0] == this->board[2][2] && this->board[2][0] != 0) || (this->board[2][1] == this->board[2][2] && this->board[2][1] == this->board[2][3] && this->board[2][1] != 0) || (this->board[2][2] == this->board[2][3] && this->board[2][2] == this->board[2][4] && this->board[2][2] != 0) ||
       (this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3] && this->board[1][1] != 0) || (this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2][2] && this->board[0][2] != 0)){
        return true;
    }

    if((this->board[2][0] == this->board[1][1] && this->board[2][0] == this->board[0][2] && this->board[2][0] != 0) ||
       (this->board[2][4] == this->board[1][3] && this->board[2][4] == this->board[0][2] && this->board[2][4] != 0)){
        return true;
    }

    return false;
}

template <typename T>
bool PTTT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
PTTT_Player<T>::PTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PTTT_Player<T>::getmove(int& x, int& y) {
    cout << '\n' << this->name << " Please enter your move x and y separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
PTTT_Random_Player<T>::PTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
}

template <typename T>
void PTTT_Random_Player<T>::getmove(int& x, int& y) {

    while (true) {
        int i = rand() % index.size();
        x = index[i].first;
        y = index[i].second;


        if (!((x == 0 && y == 1) || (x == 0 && y == 0) || (x == 1 && y == 0) ||
              (x == 3 && y == 0) || (x == 4 && y == 1) || (x == 4 && y == 0))) {
            index.erase(index.begin() + i);
            break;
        }
    }
}

#endif

void ui_ptt::main(){

        
    char choice;
    
    Player<char>* players[2];
    PTTT_Board<char>* B = new PTTT_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to Pyramid tic tac toe Game. :)\n";

    
    cout << "Enter Player 1 name: ";
    cin >> player1Name;


    while(true){

        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if(choice == '1'){
            players[0] = new PTTT_Player<char>(player1Name, 'X');
            break;
        }
        else if(choice == '2'){
            players[0] = new PTTT_Random_Player<char>('X');
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
            players[1] = new PTTT_Player<char>(player2Name, 'O');
            break;
        }
        else if(choice == '2'){
            players[1] = new PTTT_Random_Player<char>('O');
            break;
        }
        cout << "Invalid choice for Player 2. Please enter a valid input.\n\n";

    }

    // Create the game manager and run the game
    GameManager<char> PTTT_game(B, players);
    PTTT_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }


    
}






