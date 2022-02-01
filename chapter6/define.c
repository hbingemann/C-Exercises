/*
    make a custom define statement that replaces words with their definition
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define BUFSIZE 100
#define MAXLEN 20 /* maxlen for word */

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
char getchbuf[BUFSIZE];
char getchp = 0;

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void ungetch(char);
char fgetch(FILE *);
int getword(char *, int, FILE *);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./define FILENAME");
        return 1;
    }

    FILE *inp = fopen(argv[1], "r");
    FILE *outp = fopen("outfile.c", "w");

    char define[] = "#define", *d = define;
    char s[MAXLEN], *p = s;
    char def[MAXLEN];
    struct nlist *np;

    loop:
        while ((*p = fgetch(inp)) != EOF)
        {
            if (*p++ == *d++)
            { /* check for new def */
                while ((*p++ = fgetch(inp)) == *d++)
                {
                    if (*d == '\0')
                    {
                        d = define;
                        getword(s, MAXLEN, inp);
                        getword(def, MAXLEN, inp);
                        install(s, def);
                        goto loop;
                    }
                }
                fputs(s, fp);
                p = s;
                goto loop;
            } else { /* check for replacement */
                for (int i = 0; i < HASHSIZE; i++)
                {
                    for (np = hashtab[i]; np != NULL; np = np->next)
                    {   /* loop through every word */
                        
                    }
                }
            }
            fputc(*p, fp);
        }
    return 0;
}

/* getword: write next word in file into 'word' */
int getword(char *word, int lim, FILE *fp)
{
    char ch, *w = word;
    while (isspace(ch = fgetch(fp)))  /* skip whitespace */
        if (ch == '\n')
            return ch;

    if (ch != EOF)
        *w++ = ch;
    if (!isalpha(ch))
    {
        *w = '\0';
        return ch;
    }
    for (; --lim > 0; w++)
    {
        if (!isalnum(*w = fgetch(fp))) {
            fungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

/* getch and ungetch: use buffer to place character back on stream */
char fgetch(FILE *fp)
{
    return (getchp > 0) ? getchbuf[--getchp] : fgetc(fp);
}

void ungetch(char c)
{
    if (getchp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        getchbuf[getchp++] = c;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)
    {   /* name not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);  /* free previous defn so that new defn can be put there */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

