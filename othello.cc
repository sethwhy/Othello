// File: othello.cc

#include "othello.h"
#include "color.h"
#include "game.h"
#include "piece.h"
#include <iostream>
#include <cctype>

using namespace main_savitch_14;
using namespace std;

Othello::Othello()
{
    restart(); // Initialize the game when an object is created
}

// CHANGE COLORS HERE
void Othello::display_status() const
{
    cout << RED << "   A   B   C   D   E   F   G   H   " << endl;
    for (int i = 0, j = 1; i < 8; i++, j++)
    {
        cout << WHITE << "  ---------------------------------" << endl;
        cout << RED << j;
        for (int m = 0; m < 8; m++)
        {
            cout << WHITE << " | " << YELLOW;
            cout << board[i][m];
        }
        cout << WHITE << " | " << RED << endl;
    }
    cout << WHITE << "  ---------------------------------" << RESET << endl;
}

void Othello::make_move(const string &move)
{
    if (!is_legal(move))
    {
        cout << "Illegal move!" << endl;
        return;
    }

    int row = move[1] - '1';
    int col = toupper(move[0]) - 'A';
    char piece_color = (next_mover() == HUMAN) ? 'b' : 'w';

    board[row][col].set_piece_color(piece_color);

    // Directions for checking adjacent cells
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int d = 0; d < 8; ++d)
    {
        int r = row + dr[d];
        int c = col + dc[d];
        bool valid_sequence = false;
        vector<pair<int, int>> pieces_to_flip; // Store pieces to flip

        while (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c].getColor() != piece_color)
        {
            if (board[r][c].getColor() != 'e' && board[r][c].getColor() != piece_color)
            {
                valid_sequence = true;
                pieces_to_flip.push_back({r, c}); // Add piece to flip
            }
            r += dr[d];
            c += dc[d];
        }

        if (valid_sequence)
        {
            // Check if the sequence ends with a piece of the current player's color
            if (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c].getColor() == piece_color)
            {
                // Flip pieces
                for (const auto &pos : pieces_to_flip)
                {
                    board[pos.first][pos.second].flip();
                }
            }
        }
    }

    game::make_move(move);
}

bool Othello::is_legal(const string &move) const
{
    // Convert the move coordinates to row and column indices
    int row = move[1] - '1';
    int col = toupper(move[0]) - 'A';

    // Check if the move is outside the board bounds or on an occupied space
    if (row < 0 || row >= 8 || col < 0 || col >= 8 || board[row][col].is_Black() || board[row][col].is_White())
    {
        return false;
    }

    // Directions for checking adjacent cells
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    char player_color = (next_mover() == HUMAN) ? 'b' : 'w';
    char opponent_color = (player_color == 'b') ? 'w' : 'b';

    // Check each direction for a valid sequence
    for (int d = 0; d < 8; ++d)
    {
        int r = row + dr[d];
        int c = col + dc[d];
        bool valid_sequence = false;

        while (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c].getColor() == opponent_color)
        {
            r += dr[d];
            c += dc[d];
            if (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c].getColor() == player_color)
            {
                valid_sequence = true;
                break;
            }
        }

        if (valid_sequence)
        {
            return true;
        }
    }

    return false;
}

void Othello::setStart()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board[i][j].set_piece_color('e');
        }
    }
    board[3][3].set_piece_color('w');
    board[4][4].set_piece_color('w');
    board[3][4].set_piece_color('b');
    board[4][3].set_piece_color('b');
}

void Othello::restart()
{
    setStart();
}

game *Othello::clone() const
{
    return new Othello(*this); // Implement cloning logic
}

void Othello::compute_moves(queue<string> &moves) const
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            string move = get_move_string(row, col);
            if (is_legal(move))
            {
                moves.push(move);
            }
        }
    }
}

// bool Othello::is_legal_move(int row, int col) const
// {
//     if (board[row][col].getColor() != 'e')
//     {
//         return false;
//     }
//     for (int dr = -1; dr <= 1; ++dr)
//     {
//         for (int dc = -1; dc <= 1; ++dc)
//         {
//             if (dr == 0 && dc == 0)
//             {
//                 continue;
//             }
//             if (is_valid_sequence(row, col, dr, dc))
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

bool Othello::is_valid_sequence(int row, int col, int dr, int dc) const
{
    char opponent_color = (next_mover() == HUMAN) ? 'b' : 'w';
    int r = row + dr;
    int c = col + dc;
    if (r < 0 || r >= 8 || c < 0 || c >= 8 || board[r][c].getColor() != opponent_color)
    {
        return false;
    }
    while (r >= 0 && r < 8 && c >= 0 && c < 8)
    {
        char cell_color = board[r][c].getColor();
        if (cell_color == 'e')
        {
            return false;
        }
        if (cell_color == (next_mover() == HUMAN ? 'w' : 'b'))
        {
            return true;
        }
        r += dr;
        c += dc;
    }
    return false;
}

string Othello::get_move_string(int row, int col) const
{
    char col_char = static_cast<char>('A' + col);
    char row_char = static_cast<char>('1' + row);
    string move = "";
    move += col_char;
    move += row_char;
    return move;
}

int Othello::evaluate() const
{
    int human_score = 0;
    int computer_score = 0;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            char cell_color = board[row][col].getColor();
            if (cell_color == 'b')
            {
                ++human_score;
            }
            else if (cell_color == 'w')
            {
                ++computer_score;
            }
        }
    }
    return human_score - computer_score;
}

bool Othello::is_game_over() const
{
    queue<string> moves;
    compute_moves(moves);
    if (moves.empty())
    {
        return true;
    }
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col].getColor() == 'e')
            {
                return false;
            }
        }
    }
    return true;
}
