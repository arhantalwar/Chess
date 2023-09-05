int k_elem_in = 0;

void UP(int* all_possible_moves, int rank, int file) {
    
    if((rank - 2 >= 0) && (file - 1 >= 0)) {
        all_possible_moves[k_elem_in] = (8 * (rank - 2) + (file - 1));
        k_elem_in++;
    }

    if((rank - 2 >= 0) && (file + 1 <= 7)) {
        all_possible_moves[k_elem_in] = (8 * (rank - 2) + (file + 1));
        k_elem_in++;
    }

}

void DOWN(int* all_possible_moves, int rank, int file) {

    if((rank + 2 <= 7) && (file - 1 >= 0)) {
        all_possible_moves[k_elem_in] = (8 * (rank + 2) + (file - 1));
        k_elem_in++;
    }

    if((rank + 2 <= 7) && (file + 1 <= 7)) {
        all_possible_moves[k_elem_in] = (8 * (rank + 2) + (file + 1));
        k_elem_in++;
    }

}

void LEFT(int* all_possible_moves, int rank, int file) {

    if((file - 2 >= 0) && (rank - 1 >= 0)) {
        all_possible_moves[k_elem_in] = (8 * (rank - 1) + (file - 2));
        k_elem_in++;
    }

    if((file - 2 >= 0) && (rank + 1 <= 7)) {
        all_possible_moves[k_elem_in] = (8 * (rank + 1) + (file - 2));
        k_elem_in++;
    }

}

void RIGHT(int* all_possible_moves, int rank, int file) {

    if((file + 2 <= 7) && (rank - 1 >= 0)) {
        all_possible_moves[k_elem_in] = (8 * (rank - 1) + (file + 2));
        k_elem_in++;
    }

    if((file + 2 <= 7) && (rank + 1 <= 7)) {
        all_possible_moves[k_elem_in] = (8 * (rank + 1) + (file + 2));
        k_elem_in++;
    }

}

int* validateKnight(int* all_possible_moves, int rank, int file) {

    UP(all_possible_moves, rank, file);
    DOWN(all_possible_moves, rank, file);
    LEFT(all_possible_moves, rank, file);
    RIGHT(all_possible_moves, rank, file);

    for(int i = k_elem_in; i < 40; i++) {
        all_possible_moves[i] = -1;
    }

    k_elem_in = 0;

    return all_possible_moves;

}
