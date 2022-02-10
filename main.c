#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MYFILENAME "testimage.ppm" // Ihr Filename
#define X_PIXEL 200 // Ihre Bildbreite
#define Y_PIXEL 200 // Ihre Bildhöhe


int blue;
int green;
int red;

int ausgabeArray[Y_PIXEL][X_PIXEL][3];

struct dotPosition {
    int x;
    int y;
};

struct xyGroesse {
    int x;
    int y;
    int maxX;
    int maxY;
};

int create_ppm() {
    FILE *p_file = fopen(MYFILENAME, "w");
    if (NULL != p_file) {
        fprintf(p_file, "P3\n %d %d\n 255\n", X_PIXEL, Y_PIXEL);
        for (int i = 0; i < Y_PIXEL; i++) {
            for (int j = 0; j < X_PIXEL; j++) {
                fprintf(p_file, "%d %d %d ", ausgabeArray[i][j][0], ausgabeArray[i][j][1], ausgabeArray[i][j][2]);
            }
            fprintf(p_file, "\n");
        }
        fclose(p_file);
    }
}

void setRedGreenBlueOnCord();

void zeichneGrossesQuadrat();

void zeichneQuadrate();

void ungeradeBerechnung();

void connectDots();

struct xyGroesse berechneMaximaleQuadratGroesse();

int main() {
    int anzahlQuadrate = 3;
    for (int i = 0; i < X_PIXEL; i++)
        for (int j = 0; j < Y_PIXEL; j++) {
            for (int k = 0; k < 3; k++) {
                ausgabeArray[j][i][k] = 255;
            }
        }
    int anzahlDots = (((5 * anzahlQuadrate) + (anzahlQuadrate + 1)) * (anzahlQuadrate + 1)) + ((5*anzahlQuadrate)* (anzahlQuadrate +1));
    struct dotPosition connectDots[anzahlDots];
    struct dotPosition centralDots[anzahlQuadrate * anzahlDots];
    //Farben der Quadrate
    red = 0;
    green = 100;
    blue = 255;
//    zeichneGrossesQuadrat();
    zeichneQuadrate(anzahlQuadrate);
    //Farben der Linien
    red = 255;
    green = 0;
    blue = 0;
    create_ppm();

}

struct xyGroesse berechneMaximaleQuadratGroesse(int anzahlQuadrate) {
    struct xyGroesse tmpGroesse;
    int x = X_PIXEL - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (x % anzahlQuadrate == 0) {
            tmpGroesse.x = x / anzahlQuadrate;
            tmpGroesse.maxX = X_PIXEL - i;
            i = anzahlQuadrate;
        } else {
            x--;
        }
    }
    int y = Y_PIXEL - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (y % anzahlQuadrate == 0) {
            tmpGroesse.y = y / anzahlQuadrate;
            tmpGroesse.maxY = Y_PIXEL - i;
            i = anzahlQuadrate;
        } else {
            y--;
        }
    }
    return tmpGroesse;
}


void zeichneQuadrate(int anzahlQuadrate) {
    struct xyGroesse quadratGroesse = berechneMaximaleQuadratGroesse(anzahlQuadrate);
    for (int i = 0; i < quadratGroesse.maxX; i = i + 1 + quadratGroesse.x) {
        for (int j = 0; j < quadratGroesse.maxY; j++) {
            setRedGreenBlueOnCord(j, i);
        }
    }
    for (int j = 0; j < quadratGroesse.maxY; j = j + 1 + quadratGroesse.y) {
        for (int i = 0; i < quadratGroesse.maxX; i++) {
            setRedGreenBlueOnCord(j, i);
        }
    }

    red = 255;
    green = 0;
    blue = 0;
    connectDots(quadratGroesse);
}

void connectDots(struct xyGroesse quadratgroesse) {
    for (int i = 0; i <= quadratgroesse.maxX; i = i + 1 + quadratgroesse.x) {
        for (int j = 0; j <= quadratgroesse.maxY; j = j + 1 + quadratgroesse.y) {
            setRedGreenBlueOnCord(j, i);
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