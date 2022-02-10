#include <stdio.h>
#include <stdlib.h>

#define MYFILENAME "testimage.ppm" // Ihr Filename
#define X_PIXEL 200 // Ihre Bildbreite
#define Y_PIXEL 200 // Ihre Bildhöhe


int blue;
int green;
int red;

int ausgabeArray[X_PIXEL][Y_PIXEL][3];

int create_ppm() {
    FILE *p_file = fopen(MYFILENAME, "w");
    if (NULL != p_file) {
        fprintf(p_file, "P3\n %d %d\n 255\n", X_PIXEL, Y_PIXEL);
        for (int i = 0; i < X_PIXEL; i++) {
            for (int j = 0; j < Y_PIXEL; j++) {
                fprintf(p_file, "%d %d %d ", ausgabeArray[i][j][0], ausgabeArray[i][j][1], ausgabeArray[i][j][2]);
            }
            fprintf(p_file, "\n");
        }
        fprintf(p_file, "\n %d %d %d", 255, 255, 255);
        fclose(p_file);
    }
}

void setRedGreenBlueOnCord();

void zeichneGrossesQuadrat();

void zeichneQuadrate();

void ungeradeBerechnung();

int main() {
    for (int i = 0; i < X_PIXEL; i++)
        for (int j = 0; j < Y_PIXEL; j++)
            for (int k = 0; k < 3; k++)
                ausgabeArray[i][j][k] = 255;
    //Farben der Quadrate
    red = 0;
    green = 100;
    blue = 255;
    zeichneGrossesQuadrat();
    zeichneQuadrate(5);
    //Farben der Linien
    red = 255;
    green = 0;
    blue = 0;
    create_ppm();

}

void zeichneGrossesQuadrat() {
    for (int i = 0; i < X_PIXEL; i++) {
        setRedGreenBlueOnCord(i, 0);
        setRedGreenBlueOnCord(i, Y_PIXEL - 1);
    }
    for (int i = 0; i < Y_PIXEL; i++) {
        setRedGreenBlueOnCord(0, i);
        setRedGreenBlueOnCord(X_PIXEL - 1, i);
    }
}

void zeichneQuadrate(int anzahlQuadrate) {
    int xGroesseQuadrat = X_PIXEL / anzahlQuadrate;
    int yGroesseQuadrat = Y_PIXEL / anzahlQuadrate;
    for(int i = 0; i <= X_PIXEL - xGroesseQuadrat; i += xGroesseQuadrat) {
        for(int j = 0; j < Y_PIXEL; j++) {
            setRedGreenBlueOnCord(i,j);
        }
    }
    for(int j = 0; j <= Y_PIXEL - yGroesseQuadrat; j += yGroesseQuadrat) {
        for(int i = 0; i < X_PIXEL; i++) {
            setRedGreenBlueOnCord(i,j);
        }
    }
}

void ungeradeBerechnung(int anzahlQuadrate) {

}

void setRedGreenBlueOnCord(int x, int y) {
    ausgabeArray[x][y][0] = red;
    ausgabeArray[x][y][1] = green;
    ausgabeArray[x][y][2] = blue;
}