#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "rook.c"
#include "bishop.c"
#include "knight.c"
#include "queen.c"
#include "king.c"
#include "pawn.c"

#define width 480
#define height 480
#define sqSize 60
#define all_possible_moves_len 40

static char *pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

enum piece { 
    None = 0, 
    King = 1, 
    Pawn = 2, 
    Knight = 3, 
    Bishop = 4, 
    Rook = 5, 
    Queen = 6, 
    White = 8, 
    Black = 16,
};

static int piece_info = 0;
static int pos_piece_info = -1;
static int all_possible_moves[all_possible_moves_len] = { 0 };

void drawChessBoard() {
    for(int file = 0; file < 8; file++) {
        for(int rank = 0; rank < 8; rank++) {
            bool isLightSquared = (file + rank) % 2 != 0;
            Color color = isLightSquared ? DARKPURPLE : WHITE;
            DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, color);
        }
    }
}

void fixHighlightedSquares() {
    for(int i = 0; i < all_possible_moves_len; i++) {
        if(all_possible_moves[i] != -1) {
            int rank = all_possible_moves[i] / 8;
            int file = all_possible_moves[i] % 8;
            bool isLightSquared = (file + rank) % 2 != 0;
            Color color = isLightSquared ? DARKPURPLE : WHITE;
            DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, color);
        }
    }
}

void show() {
    printf("+++++++++++++++++++++++\n");
    for(int i = 0; i < all_possible_moves_len; i++) {
        if(all_possible_moves[i] != -1)
            printf("%d ", all_possible_moves[i]);
    }
    printf("\n+++++++++++++++++++++++\n");
}

void drawAllPossibleSquares() {
    for(int i = 0; i < all_possible_moves_len; i++) {
        if(all_possible_moves[i] != -1) {
            int rank = all_possible_moves[i] / 8;
            int file = all_possible_moves[i] % 8;
            DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, ColorAlpha(RED, 0.6));
        }
    }
}

//------------------------ BISHOP 

int whereIsTargetOnDiagonal(int targetPos) {
    
    int tRank = targetPos / 8;
    int tFile = targetPos % 8;

    int sRank = pos_piece_info / 8;
    int sFile = pos_piece_info % 8;

    if(tFile < sFile) {

        if(tRank < sRank) {
            return  1;
        }

        if(tRank > sRank) {
            return  3;
        }

    } else {

        if(tRank < sRank) {
            return  2;
        }

        if(tRank > sRank) {
            return  4;
        }

    }

    return 0;

}

bool diagonalPiecesValidMoveCheck(int targetPos, int* squareBoard) {
    
    int whereTo = whereIsTargetOnDiagonal(targetPos);
    int pos_piece_info_copy = pos_piece_info;

    while(pos_piece_info_copy != targetPos) {

        if(whereTo == 1) {
            pos_piece_info_copy -= 9;

        } else if (whereTo == 2) {
            pos_piece_info_copy -= 7;

        } else if (whereTo == 3) {
            pos_piece_info_copy += 7;

        } else if (whereTo == 4) {
            pos_piece_info_copy += 9;

        }

        if(pos_piece_info_copy == targetPos) {

            int a = squareBoard[pos_piece_info_copy] >> 3;
            int b = piece_info >> 3;

            if((a ^ b) == 3) {
                return true;
            }

        }

        if(squareBoard[pos_piece_info_copy] != 0) {
            printf("PIECE IN THE WAY\n");
            return false;
        }

    }

    return true;

}

// ----------------------------------- ROOK

int whereIsTargetOnStraightLine(int targetPos) {
    
    int tRank = targetPos / 8;
    int tFile = targetPos % 8;

    int sRank = pos_piece_info / 8;
    int sFile = pos_piece_info % 8;

    if(tFile < sFile) {
        return 1;
    }

    if(tRank < sRank) {
        return 2;
    }

    if(tFile > sFile) {
        return 3;
    }

    if(tRank > sRank) {
        return 4;
    }

    return 0;

}

bool straightPiecesValidMoveCheck(int targetPos, int* squareBoard) {
    
    int whereTo = whereIsTargetOnStraightLine(targetPos);
    int pos_piece_info_copy = pos_piece_info;

    while(pos_piece_info_copy != targetPos) {

        if(whereTo == 1) {
            pos_piece_info_copy -= 1;

        } else if (whereTo == 2) {
            pos_piece_info_copy -= 8;

        } else if (whereTo == 3) {
            pos_piece_info_copy += 1;

        } else if (whereTo == 4) {
            pos_piece_info_copy += 8;

        }

        if(pos_piece_info_copy == targetPos) {

            int a = squareBoard[pos_piece_info_copy] >> 3;
            int b = piece_info >> 3;

            if((a ^ b) == 3) {
                return true;
            }

        }
        
        if(squareBoard[pos_piece_info_copy] != 0) {
            printf("PIECE IN THE WAY\n");
            return false;
        }

    }

    return true;

}

