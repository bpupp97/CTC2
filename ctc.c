#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

#define MAXRD   250

char * sanitize (char **);
char * caesar (char **, int);
int wordMatch (char *, char *);
int wordnMatch (char *, char *, int);
char * paCipher (char *, char *, int);
int * letterFreq (char *);

int main(int argc, char * argv[]) {
    FILE * fd = NULL;
    FILE * fd2 = NULL;
    char * rdLine = NULL;
    char * rdLine2 = NULL;
    size_t rdLen = 0;
    size_t rdLen2 = 0;
    char * buffer = NULL;
    int i, j;
    int * freq;

    if (argc < 2)
        goto usage;

    /*
    * CAESAR CIPHER
    */
    if (strcmp (argv[1], "-caesar") == 0) {
        /* caesar cipher for the given shift */
        if (argc != 3 && argc != 4)
            goto usage;

        if ( (fd = fopen (argv[2], "r")) != NULL) {
            /* interpret the arg as a file */

            /* do this in advance to save additional calls */
            while (getline (&rdLine, &rdLen, fd) != -1) {
                sanitize (&rdLine);
                if (argc == 4) {
                    printf ("%s\n", caesar (&rdLine, atoi(argv[3])));
                } else {
                    printf ("%s\n", rdLine);
                    for (i = 0; i < 25; i++)
                        printf ("%s\n", caesar (&rdLine, 1));
                }
                free (rdLine);
                rdLine = NULL;
            }

        } else {
            /* interpret the arg as a string */
            rdLine = malloc (strlen (argv[2]) + 1);
            if (rdLine == NULL)
                goto memerr;
            strcpy (rdLine, argv[2]);
            sanitize (&rdLine);
            if (argc == 4) {
                printf ("%s\n", caesar (&rdLine, atoi(argv[3])));
            } else {
                printf ("%s\n", rdLine);
                for (i = 0; i < 25; i++)
                    printf ("%s\n", caesar (&rdLine, 1));
            }
        }
    }
    /*
    * POLYALPHABETIC CIPHER
    */
    else if (strcmp (argv[1], "-pa") == 0) {
        if (argc == 4)
            j = 1;
        else if (argc == 5 && strcmp(argv[4], "-de") == 0)
            j = -1;
        else
            goto usage;

        if ( (fd = fopen (argv[2], "r")) != NULL) {
            /* interpret arg1 as a file */
            if ( (fd2 = fopen (argv[3], "r")) != NULL) {
                /* interpret arg2 as a file */

                while ( (getline (&rdLine, &rdLen, fd)) != -1 ) {
                    sanitize (&rdLine);
                    printf("%s\n", rdLine);
                    while ( (getline (&rdLine2, &rdLen2, fd2)) != -1 ) {
                        sanitize (&rdLine2);
                        buffer = paCipher (rdLine, rdLine2, j);
                        printf ("%s\n", buffer);
                        free (buffer);
                        free (rdLine2);
                        rdLine2 = NULL;
                    }
                    free (rdLine);
                    rdLine = NULL;

                    rewind (fd2);
                }

            } else {
                /* interpret arg2 as a string */
                rdLine2 = malloc (strlen (argv[3]) + 1);
                if (rdLine2 == NULL)
                    goto memerr;
                strcpy (rdLine2, argv[3]);
                sanitize (&rdLine2);

                while ( (getline (&rdLine, &rdLen, fd)) != -1 ) {
                    sanitize (&rdLine);
                    buffer = paCipher (rdLine, rdLine2, j);
                    printf ("%s\n", buffer);
                    free (buffer);
                    free (rdLine);
                    rdLine = NULL;
                }
            }
        } else {
            /* interpret arg1 as a string */
            if ( (fd2 = fopen (argv[3], "r")) != NULL) {
                /* interpret arg2 as a file */
                rdLine = malloc (strlen (argv[2]) + 1);
                if (rdLine == NULL)
                    goto memerr;

                strcpy (rdLine, argv[2]);
                sanitize (&rdLine);

                while ( (getline (&rdLine2, &rdLen2, fd2)) != -1 ) {
                    sanitize (&rdLine2);
                    buffer = paCipher (rdLine, rdLine2, j);
                    printf ("%s\n", buffer);
                    free (buffer);
                    free (rdLine2);
                    rdLine2 = NULL;
                }

            } else {
                /* interpret arg2 as a string */
                rdLine = malloc (strlen (argv[2]) + 1);
                rdLine2 = malloc (strlen (argv[3]) + 1);
                if (rdLine == NULL | rdLine2 == NULL)
                    goto memerr;

                strcpy (rdLine, argv[2]);
                strcpy (rdLine2, argv[3]);

                sanitize (&rdLine);
                sanitize (&rdLine2);

                printf ("%s\n", paCipher (rdLine, rdLine2, j));
            }
        }
    }
    /*
    * MATCHING STRINGS
    */
    else if (strcmp (argv[1], "-match") == 0) {
        if (argc == 4)
            i = 1;
        else if (argc == 5)
            i = atoi(argv[4]);
        else
            goto usage;

        if ( (fd = fopen (argv[2], "r")) != NULL) {
            /* interpret arg1 as a file */
            if ( (fd2 = fopen (argv[3], "r")) != NULL) {
                /* interpret arg2 as a file */

                while ( (getline (&rdLine, &rdLen, fd)) != -1 ) {
                    sanitize (&rdLine);
                    while ( (getline (&rdLine2, &rdLen2, fd2)) != -1 ) {
                        sanitize (&rdLine2);

                        if ( (j = wordnMatch (rdLine, rdLine2, i)) != -1 )
                            printf ("%s %s %d\n", rdLine, rdLine2, j);

                        free (rdLine2);
                        rdLine2 = NULL;
                    }
                    free (rdLine);
                    rdLine = NULL;

                    rewind (fd2);
                }

            } else {
                /* interpret arg2 as a string */
                rdLine2 = malloc (strlen (argv[3]) + 1);
                if (rdLine2 == NULL)
                    goto memerr;
                strcpy (rdLine2, argv[3]);
                sanitize (&rdLine2);

                while ( (getline (&rdLine, &rdLen, fd)) != -1 ) {
                    sanitize (&rdLine);

                    if ( (j = wordnMatch (rdLine, rdLine2, i)) != -1 )
                        printf ("%s %s %d\n", rdLine, rdLine2, j);
                    
                    free (rdLine);
                    rdLine = NULL;
                }
            }
        } else {
            /* interpret arg1 as a string */
            if ( (fd2 = fopen (argv[3], "r")) != NULL) {
                /* interpret arg2 as a file */
                rdLine = malloc (strlen (argv[2]) + 1);
                if (rdLine == NULL)
                    goto memerr;

                strcpy (rdLine, argv[2]);
                sanitize (&rdLine);

                while ( (getline (&rdLine2, &rdLen2, fd2)) != -1 ) {
                    sanitize (&rdLine2);

                    if ( (j = wordnMatch (rdLine, rdLine2, i)) != -1 )
                        printf ("%s %s %d\n", rdLine, rdLine2, j);
                    
                    free (rdLine2);
                    rdLine2 = NULL;
                }

            } else {
                /* interpret arg2 as a string */
                rdLine = malloc (strlen (argv[2]) + 1);
                rdLine2 = malloc (strlen (argv[3]) + 1);
                if (rdLine == NULL | rdLine2 == NULL)
                    goto memerr;

                strcpy (rdLine, argv[2]);
                strcpy (rdLine2, argv[3]);

                sanitize (&rdLine);
                sanitize (&rdLine2);
                
                if ( (j = wordnMatch (rdLine, rdLine2, i)) != -1 )
                    printf ("%s %s %d\n", rdLine, rdLine2, j);
            }
        }
 
    }
    /*
    * FILTER BY LENGTH
    */
    else if (strcmp (argv[1], "-len") == 0) {
        if (argc != 4)
            goto usage;

        if ( (fd = fopen (argv[2], "r")) == NULL) {
            printf ("FAILED TO OPEN FILE '%s'\n", argv[2]);
            return -1;
        }

        i = atoi (argv[3]);
        while ( getline (&rdLine, &rdLen, fd) != -1 ) {
            sanitize (&rdLine);
            if (strlen (rdLine) == i)
                printf ("%s\n", rdLine);
            free (rdLine);
            rdLine = NULL;
        }
    }
    else if (strcmp (argv[1], "-freq") == 0) {
        if (argc != 3)
            goto usage;

        if ( (fd = fopen (argv[2], "r")) != NULL) {
            /* read frequency from file */
            fseek (fd, 0, SEEK_END);
            i = ftell(fd);
            rewind (fd);

            rdLine = malloc (i);
            if (rdLine == NULL)
                goto memerr;

            fread (rdLine, 1, i, fd);
            freq = letterFreq (rdLine);

            for (i = 0; i < 26; i++) {
                if (freq[i] != 0)
                    printf ("%c : %d\n", 'a' + i, freq[i]);
            }

        } else {
            /* read frequency from arg string */
            rdLine = malloc (strlen (argv[2]));
            if (rdLine == NULL)
                goto memerr;

            strcpy (rdLine, argv[2]);
            
            for (i = 0; i < 26; i++) {
                if (freq[i] != 0)
                    printf ("%c : %d\n", 'a' + i, freq[i]);
            }
        } 
    }
    else if (strcmp (argv[1], "-sanitize") == 0) {
        if (argc != 3)
            goto usage;

        if ( (fd = fopen (argv[2], "r")) == NULL) {
            printf ("FAILED TO OPEN FILE '%s'\n", argv[2]);
            return -1           /* read frequency from file */;
        }

        while ( getline (&rdLine, &rdLen, fd) != -1 ) {
            sanitize (&rdLine);
            printf("%s\n", rdLine);
            free (rdLine);
            rdLine = NULL;
        }
    }
    /*
    * INVALID
    */
    else {
        goto usage;
    }

     


    return 0;

usage:
    printf ("USAGE: ctc -caesar <text/file> <offset>\n"
            "       ctc -pa <text/file> <key/file>\n"
            "       ctc -match <text/file> <key/file> (index)\n"
            "       ctc -len <file> <length>\n"
            "       ctc -freq <text/file>\n"
            "       ctc -sanitize <file>\n");
    return -1;

memerr:
    printf ("FAILED TO ALLOCATE MEMORY!\n");
    return -1;
}


