#include <ctype.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#define width 480
#define height 480
#define sqSize 60

static char *pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; // FOR FEN
static int piece_info = 0;

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

    for(int file = 0; file < 8; file++) {
        for(int rank = 0; rank < 8; rank++) {
            bool isLightSquared = (file + rank) % 2 != 0;
            Color color = isLightSquared ? WHITE : DARKPURPLE;
            DrawRectangle(file * sqSize, rank * sqSize, sqSize, sqSize, color);
        }
    }

    // ------------------- FEN -------------------

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

    for(int file = 0; file < 8; file++) {
        for(int rank = 0; rank < 8; rank++) {

            if(squareBoard[8 * rank + file] == 9) {
                DrawTexture(LoadTextureFromImage(white_king), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 10) {
                DrawTexture(LoadTextureFromImage(white_pawn), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 11) {
                DrawTexture(LoadTextureFromImage(white_knight), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 12) {
                DrawTexture(LoadTextureFromImage(white_bishop), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 13) {
                DrawTexture(LoadTextureFromImage(white_rook), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 14) {
                DrawTexture(LoadTextureFromImage(white_queen), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 17) {
                DrawTexture(LoadTextureFromImage(black_king), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 18) {
                DrawTexture(LoadTextureFromImage(black_pawn), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 19) {
                DrawTexture(LoadTextureFromImage(black_knight), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 20) {
                DrawTexture(LoadTextureFromImage(black_bishop), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 21) {
                DrawTexture(LoadTextureFromImage(black_rook), file * sqSize, rank * sqSize, RAYWHITE);
            }

            if(squareBoard[8 * rank + file] == 22) {
                DrawTexture(LoadTextureFromImage(black_queen), file * sqSize, rank * sqSize, RAYWHITE);
            }

        }
    }


    while(!WindowShouldClose()) {

        // ------------------- TRACKING MOUSE -------------------

        int mouseX = GetMouseX() / sqSize;
        int mouseY = GetMouseY() / sqSize;
        int mouseOnBoard = mouseY * 8 + mouseX;

        if(IsMouseButtonPressed(0)) {
            if(squareBoard[mouseOnBoard] != 0 && piece_info == 0) {
                piece_info = squareBoard[mouseOnBoard];
                squareBoard[mouseOnBoard] = 0;
            } else {
                squareBoard[mouseOnBoard] = piece_info;
                piece_info = 0;
            }
        }

        BeginDrawing();

        EndDrawing();

    }

    return 0;

}
