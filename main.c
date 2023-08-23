#include <ctype.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "rook.c"
#include "bishop.c"

#define width 480
#define height 480
#define sqSize 60

static char *pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; // FOR FEN
static int piece_info = 0;
static int all_possible_moves[32] = { 0 };

void show() {
    for(int i = 0; i < 32; i++) {
        printf("%d ", all_possible_moves[i]);
    }
}

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
            validateBishop(all_possible_moves, mouseX, mouseY);
            show();
            if(squareBoard[mouseOnBoard] != 0 && piece_info == 0) {
                piece_info = squareBoard[mouseOnBoard];
                squareBoard[mouseOnBoard] = 0;
                switch (piece_info) {
                    case (White | Rook):
                        validateRook(all_possible_moves, mouseX, mouseY);
                        show();
                        break;
                }
            } else {
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
                piece_info = 0;
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