/* takes an input string, converts all upper-case to lower case,
removes anything that isnt a letter. Will stop at a null character
or EOL */
char * sanitize (char ** inputStr) {
    int idx;
    int skips;
    int length = strlen (*inputStr);

    skips = 0;
    for (idx = 0; idx < length; idx++) {
        /* uppercase letter, add 32 and append */
        if ((*inputStr)[idx] >= 'A' &&
            (*inputStr)[idx] <= 'Z') {
            (*inputStr)[idx - skips] = (*inputStr)[idx] + 32;
            }
        /* lowercase letter, just shift in case skips != 0 */
        else if ((*inputStr)[idx] >= 'a' &&
            (*inputStr)[idx] <= 'z') {
            (*inputStr)[idx - skips] = (*inputStr)[idx];
            }
        /* invalid character, increment skips value */
        else {
            if ((*inputStr)[idx] == '\n' || (*inputStr)[idx] == 0x00)
                break;
            skips++;
        }
    }
    /* set null character */
    (*inputStr)[idx - skips] = 0x00;
    return *inputStr;
}

/* takes an input string, modifies the given string by a shift
of <shift> characters. loops at z->a */
char * caesar (char ** inputStr, int shift) {
    int idx;
    int length = strlen (*inputStr);

    for (idx = 0; idx < length; idx++) {
        if ((*inputStr)[idx] == 0x00)
            break;
        (*inputStr)[idx] = ((((*inputStr)[idx] - 'a') + shift) % 26) + 'a';
    }

    return *inputStr;
}

