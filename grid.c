#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMSYM      44

#define NUMCIRCLE   10
#define NUMSQUARE   12
#define NUMTRIANGLE 11
#define NUMDIAMOND  11

#define HALFC       14
#define HALFS       29
#define HALFT       28
#define HALFD       20

typedef struct _symbol {
   char shape;
   int value;
   int x;
   int y;
   int clue;
} sym;


sym * newSym (char, int, int, int, int);
sym ** allSyms ();
int printSyms (sym **, int);

/* MAIN */
int main (int argc, char * argv[]) {
    printSyms (allSyms(), NUMSYM);

    return 0;
}

/* Create a new symbol with the values (constructor-like) */
sym * newSym (char shape, int value, int x, int y, int clue) {
    sym * pSym = NULL;

    pSym = malloc (sizeof(sym));
    if (pSym == NULL)
        return NULL;

    pSym->shape = shape;
    pSym->value = value;
    pSym->x = x;
    pSym->y = y;
    pSym->clue = clue;

    return pSym;
}

/* Create a list of all symbols on grid */
sym ** allSyms () {
    sym ** symTbl = NULL;

    symTbl = malloc (sizeof (sym*) * NUMSYM);
    if (symTbl == NULL)
        return NULL;
    /*                 shape val x  y clue */
    symTbl[0] = newSym ('c', 4, 2, 1, 4);
    symTbl[1] = newSym ('c', 2, 6, 1, 1);
    symTbl[2] = newSym ('t', 2, 1, 2, 4);
    symTbl[3] = newSym ('t', 8, 3, 2, 4);
    symTbl[4] = newSym ('d', 8, 11, 2, 2);
    symTbl[5] = newSym ('d', 0, 2, 3, 4);
    symTbl[6] = newSym ('d', 2, 3, 3, 4);
    symTbl[7] = newSym ('c', 1, 7, 3, 1);
    symTbl[8] = newSym ('t', 1, 10, 3, 2);
    symTbl[9] = newSym ('c', 5, 3, 4, 4);
    symTbl[10] = newSym ('t', 0, 5, 4, 1);
    symTbl[11] = newSym ('t', 5, 6, 4, 1);
    symTbl[12] = newSym ('c', 4, 12, 4, 4);
    symTbl[13] = newSym ('d', 4, 15, 4, 3);
    symTbl[HALFC] = newSym ('c', 2, 3, 5, 4);
    symTbl[15] = newSym ('d', 4, 10, 5, 4);
    symTbl[16] = newSym ('c', 6, 12, 5, 4);
    symTbl[17] = newSym ('d', 2, 13, 5, 3);
    symTbl[18] = newSym ('c', 6, 15, 5, 3);
    symTbl[19] = newSym ('c', 2, 1, 6, 4);
    symTbl[HALFD] = newSym ('d', 6, 7, 6, 2);
    symTbl[21] = newSym ('d', 2, 14, 6, 1);
    symTbl[22] = newSym ('d', 2, 3, 7, 4);
    symTbl[23] = newSym ('t', 1, 5, 7, 2);
    symTbl[24] = newSym ('c', 7, 6, 7, 2);
    symTbl[25] = newSym ('s', 6, 8, 7, 2);
    symTbl[26] = newSym ('t', 8, 11, 7, 4);
    symTbl[27] = newSym ('s', 1, 13, 7, 1);
    symTbl[HALFT] = newSym ('t', 0, 1, 8, 3);
    symTbl[HALFS] = newSym ('s', 5, 4, 8, 3);
    symTbl[30] = newSym ('s', 1, 5, 8, 2);
    symTbl[31] = newSym ('s', 2, 7, 8, 2);
    symTbl[32] = newSym ('s', 7, 15, 8, 1);
    symTbl[33] = newSym ('t', 2, 15, 9, 1);
    symTbl[34] = newSym ('s', 2, 1, 10, 3);
    symTbl[35] = newSym ('t', 1, 3, 10, 3);
    symTbl[36] = newSym ('s', 9, 9, 10, 2);
    symTbl[37] = newSym ('d', 7, 6, 11, 1);
    symTbl[38] = newSym ('s', 7, 1, 12, 3);
    symTbl[39] = newSym ('t', 6, 1, 13, 1);
    symTbl[40] = newSym ('s', 3, 1, 14, 1);
    symTbl[41] = newSym ('s', 4, 6, 14, 2);
    symTbl[42] = newSym ('d', 8, 10, 14, 2);
    symTbl[43] = newSym ('s', 9, 4, 15, 1);

    return symTbl;
}

/* print symbols, each has the format <sym><val> */
int printSyms (sym ** tbl, int syms) {
    int i, j, k;

    if (syms == 0) return 0;

    /* table headers */
    for (i = 1; i <= 15; i++) {
        if (i < 10)
            printf ("%d  ", i);
        else
            printf ("%d ", i);
    }
    printf ("\n");

    /* do the first symbol, since we cant reference index -1 for spacing */
    for (i = 1; i < tbl[0]->y; i++)
        printf ("__ __ __ __ __ __ __ __ __ __ __ __ __ __ __\n");
    for (i = 1; i < tbl[0]->x; i++)
        printf ("__ ");
    printf ("%c%d ", tbl[0]->shape, tbl[0]->value);

    for (i = 1; i < syms; i++) {
        /* check for new line(s) */
        j = tbl[i-1]->y;
        k = tbl[i-1]->x;
        while (j < tbl[i]->y) {
            while (k < 15) {
                printf("__ ");
                k++;
            }
            printf ("\n");
            k = 0;
            j++;
        }

        /* catch up to position in right line */
        while(k < tbl[i]->x - 1) {
            printf("__ ");
            k++;
        }

        /* print the symbol */
        printf ("%c%d ", tbl[i]->shape, tbl[i]->value);
        k++;

        /* print the rest of empty table if at end */
        if (i == syms - 1) {
            while (j <= 15) {
                while (k < 15) {
                    printf ("__ ");
                    k++;
                }
                printf ("\n");
                k = 0;
                j++;
            }
        }

    }

    return 0;
}
