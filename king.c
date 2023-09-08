#include <stdbool.h>

bool isLeftCastlingPossible(int* squareBoard) {
    for(int i = 57; i < 60; i++) {
        if(squareBoard[i] != 0) {
            return false;
        }
    }
    return true;
}

bool isRightCastlingPossible(int* squareBoard) {
    for(int i = 61; i < 63; i++) {
        if(squareBoard[i] != 0) {
            return false;
        }
    }
    return true;
}

int* validateKing(int* all_possible_moves, int rank, int file) {

    int k_elem_in = 0;

    for(int i = rank - 1; i <= rank + 1; i++) {
        if(i <= 7 && i >= 0) {
            for(int j = file - 1; j <= file + 1; j++) {
                if(j <= 7 && j >= 0) {
                    all_possible_moves[k_elem_in] = (8 * i + j);
                    k_elem_in++;
                }
            }
        }
    }

    for(int i = k_elem_in; i < 40; i++) {
        all_possible_moves[i] = -1;
    }

    k_elem_in = 0;

    return all_possible_moves;

}

