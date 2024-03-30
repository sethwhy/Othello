#include "color.h"
#include "game.h"
#include "piece.h"
#include <queue> // Include queue header for using queue<string>

using namespace std;

class Othello : public main_savitch_14::game
{
public:
    // Default constructor
    Othello();

    // Member functions
    void display_status() const;
    bool is_legal(const string &move) const;
    void make_move(const string &move);

    // Additional functions
    void setStart();
    void restart();
    bool is_legal_move(int row, int col) const;
    bool is_valid_sequence(int row, int col, int dr, int dc) const;
    string get_move_string(int row, int col) const;

    // Pure virtual functions from the base class
    game *clone() const;
    void compute_moves(queue<string> &moves) const;
    int evaluate() const;
    bool is_game_over() const;

private:
    piece board[8][8]; // Define the board size as 8x8
};