// ----------------------------------- KNIGHT

bool knightPiecesValidMoveCheck(int targetPos, int* squareBoard) {

    if(squareBoard[targetPos] == 0) {
        return true;
    }

    int a = squareBoard[targetPos] >> 3;
    int b = piece_info >> 3;

    if((a ^ b) == 3) {
        return true;
    }

    return false;

}
    
// ----------------------------------- KING

bool kingPiecesValidMoveCheck(int targetPos, int* squareBoard) {

    if(squareBoard[targetPos] == 0) {
        return true;
    }

    int a = squareBoard[targetPos] >> 3;
    int b = piece_info >> 3;

    if((a ^ b) == 3) {
        return true;
    }

    return false;

}

bool isMoveInPossible(int targetPos) {

    int first = 0;
    int last = all_possible_moves_len - 1;

    while(first <= last){

        int mid = (first + last) / 2;

        if(targetPos == all_possible_moves[mid]){

            return true;

        } else if(all_possible_moves[mid] > targetPos){
            last = mid - 1;
        } else{
            first = mid + 1;
        }

    }

    return false;

}

void sortList() {
    bool swapped=false;
    for(int i = all_possible_moves_len-1; i >=1; i--) {
        swapped = false;
        for(int j = 0; j <= i-1; j++) {
            if(all_possible_moves[j] > all_possible_moves[j+1]) {
                int temp = all_possible_moves[j];
                all_possible_moves[j] = all_possible_moves[j+1];
                all_possible_moves[j+1] = temp;
                swapped = true;
            }
        }
        if(swapped == false) {
            break;
        }
    }
}

void removeDupFromList() {
    for(int i = 0; i < all_possible_moves_len; i++) {
        if(all_possible_moves[i] == all_possible_moves[i + 1]) {
            all_possible_moves[i] = -1;
        }
    }
}

void initChessBoard(int *squareBoard) {

    for(int file = 0; file < 8; file++) {
        for(int rank = 0; rank < 8; rank++) {
            bool isLightSquared = (file + rank) % 2 != 0;
            Color color = isLightSquared ? DARKPURPLE : WHITE;
            DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, color);
        }
    }

    int file = 0;
    int rank = 0;

    for(int i = 0; i < strlen(pos); i++) {

        char *c = &pos[i];

        if(isdigit(*c)) {

            file += atoi(c);

        } else if (strncmp("/", c, 1) == 0) {

            rank++;
            file = 0;

        } else {

            if (strncmp("k", c, 1) == 0) {
                squareBoard[8 * rank + file] = 17;
            }

            if (strncmp("p", c, 1) == 0) {
                squareBoard[8 * rank + file] = 18;
            }

            if (strncmp("n", c, 1) == 0) {
                squareBoard[8 * rank + file] = 19;
            }

            if (strncmp("b", c, 1) == 0) {
                squareBoard[8 * rank + file] = 20;
            } 

            if (strncmp("r", c, 1) == 0) {
                squareBoard[8 * rank + file] = 21;
            } 

            if (strncmp("q", c, 1) == 0) {
                squareBoard[8 * rank + file] = 22;
            } 

            if(strncmp("K", c, 1) == 0) {
                squareBoard[8 * rank + file] = 9;
            } 

            if (strncmp("P", c, 1) == 0) {
                squareBoard[8 * rank + file] = 10;
            } 

            if (strncmp("N", c, 1) == 0) {
                squareBoard[8 * rank + file] = 11;
            } 

            if (strncmp("B", c, 1) == 0) {
                squareBoard[8 * rank + file] = 12;
            } 

            if (strncmp("R", c, 1) == 0) {
                squareBoard[8 * rank + file] = 13;
            } 

            if (strncmp("Q", c, 1) == 0) {
                squareBoard[8 * rank + file] = 14;
            }

            file++;

        }

    }
}

