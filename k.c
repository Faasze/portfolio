#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "k.h"
// pridava skore pre kazde pismeno ine 
int add_score(char letter) {
    switch(letter) {
        case 'A':
            return 2;
        case 'B':
            return 4;
        case 'C':
            return 8;
        case 'D':
            return 16;
        case 'E':
            return 32;
        case 'F':
            return 64;
        case 'G':
            return 128;
        case 'H':
            return 256;
        case 'I':
            return 512;
        case 'J':
            return 1024;
        case 'K':
            return 2048;
        default:
            return 0; // Nezname char 
    }
}
bool is_move_possible(const struct game game){
    for(size_t y=0 ; y<SIZE ; y++){
        for(size_t x=0 ; x<SIZE ; x++){
            // Kontrola pre prazdne pole 
            if(game.board[y][x]==' '){
                return true;
            }    
            // Kontrola pre rovnake v riadku po sebe 
            if(x < SIZE - 1 && game.board[y][x] == game.board[y][x+1]){
                return true;
            }
            // Kontrola v stlpci
            if(y < SIZE - 1 && game.board[y][x] == game.board[y+1][x]){
                return true;
            }
        }
    }
    return false;
}
bool is_game_won(const struct game game){
    for(int i =0 ; i < SIZE ; i++){
        for(int j =0 ; j < SIZE ; j++){
            if(game.board[i][j]=='K'){                   // Kontrola K
                return true;
            }
        }
    }
    return false;
}
void add_random_tile(struct game *game){
    int row, col;
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');
    game->board[row][col] = (rand() % 2 == 0) ? 'A' : 'B';
}

    void shift_tiles_right(struct game* game, size_t y) {
        for (size_t x = SIZE - 2; x != -1; x--) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            char current_tile = game->board[y][x];
            for (size_t i = x + 1; i < SIZE; i++) {
                if (game->board[y][i] == ' ') {
                    game->board[y][i] = current_tile;
                    game->board[y][i - 1] = ' ';
                }
            }
        }
    }

    void merge_tiles_right(struct game* game, size_t y) {
        for (size_t x = SIZE - 2; x != -1; x--) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            if (game->board[y][x] == game->board[y][x + 1]) {
                game->board[y][x + 1]++;
                game->score += add_score(game->board[y][x + 1]);
                game->board[y][x] = ' ';
            }
        }
    }

    void shift_tiles_left(struct game* game, size_t y) {
        for (size_t x = 1; x < SIZE; x++) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            char current_tile = game->board[y][x];
            for (size_t i = x - 1; i != -1; i--) {
                if (game->board[y][i] == ' ') {
                    game->board[y][i] = current_tile;
                    game->board[y][i + 1] = ' ';
                }
            }
        }
    }

    void merge_tiles_left(struct game* game, size_t y) {
        for (size_t x = 1; x < SIZE; x++) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            if (game->board[y][x] == game->board[y][x - 1]) {
                game->board[y][x - 1]++;
                game->score += add_score(game->board[y][x - 1]);
                game->board[y][x] = ' ';
            }
        }
    }

    void shift_tiles_up(struct game* game, size_t x) {
        for (size_t y = 1; y < SIZE; y++) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            char current_tile = game->board[y][x];
            for (size_t i = y - 1; i != -1; i--) {
                if (game->board[i][x] == ' ') {
                    game->board[i][x] = current_tile;
                    game->board[i + 1][x] = ' ';
                }
            }
        }
    }

    void merge_tiles_up(struct game* game, size_t x) {
        for (size_t y = 1; y < SIZE; y++) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            if (game->board[y][x] == game->board[y - 1][x]) {
                game->board[y - 1][x]++;
                game->score += add_score(game->board[y - 1][x]);
                game->board[y][x] = ' ';
            }
        }
    }

    void shift_tiles_down(struct game* game, size_t x) {
        for (size_t y = SIZE - 2; y != -1; y--) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            char current_tile = game->board[y][x];
            for (size_t i = y + 1; i < SIZE; i++) {
                if (game->board[i][x] == ' ') {
                    game->board[i][x] = current_tile;
                    game->board[i - 1][x] = ' ';
                }
            }
        }
    }

    void merge_tiles_down(struct game* game, size_t x) {
        for (size_t y = SIZE - 2; y != -1; y--) {
            if (game->board[y][x] == ' ') {
                continue;
            }
            if (game->board[y][x] == game->board[y + 1][x]) {
                game->board[y + 1][x]++;
                game->score += add_score(game->board[y + 1][x]);
                game->board[y][x] = ' ';
            }
        }
    }
bool update(struct game *game, int dy, int dx) {
    bool board_changed = false;

    if ((dy != 0 && dy != 1 && dy != -1) || (dx != 0 && dx != 1 && dx != -1)) {
        return false;
    }

    if (dx == 1) { // pravo
        for (size_t y = 0; y < SIZE; y++) {
            shift_tiles_right(game, y);
            merge_tiles_right(game, y);
            shift_tiles_right(game, y);
        }
        board_changed = true;
    } else if (dx == -1) { // lavo
        for (size_t y = 0; y < SIZE; y++) {
            shift_tiles_left(game, y);
            merge_tiles_left(game, y);
            shift_tiles_left(game, y);
        }
        board_changed = true;
    }

    if (dy == 1) { // dole
        for (size_t x = 0; x < SIZE; x++) {
            shift_tiles_down(game, x);
            merge_tiles_down(game, x);
            shift_tiles_down(game, x);
        }
        board_changed = true;
    } else if (dy == -1) { // hore
        for (size_t x = 0; x < SIZE; x++) {
            shift_tiles_up(game, x);
            merge_tiles_up(game, x);
            shift_tiles_up(game, x);
        }
        board_changed = true;
    }

    return board_changed;
}

