int q_elem_in = 0;

void NEQ(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i >= 0; i--) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[q_elem_in] = (8 * i + file);
            file++;
            q_elem_in++;
        }
    }
}

void WSQ(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i <= 7; i++) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[q_elem_in] = (8 * i + file);
            file--;
            q_elem_in++;
        }
    }
}

void WNQ(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i >= 0; i--) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[q_elem_in] = (8 * i + file);
            file--;
            q_elem_in++;
        }
    }
}

void SEQ(int* all_possible_moves, int rank, int file) {
    for(int i = rank; i <= 7; i++) {
        if(file >= 0 && file <= 7) {
            all_possible_moves[q_elem_in] = (8 * i + file);
            file++;
            q_elem_in++;
        }
    }
}

int* validateQueen(int* all_possible_moves, int rank, int file) {

    WSQ(all_possible_moves, rank, file);
    WNQ(all_possible_moves, rank, file);
    SEQ(all_possible_moves, rank, file);
    NEQ(all_possible_moves, rank, file);

    for(int i = 0; i < 8; i++) {
        all_possible_moves[q_elem_in] = (8 * rank + i);
        q_elem_in++;
    }

    for(int i = 0; i < 8; i++) {
        all_possible_moves[q_elem_in] = (8 * i + file);
        q_elem_in++;
    }

    for(int i = q_elem_in; i < 40; i++) {
        all_possible_moves[i] = -1;
    }

    q_elem_in = 0;

    return all_possible_moves;

}

