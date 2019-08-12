#include <iostream>
#include "SOS.h"
#include <fstream>
using namespace std;

int main(){

    ifstream in("input.txt", ios::in);
    int _size;
    int counter;
    while(in>>_size){
        SOS obj(_size);
        counter = 0;
        obj.constructBoard();
        do{
            if(_size < 3) break;
            obj.run();
            obj.log();
            obj.switch_players();
            if(!obj.gameOver()){

                obj.randon_placement();
                obj.log();
                obj.switch_players();
            }

        }while(!obj.gameOver());
        obj.display();
    }

    return 0;
}
