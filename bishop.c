static int elem_in = 0;

void NE(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i >= 0; i--) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[elem_in] = (8 * i + file);
            file++;
            elem_in++;
        }
    }
}

void WS(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i <= 7; i++) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[elem_in] = (8 * i + file);
            file--;
            elem_in++;
        }
    }
}

void WN(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i >= 0; i--) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[elem_in] = (8 * i + file);
            file--;
            elem_in++;
        }
    }
}

void SE(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i <= 7; i++) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[elem_in] = (8 * i + file);
            file++;
            elem_in++;
        }
    }
}

int* validateBishop(int* all_possible_moves, int rank, int file) {

    NE(all_possible_moves, rank, file);
    WS(all_possible_moves, rank, file);
    WN(all_possible_moves, rank, file);
    SE(all_possible_moves, rank, file);

    for(int i = elem_in; i < 32; i++) {
        all_possible_moves[i] = -1;
    }

    elem_in = 0;

    return all_possible_moves;

}
