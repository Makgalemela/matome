#ifndef SOS_H
#define SOS_H
#include <string>
#include <fstream>

typedef struct{
    int x;
    int y;
} point;


class SOS{
    public:
        SOS(int size = 0);
        /// initialize the board with the empty cells
        void constructBoard();
        /// traverse the board forward and backwards
        void foward_backward();
        /// traverse the board up and down
        void up_down();
        /// traverse the board diagonally upper left and bottom right, back-forth
        void topleft_bottonright();
        /// traverse the board diagonally upper right and bottom left, back-forth
        void topright_bottomleft();
        /// place S or O on the board
        void place_piece();
        /// run the game
        void run();
        ///clear the marks
        bool check_higher_possibility();
        /// random selection play
        void randon_placement();
        ///switch players / switches
        void switch_players();
        ///check if the letter can be used in the current turn
        void validletter();
        /// place the letter on the board
        void place_letter();

        void display();

        /// write current points

        bool gameOver();

        /// log the moves

        void log();

        /// play again of the play has collected a point
        bool playAgain();
        ~SOS();
    private:
        int _size;
        char **Board;
        char s_piece;
        char o_piece;
        char curr_piece;
        char empty_cell;
        int player1_points;
        int player2_points;
        int temp_points;
        int randon_points[1000][2];

        std::ofstream out;
        int tr;
        int tc;
        int row;
        int col;
        int s_possible;
        int o_possible;
        int s_count;
        int o_count;
        std::string player;
        std::string curr_player;
        void moves();
};

#endif // SOS_H
