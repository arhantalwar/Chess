#include <stdio.h>
#include <raylib.h>

#define width 480
#define height 480
#define sqSize 60

Color lightSquare = (Color){240, 217, 181, 255};
Color darkSquare = (Color){22, 21, 18, 255};

//static char *pos = "rr"; // FOR FEN

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

    // ------------------- WHITE -------------------

    squareBoard[0] = Rook | White;
    squareBoard[7] = Rook | White;

    squareBoard[1] = Knight | White;
    squareBoard[6] = Knight | White;

    squareBoard[2] = Bishop | White;
    squareBoard[5] = Bishop | White;

    squareBoard[3] = King | White;
    squareBoard[4] = Queen | White;

    squareBoard[8] = Pawn | White;
    squareBoard[9] = Pawn | White;
    squareBoard[10] = Pawn | White;
    squareBoard[11] = Pawn | White;
    squareBoard[12] = Pawn | White;
    squareBoard[13] = Pawn | White;
    squareBoard[14] = Pawn | White;
    squareBoard[15] = Pawn | White;

    // ------------------- BLACK -------------------

    squareBoard[48] = Pawn | Black;
    squareBoard[49] = Pawn | Black;
    squareBoard[50] = Pawn | Black;
    squareBoard[51] = Pawn | Black;
    squareBoard[52] = Pawn | Black;
    squareBoard[53] = Pawn | Black;
    squareBoard[54] = Pawn | Black;
    squareBoard[55] = Pawn | Black;

    squareBoard[56] = Rook | Black;
    squareBoard[63] = Rook | Black;

    squareBoard[57] = Knight | Black;
    squareBoard[62] = Knight | Black;

    squareBoard[58] = Bishop | Black;
    squareBoard[61] = Bishop | Black;

    squareBoard[59] = King | Black;
    squareBoard[60] = Queen | Black;

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

    // ------------------- TRACKING MOUSE -------------------


    while(!WindowShouldClose()) {

        int mouseX = GetMouseX() / sqSize;
        int mouseY = GetMouseY() / sqSize;
        int mouseOnBoard = mouseY * 8 + mouseX;

        BeginDrawing();

        EndDrawing();

    }

    return 0;

}