void updateChessBoard(
        int *squareBoard,
        Image white_pawn,
        Image white_knight,
        Image white_queen,
        Image white_king,
        Image white_bishop,
        Image white_rook,
        Image black_pawn,
        Image black_knight,
        Image black_queen,
        Image black_king,
        Image black_bishop,
        Image black_rook
        ) {

    for(int file = 0; file < 8; file++) {
        for(int rank = 0; rank < 8; rank++) {

            if(squareBoard[8 * rank + file] == None) {
                if((rank + file) % 2 != 0) {
                    DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, DARKPURPLE);
                } else {
                    DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, WHITE);
                }
            }

            if(squareBoard[8 * rank + file] == (King | White)) {
                DrawTexture(LoadTextureFromImage(white_king), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Pawn | White)) {
                DrawTexture(LoadTextureFromImage(white_pawn), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Knight | White)) {
                DrawTexture(LoadTextureFromImage(white_knight), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Bishop | White)) {
                DrawTexture(LoadTextureFromImage(white_bishop), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Rook | White)) {
                DrawTexture(LoadTextureFromImage(white_rook), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Queen | White)) {
                DrawTexture(LoadTextureFromImage(white_queen), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (King | Black)) {
                DrawTexture(LoadTextureFromImage(black_king), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Pawn | Black)) {
                DrawTexture(LoadTextureFromImage(black_pawn), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Knight | Black)) {
                DrawTexture(LoadTextureFromImage(black_knight), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Bishop | Black)) {
                DrawTexture(LoadTextureFromImage(black_bishop), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Rook | Black)) {
                DrawTexture(LoadTextureFromImage(black_rook), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == (Queen | Black)) {
                DrawTexture(LoadTextureFromImage(black_queen), file * sqSize, rank * sqSize, RAYWHITE);
            }

        }
    }

}

