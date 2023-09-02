int* validateWhitePawn(int* all_possible_moves, int rank, int file) {

    int p_elem_in = 0;

    for(int i = rank - 1; i < rank; i++) {
        if(i <= 7 && i >= 0) {
            for(int j = file - 1; j <= file + 1; j++) {
                if(j <= 7 && j >= 0) {
                    all_possible_moves[p_elem_in] = (8 * i + j);
                    p_elem_in++;
                }
            }
        }
    }

    if(rank == 6) {
        all_possible_moves[p_elem_in] = ((8 * (rank-2)) + file);
        p_elem_in++;
    }

    for(int i = p_elem_in; i < 32; i++) {
        all_possible_moves[i] = -1;
    }

    p_elem_in = 0;

    return all_possible_moves;

}

int* validateBlackPawn(int* all_possible_moves, int rank, int file) {

    int p_elem_in = 0;

    for(int i = rank + 1; i <= rank + 1; i++) {
        if(i <= 7 && i >= 0) {
            for(int j = file - 1; j <= file + 1; j++) {
                if(j <= 7 && j >= 0) {
                    all_possible_moves[p_elem_in] = (8 * i + j);
                    p_elem_in++;
                }
            }
        }
    }

    if(rank == 1) {
        all_possible_moves[p_elem_in] = ((8 * (rank+2)) + file);
        p_elem_in++;
    }

    for(int i = p_elem_in; i < 32; i++) {
        all_possible_moves[i] = -1;
    }

    p_elem_in = 0;

    return all_possible_moves;

}
