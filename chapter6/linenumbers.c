/*
 Store every line a word appears on in text
 Sort the words lexographically
 Print out the words and their occurenes
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 100 /* max lines stored per word */
#define MAXLEN 15    /* max word length stored */

int getword(char *, int, FILE *);

/* for fgetch and fungetch */
#define BUFSIZE 100
char getchbuf[BUFSIZE];
char getchp = 0;

void fungetch(char);
char fgetch(FILE *);

/* binary tree */
struct node {
    char *word;
    int *lines;
    int cline;
    struct node *left;
    struct node *right;
};

struct node *addnode(char *, int, struct node *);
void treeprint(struct node *);

int main(int argc, char const *argv[])
{
    FILE *fp;
    fp = fopen("speech.txt", "r");

    char word[MAXLEN];
    int ch, line;
    struct node *root = NULL;
    line = 0;

    while ((ch = getword(word, MAXLEN, fp)) != EOF)
    {
        if (isalpha(ch))
            root = addnode(word, line, root);
        else if (ch == '\n')
            line++;
    }

    treeprint(root);

    fclose(fp);
    return 0;
}

struct node *talloc(void)
{
    return (struct node *) malloc(sizeof(struct node));
}

struct node *addnode(char *word, int line, struct node *p)
{
    int cond;

    if (p == NULL) 
    {   /* make a new node */
        p = talloc();
        p->word = strdup(word);
        p->lines = (int *) malloc(sizeof(int) * MAXLINES);
        (p->lines)[0] = line;
        p->cline = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(word, p->word)) == 0)
    {
        if (p->cline < MAXLINES && !((p->lines)[p->cline - 1] == line))
        {
            (p->lines)[p->cline++] = line;
        }
    }
    else if (cond < 0)
        p->left = addnode(word, line, p->left);
    else 
        p->right = addnode(word, line, p->right);
    return p;
}

void treeprint(struct node *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%s: ", p->word);
        for (int i = 0; i < p->cline; i++)
            printf("%i ", (p->lines)[i]);
        printf("\n");
        treeprint(p->right);
    }
}

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

char fgetch(FILE *fp)
{
    return (getchp > 0) ? getchbuf[--getchp] : fgetc(fp);
}

void fungetch(char c)
{
    if (getchp >= BUFSIZE)
        printf("fungetch: too many characters\n");
    else
        getchbuf[getchp++] = c;
}