/* returns an index for the first occurance of a substring 'word'
within string 'searchSpace'. for the nth occurance, use
wordnMatch */
int wordMatch (char * searchSpace, char * word) {
    return wordnMatch (searchSpace, word, 1);
}

int wordnMatch (char * searchSpace, char * word, int occurance) {
    int idx;
    int matchCnt;
    int spaceLen = strlen (searchSpace);
    int wordLen = strlen (word);

    matchCnt = 0;
    idx = 0;
    while (idx + wordLen <= spaceLen) {
        /* TODO : rewrite to allow wildcards */
        if (strncmp ((searchSpace + idx), word, wordLen) == 0) {
            matchCnt++;
            if (matchCnt == occurance)
                return idx;
        }
        idx++;
    }

    return -1;
}


/* returns a polyaphabetic shift using <key> on <pt>, stored
in a new string, leaving the original untouched. key must be
all lowercase letters */
char * paCipher (char * pt, char * key, int dir) {
    int idx;

    int ptLen = strlen(pt);
    int keyLen = strlen(key);
    
    char * ct = malloc (ptLen+1);
    if (ct == NULL)
        return NULL;
    memset (ct, 0, ptLen+1);

    /* check the key for bad characters */
    for (idx = 0; idx < keyLen; idx++) {
        if (key[idx] < 'a' || key[idx] > 'z')
            return NULL;
    }

    for (idx = 0; idx < ptLen; idx++) {
        ct[idx] = pt[idx] - 'a';                    /* convert to a letter index */
        ct[idx] += dir * (key[idx % keyLen] - 'a'); /* add or subtract key letter */
        ct[idx] = ((ct[idx] + 26) % 26) + 'a';      /* normalize mod and make letter*/
    }

    return ct;
}

/* Counts the letter frequencies of the input language, only counts letters */
int * letterFreq (char * language) {
    int llen = strlen (language);
    int i;

    int * freq;
    freq = malloc (26 * sizeof (int));
    if (freq == NULL)
        return NULL;

    for (i = 0; i < 26; i++)
        freq[i] = 0;

    for (i = 0; i < llen; i++) {
        if (language[i] >= 'a' || language[i] <= 'z')
            freq[language[i] - 'a']++;
        else if (language[i] >= 'A' || language[i] <= 'A')
            freq[language[i] - 'A']++;
    }

    return freq;
}

