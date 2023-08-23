int* validateRook(int* all_possible_moves, int rank, int file) {

    int r_elem_in = 0;

    for(int i = 0; i < 8; i++) {
        all_possible_moves[r_elem_in] = (8 * file + i);
        r_elem_in++;
    }

    for(int i = 0; i < 8; i++) {
        all_possible_moves[r_elem_in] = (8 * i + rank);
        r_elem_in++;
    }

    for(int i = r_elem_in; i < 32; i++) {
        all_possible_moves[i] = -1;
    }

    return all_possible_moves;

}

//RANK -> 8 * file + i
//FILE -> 8 * i + rank
