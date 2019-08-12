#include "SOS.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
SOS::SOS(int size):
    _size{size}, s_piece{'S'},
    o_piece{'O'}, curr_piece{'O'}
    ,empty_cell{' '}, player1_points{0},
    player2_points{0}, s_possible{0},
    o_possible{0}, temp_points{0},
    o_count{0}, s_count{0}, curr_player{"Player1: "} ,
    player{"Player1: "}{

    ///initialize the size of the board dynamically
    Board = new char*[_size];
    for(int it = 0 ; it < _size ; it++)
        Board[it] = new char[_size];
    out.open("output.txt", ios::app);
}

///built initial board, and initialize the board with empty cells
void SOS::constructBoard(){
    if(_size < 3) return;
    srand(time(0));
    out<<"size = "<<_size<<endl;
    for(int it =0 ; it < _size ; it++)
        for(int yt = 0 ; yt < _size ; yt++)
            Board[it][yt] = empty_cell;
}
/// traverse the board left and right back and forth
void SOS::foward_backward(){
    if(tc+2< _size && Board[tr][tc+1]== o_piece &&Board[tr][tc+2]== s_piece ){
        s_possible++;
    }
    if(tc-2>0 && Board[tr][tc-1]== o_piece &&Board[tr][tc-2]== s_piece){
        s_possible++;
    }
    if(tc+1< _size &&tc-1>0&& Board[tr][tc+1]== s_piece &&Board[tr][tc-1]==s_piece){
        o_possible++;
    }
    return;
}

/// traverse the board up and down back and forth
void SOS::up_down(){
    if(tr+2< _size && Board[tr+1][tc]== o_piece &&Board[tr+2][tc]== s_piece ){
        s_possible++;
    }
    if(tr-2>0 && Board[tr-1][tc]== o_piece &&Board[tr-2][tc]== s_piece){
        s_possible++;
    }
    if(tr+1< _size &&tr-1>0&& Board[tr+1][tc]== s_piece &&Board[tr-1][tc]==s_piece){
        o_possible++;
    }
    return;
}

/// traverse the board top left and bottom right back and forth
void SOS::topleft_bottonright(){
    if(tr+2< _size && tc+2 < _size && Board[tr+1][tc+1]== o_piece &&Board[tr+2][tc+2]== s_piece ){
        s_possible++;
    }
    if(tr-2>0 && tc-2>0 && Board[tr-1][tc-1]== o_piece &&Board[tr-2][tc-2]== s_piece){
        s_possible++;
    }
    if(tr+1< _size && tr-1> 0&&tc+1<_size&&tr-1>0&& Board[tr+1][tc+1]== s_piece &&Board[tr-1][tc-1]==s_piece){
        o_possible++;
    }
    return;
}

/// traverse the board top right and bottom left back and forth
void SOS::topright_bottomleft(){
    if(tr+2< _size && tc-2>0&& Board[tr+1][tc-1]== o_piece &&Board[tr+2][tc-2]== s_piece ){
        s_possible++;
    }
    if(tr-2>0 && tc+2< _size && Board[tr-1][tc+1]== o_piece &&Board[tr-2][tc+2]== s_piece){
        s_possible++;
    }
    if(tr+1< _size&& tr-1> 0&&tc+1<_size&&tr-1>0&& Board[tr-1][tc+1]== s_piece &&Board[tr-1][tc+1]==s_piece){
        o_possible++;
    }
    return;
}
///Mark the board with either S or O
void SOS::place_piece(){

    if(s_possible > o_possible){
        temp_points = s_possible;
        curr_piece = s_piece;
    }
    else if(s_possible < o_possible){
        temp_points = o_possible;
        curr_piece = o_piece;
    }
    else{
        temp_points = s_possible=o_possible;
    }
    return;
}


void SOS::moves(){
   player += 'c' +to_string(row) + 'r'+to_string(col) + ' ';
   return;
}
SOS::~SOS(){
    delete Board;
}

///run the game by calling multiple  function

void SOS::run(){
    temp_points = 0;
    curr_player = "Player1: ";
    for(int it = 0 ; it<_size ; it++){
        for(int yt =0; yt<_size ; yt++){
            tr =it;
            tc =yt;
            o_possible = s_possible = 0;
            if(Board[it][yt] == empty_cell){
            if(check_higher_possibility()){
                row = it;
                col = yt;
            }

            foward_backward();
            up_down();
            topleft_bottonright();
            topright_bottomleft();
            place_piece();
            }
        }
    }
    player2_points += temp_points;
    validletter();
    place_letter();
    if(temp_points > 0){
        run();
    }
    ///out<<player<<' '<<curr_piece<<endl;
    ///player = "Player2: ";
    return;
}

///clear temporary marks

bool SOS::check_higher_possibility(){

    if(temp_points < o_possible || temp_points < s_possible)
        return true;
    else if(temp_points == o_possible || temp_points == s_possible)
        return true;
    return false;
}


///display function

void SOS::display(){
    if(_size < 3) return;
     out<<"Player1 = "<<player1_points<<endl;
     out<<"Player2 = "<<player2_points<<endl;
    if(player1_points >player2_points){
        out<<"win = "<< "Player1";
    }
    else if(player1_points < player2_points){
        out<<"win = "<< "Player2";
    }
    else{
        out<<"win = "<< "Draw";
    }
    out<<endl<<endl;
    return;
}

void SOS::randon_placement(){
     int index =0;
     temp_points =0;
     curr_player = "Player2: ";
     index = rand()%100;
     if(index%2==0){
        curr_piece = o_piece;
     }
     else{
         curr_piece = s_piece;
     }
     o_possible = s_possible =0;
     index = 0;
     for(int it = 0 ; it<_size ; it++){
        for(int yt =0; yt <_size ; yt++){
            if(Board[it][yt] == empty_cell){
                randon_points[index][0] = it;
                randon_points[index][1] = yt;
                index++;
            }
        }
    }

    if(index !=0){
        index = rand()%index;
        tr = row = randon_points[index][0];
        tc = col = randon_points[index][1];
        foward_backward();
        up_down();
        topleft_bottonright();
        topright_bottomleft();
        place_piece();
    }
    player1_points += temp_points;
    validletter();
    place_letter();
    if(temp_points > 0){
        randon_placement();
    }
    ///player = "Player1: ";
    return;
 }
/// check if the letter has been previously place twice

 void SOS::validletter(){

    if(curr_piece == o_piece && o_count < 2){
        o_count++;
        s_count = 0;
    }
    else if(curr_piece == o_piece && o_count == 2){
        o_count = 0;
        s_count++;
        curr_piece = s_piece;
    }
    else if(curr_piece == s_piece && s_count < 2){
        s_count++;
        o_count = 0;
    }
    else if(curr_piece == s_piece && s_count == 2){
        s_count = 0;
        o_count++;
        curr_piece = o_piece;
    }
    return;
 }

 ///place letter on the board
void SOS::place_letter(){
        Board[row][col] = curr_piece;
        moves();
        return;
    }
bool SOS::gameOver(){
    for(int it = 0 ; it< _size ; it++){
        for(int yt = 0 ; yt < _size ; yt++){
            if(Board[it][yt] == empty_cell)
                return false;
        }
    }
    return true;
}

void SOS::switch_players(){
    if(curr_player == "Player1: "){
        player ="Player2: ";
    }
    else {
        player ="Player1: ";
    }
    return;
}

void SOS::log(){
    out<<player<< ' '<<curr_piece<<endl;
    return;
}

bool SOS::playAgain(){

    if(temp_points > 1)
        return true;
    return false;
}