int main(void) {

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(width, height, "CHESS BOARD");
    SetTargetFPS(60);

    // ------------------- LOADING IMAGES -------------------

    Image black_king= LoadImage("./Chess Pieces/black_king.png");
    Image black_pawn = LoadImage("./Chess Pieces/black_pawn.png");
    Image black_knight = LoadImage("./Chess Pieces/black_knight.png");
    Image black_bishop = LoadImage("./Chess Pieces/black_bishop.png");
    Image black_rook = LoadImage("./Chess Pieces/black_rook.png");
    Image black_queen = LoadImage("./Chess Pieces/black_queen.png");

    Image white_king= LoadImage("./Chess Pieces/white_king.png");
    Image white_pawn = LoadImage("./Chess Pieces/white_pawn.png");
    Image white_knight = LoadImage("./Chess Pieces/white_knight.png");
    Image white_bishop = LoadImage("./Chess Pieces/white_bishop.png");
    Image white_rook = LoadImage("./Chess Pieces/white_rook.png");
    Image white_queen = LoadImage("./Chess Pieces/white_queen.png");

    // ------------------- DRAWING BOARD -------------------

    int squareBoard[64] = { 0 };

    initChessBoard(squareBoard);
    updateChessBoard(
            squareBoard,
            white_pawn,
            white_knight,
            white_queen,
            white_king,
            white_bishop,
            white_rook,
            black_pawn,
            black_knight,
            black_queen,
            black_king,
            black_bishop,
            black_rook
            );


    while(!WindowShouldClose()) {

        // ------------------- TRACKING MOUSE -------------------

        int mouseX = GetMouseX() / sqSize;
        int mouseY = GetMouseY() / sqSize;
        int mouseOnBoard = 8 * mouseY + mouseX;

        if(IsMouseButtonPressed(0)) {
            if(squareBoard[mouseOnBoard] != 0 && piece_info == 0) {
                piece_info = squareBoard[mouseOnBoard];
                pos_piece_info = mouseOnBoard;
                squareBoard[mouseOnBoard] = 0;

                switch (piece_info) {

                    case (White | Pawn):
                        validateWhitePawn(all_possible_moves, mouseY, mouseX);
                        break;

                    case (White | Rook):
                        validateRook(all_possible_moves, mouseY, mouseX);
                        break;

                    case (White | Bishop):
                        validateBishop(all_possible_moves, mouseY, mouseX);
                        break;

                    case (White | Knight):
                        validateKnight(all_possible_moves, mouseY, mouseX);
                        break;

                    case (White | Queen):
                        validateQueen(all_possible_moves, mouseY, mouseX);
                        break;

                    case (White | King):
                        validateKing(all_possible_moves, mouseY, mouseX);
                        break;

                    case (Black | Pawn):
                        validateBlackPawn(all_possible_moves, mouseY, mouseX);
                        break;

                    case (Black | Rook):
                        validateRook(all_possible_moves, mouseY, mouseX);
                        break;

                    case (Black | Bishop):
                        validateBishop(all_possible_moves, mouseY, mouseX);
                        break;

                    case (Black | Knight):
                        validateKnight(all_possible_moves, mouseY, mouseX);
                        break;

                    case (Black | Queen):
                        validateQueen(all_possible_moves, mouseY, mouseX);
                        break;

                    case (Black | King):
                        validateKing(all_possible_moves, mouseY, mouseX);
                        break;

                }

                sortList();
                removeDupFromList();
                sortList();
                show();

                drawAllPossibleSquares();

            } else {

                if(isMoveInPossible(mouseOnBoard)) {

                    bool canGoThrought = false;

                    switch (piece_info) {

                        case (White | Rook):
                            if(straightPiecesValidMoveCheck(mouseOnBoard, squareBoard) == true) {
                                canGoThrought = true;
                            }
                            break;

                        case (White | Bishop):
                            if(diagonalPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                        case (White | Queen):
                            if(straightPiecesValidMoveCheck(mouseOnBoard, squareBoard)
                            || diagonalPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                        case (White | Pawn):
                            canGoThrought = true;
                            break;

                        case (White | King):
                            if(kingPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                        case (White | Knight):
                            if(knightPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                        case (Black | Rook):
                            if(straightPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                        case (Black | Bishop):
                            if(diagonalPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                        case (Black | Queen):
                            if(straightPiecesValidMoveCheck(mouseOnBoard, squareBoard)
                            || diagonalPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;
                            
                        case (Black | Pawn):
                            canGoThrought = true;
                            break;
                            
                        case (Black | Knight):
                            if(knightPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;
                            
                        case (Black | King):
                            if(kingPiecesValidMoveCheck(mouseOnBoard, squareBoard)) {
                                canGoThrought = true;
                            }
                            break;

                    }

                    if(canGoThrought == true) {

                        squareBoard[mouseOnBoard] = 0;

                        updateChessBoard(
                                squareBoard,
                                white_pawn,
                                white_knight,
                                white_queen,
                                white_king,
                                white_bishop,
                                white_rook,
                                black_pawn,
                                black_knight,
                                black_queen,
                                black_king,
                                black_bishop,
                                black_rook
                                );

                        squareBoard[mouseOnBoard] = piece_info;

                        updateChessBoard(
                                squareBoard,
                                white_pawn,
                                white_knight,
                                white_queen,
                                white_king,
                                white_bishop,
                                white_rook,
                                black_pawn,
                                black_knight,
                                black_queen,
                                black_king,
                                black_bishop,
                                black_rook
                                );

                        fixHighlightedSquares();

                        updateChessBoard(
                                squareBoard,
                                white_pawn,
                                white_knight,
                                white_queen,
                                white_king,
                                white_bishop,
                                white_rook,
                                black_pawn,
                                black_knight,
                                black_queen,
                                black_king,
                                black_bishop,
                                black_rook
                                );

                    } else {

                    squareBoard[pos_piece_info] = piece_info;

                    fixHighlightedSquares();

                    updateChessBoard(
                            squareBoard,
                            white_pawn,
                            white_knight,
                            white_queen,
                            white_king,
                            white_bishop,
                            white_rook,
                            black_pawn,
                            black_knight,
                            black_queen,
                            black_king,
                            black_bishop,
                            black_rook
                            );

                    }

                } else {

                    squareBoard[pos_piece_info] = piece_info;

                    fixHighlightedSquares();

                    updateChessBoard(
                            squareBoard,
                            white_pawn,
                            white_knight,
                            white_queen,
                            white_king,
                            white_bishop,
                            white_rook,
                            black_pawn,
                            black_knight,
                            black_queen,
                            black_king,
                            black_bishop,
                            black_rook
                            );

                }

                piece_info = 0;
                pos_piece_info = -1;

            }
        }

        BeginDrawing();

        EndDrawing();

    }

    UnloadImage(black_king);
    UnloadImage(black_pawn);
    UnloadImage(black_rook);
    UnloadImage(black_bishop);
    UnloadImage(black_knight);
    UnloadImage(black_queen);

    UnloadImage(white_king);
    UnloadImage(white_pawn);
    UnloadImage(white_rook);
    UnloadImage(white_bishop);
    UnloadImage(white_knight);
    UnloadImage(white_queen);

    CloseWindow();

    return 0;

}
