/**
 * Autor: Simon Berndt - DHBW Heidenheim
 * Last Change: 21.03.2022
 * Erstellung einer Rastergrafik nach gegebener Vorlage
 * Version 2.0 Alpha
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "draw.h"

#define MYFILENAME "ausgabe.ppm" // Ihr Filename


struct dotPosition calculateCentralDots();

struct xyGroesse berechneMaximaleQuadratGroesse();

struct xyGroesse zeichneQuadrate();

void calculateConnectDots();

int main() {
    setbuf(stdout, 0);
    int xPixel = 2000;
    int yPixel = 1000;
    int anzahlQuadrate = 5;

    //Background Color
    struct color background = {0, 0, 0};

    //Front Color
    struct color forground = {255, 255, 255};

    //Quadrat Color
    struct color quadrat = {255, 255, 255};

    do {
        printf("\nwie viele Quadrate moechten sieh in einer Zeile und Spalte haben\n");
        printf("Bitte denken sie daran, desto groesser die Anzahl der Quadrate wird, desto groesser sollten sie später den Ausgabebereich waehlen.\n");
        printf("Bitte geben sie eine Zahl ein; Bsp: 5\n");
    } while(0 == scanf("%d", &anzahlQuadrate));

    char yesNo;
    do {
        char ch = getchar();
        printf("\n");
        printf("Soll der Ausgabebereich quadratisch sein\n");
        printf("Y oder y wird JA, jede andere Eingabe wird als NEIN interpretiert!\n");
    } while (0 == scanf("%s", &yesNo));

    if (yesNo == 'Y' || yesNo == 'y') {
        int pixel;
        do {
            char ch = getchar();
            printf("\n");
            printf("Wie gross soll der Anzeigebereich sein\n");
            printf("Die hoechstmoegliche Zahl ist Computer abhaengig, normalerweise sollte bis 10000px kein Problem sein.\n");
            printf("Einfach als Zahl in Pixelgroesse angeben. Bsp.: 1000\n");
            printf("bitte mindestens 100 Pixel, eher mehr, da das sonst erzeugte Bild keinen sinn ergibt\n");
        } while (0 == scanf("%d", &pixel));
        xPixel = pixel;
        yPixel = pixel;
    } else {
        do {
            char ch = getchar();
            printf("\n");
            printf("Wie gross soll der Anzeigebereich sein\n");
            printf("Erste Zahl wird der X Wert, zweite Zahl der Y Wert\n");
            printf("Einfach als Zahl in Pixelgroesse angeben. Bsp.: 2000 1000\n");
            printf("bitte mindestens 100 Pixel, eher mehr, da das sonst erzeugte Bild keinen sinn ergibt\n");
        } while (0 == scanf("%d %d", &xPixel, &yPixel));
    }

    do {
        char ch = getchar();
        printf("\n");
        printf("Moechtest du als Hintergrundfarben die Standard Werte verwenden (Hintergrund: schwarz, Vordergrund: weiss) --> Y/y\n");
        printf("jede andere Eingabe wird als NEIN interpretiert!\n");
        printf("wenn du selbst entscheiden moechtest, kannst du die Farben fuer den Hintergrund, fuer die Linien der Quadrate und fuer die Linien in den Quadraten selbst bestimmen\n");
    } while (0 == scanf("%s", &yesNo));

    if (yesNo != 'Y' && yesNo != 'y') {
        do {
            char ch = getchar();
            printf("\n");
            printf("Geben sie den RGB Wert fuer den Hintergrund an. Bsp. 0 0 0\n");
            printf("\n min: 0, max: 255; 3 Zahlen jeweils mit Leerzeichen getrennt\n");
        } while (0 == scanf("%d %d %d", &background.r, &background.g, &background.b));
        do {
            char ch = getchar();
            printf("\n");
            printf("Geben sie den RGB Wert fuer den Vordergrund an. Bsp. 255 255 255\n");
            printf("\n min: 0, max: 255; 3 Zahlen jeweils mit Leerzeichen getrennt\n");
        } while (0 == scanf("%d %d %d", &forground.r, &forground.g, &forground.b));
        do {
            char ch = getchar();
            printf("\n");
            printf("Geben sie den RGB Wert fuer die Quadrate an. Bsp. 0 255 0\n");
            printf("\n min: 0, max: 255; 3 Zahlen jeweils mit Leerzeichen getrennt\n");
        } while (0 == scanf("%d %d %d", &quadrat.r, &quadrat.g, &quadrat.b));
    } else {
        forground.r = 255;
        forground.g = 255;
        forground.b = 255;
        background.r = 0;
        background.g = 0;
        background.b = 0;
        quadrat.r = 255;
        quadrat.g = 255;
        quadrat.b = 255;
    }

    printf("\nBerechnung der Datei gestartet!!!\n");

    clock_t start = clock();
    int *ausgabeArray = malloc(xPixel * yPixel * sizeof(int));

    for (int i = 0; i < yPixel; i++) {
        for (int j = 0; j < xPixel; j++) {
            setPixel(i, j, ausgabeArray, xPixel, 0);
        }
    }
    struct xyGroesse quadratGroesse = zeichneQuadrate(anzahlQuadrate, ausgabeArray, xPixel, yPixel);
    calculateConnectDots(quadratGroesse, ausgabeArray, yPixel, xPixel, anzahlQuadrate);
    clock_t berechnung = clock();
    int zeitBerechnung = (int) (berechnung - start) / CLOCKS_PER_SEC;

    printf("\nDie Berechnung dauerte %d Sekunden", zeitBerechnung);
    printf("\nErstellung der .ppm Datei gestartet, bei grosser Pixel Zahl kann dies lange dauern.\n");
    create_ppm(xPixel, yPixel, ausgabeArray, background, forground, quadrat);
    clock_t end = clock();
    int endZeit = (int) (end - berechnung) / CLOCKS_PER_SEC;

    printf("\nDie Erstellung der Datei dauerte %d Sekunden", endZeit);
    printf("\n\n PROGRAM SLEEPS 5 SECONDS UNTIL IT STOPS.");
    sleep(5);
    return 0;
}

struct xyGroesse berechneMaximaleQuadratGroesse(int anzahlQuadrate, int xPixel, int yPixel) {
    struct xyGroesse tmpGroesse;
    int x = xPixel - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (x % anzahlQuadrate == 0) {
            tmpGroesse.x = x / anzahlQuadrate;
            tmpGroesse.maxX = xPixel - i;
            i = anzahlQuadrate;
        } else {
            x--;
        }
    }
    int y = yPixel - (anzahlQuadrate + 1);//steht fuer verfuegbare Flaeche von denen die QuadratLinien abgezogen werden
    for (int i = 0; i < anzahlQuadrate; i++) {
        if (y % anzahlQuadrate == 0) {
            tmpGroesse.y = y / anzahlQuadrate;
            tmpGroesse.maxY = yPixel - i;
            i = anzahlQuadrate;
        } else {
            y--;
        }
    }
    return tmpGroesse;
}


struct xyGroesse zeichneQuadrate(int anzahlQuadrate, int ausgabeArray[], int xPixel, int yPixel) {
    struct xyGroesse quadratGroesse = berechneMaximaleQuadratGroesse(anzahlQuadrate, xPixel, yPixel);
    for (int i = 0; i < quadratGroesse.maxX; i = i + 1 + quadratGroesse.x) {
        for (int j = 0; j < quadratGroesse.maxY; j++) {
            setPixel(j, i, ausgabeArray, xPixel, 2);
        }
    }
    for (int j = 0; j < quadratGroesse.maxY; j = j + 1 + quadratGroesse.y) {
        for (int i = 0; i < quadratGroesse.maxX; i++) {
            setPixel(j, i, ausgabeArray, xPixel, 2);
        }
    }
    return quadratGroesse;
}

void
calculateConnectDots(struct xyGroesse quadratgroesse, int ausgabeArray[], int yPixel, int xPixel, int anzahlQuadrate) {
    int xAbstandDots = quadratgroesse.x / (anzahlQuadrate + 1);
    int moduloXDots = quadratgroesse.x % (anzahlQuadrate + 1);
    int xZusatz = 0;
    if (moduloXDots > 3) {
        xAbstandDots++;
    } else {
        xZusatz++;
    }
    int yAbstandDots = quadratgroesse.y / (anzahlQuadrate + 1);
    int moduloYDots = quadratgroesse.x % (anzahlQuadrate + 1);
    int yZusatz = 0;
    if (moduloYDots > 3) {
        yAbstandDots++;
    } else {
        yZusatz++;
    }

    int quadratCountY = 0;
    for (int i = 0; i < quadratgroesse.maxY - 1; i = i + quadratgroesse.y + 1) {
        int quadratCountX = 0;
        for (int j = 0; j < quadratgroesse.maxX - 1; j = j + quadratgroesse.x + 1) {

            struct dotPosition dotArray[anzahlQuadrate * 4 + 4];

            struct dotPosition tmp = {i, j};
            dotArray[0] = tmp;

            struct dotPosition tmp1 = {i + quadratgroesse.y + 1, j};
            dotArray[1] = tmp1;

            struct dotPosition tmp2 = {i + quadratgroesse.y + 1, j + quadratgroesse.x + 1};
            dotArray[2] = tmp2;

            struct dotPosition tmp3 = {i, j + quadratgroesse.x + 1};
            dotArray[3] = tmp3;

            int count = 0;
            int dotCount = 4;

            for (int k = yAbstandDots + yZusatz; count < anzahlQuadrate; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = yAbstandDots + yZusatz; count < anzahlQuadrate; k += yAbstandDots) {
                struct dotPosition tmp4 = {i + k, j + quadratgroesse.x + 1};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = xAbstandDots + xZusatz; count < anzahlQuadrate; k += xAbstandDots) {
                struct dotPosition tmp4 = {i, j + k};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            count = 0;

            for (int k = xAbstandDots + xZusatz; count < anzahlQuadrate; k += xAbstandDots) {
                struct dotPosition tmp4 = {i + quadratgroesse.y + 1, j + k};
                dotArray[dotCount] = tmp4;
                count++;
                dotCount++;
            }
            struct dotPosition mittelpunkt = calculateCentralDots(anzahlQuadrate, dotArray, quadratCountY,
                                                                  quadratCountX);

            for (int l = 0; l < (anzahlQuadrate * 4 + 4); l++) {
                line(mittelpunkt.x, mittelpunkt.y, dotArray[l].x, dotArray[l].y, ausgabeArray, yPixel, xPixel);
            }
            quadratCountX++;
        }
        quadratCountY++;
    }
}

struct dotPosition
calculateCentralDots(int anzahlQuadrate, struct dotPosition quadratDots[], int yQuadrat, int xQuadrat) {
    struct dotPosition mittelpunkt;
    mittelpunkt.y = quadratDots[4 + yQuadrat].y;
    mittelpunkt.x = quadratDots[4 + (anzahlQuadrate * 2) + xQuadrat].x;
    return mittelpunkt;
}