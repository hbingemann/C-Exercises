#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
struct nlist *undef(char *);

int main(int argc, char const *argv[])
{
    install("MAX", "100");
    install("dog", "cat");
    install("soccer", "football");
    install("hello", "hallo");
    install("poop", "pee");

    char s[] = "poop";
    struct nlist *p;

    printf("lookup(%s): %s\n", s, (p = lookup(s)) == NULL ? "NULL" : p->defn);
    undef(s);
    printf("lookup(%s): %s\n", s, (p = lookup(s)) == NULL ? "NULL" : p->defn);

    return 0;
}

/* undef: remove name from table */
struct nlist *undef(char *name)
{
    struct nlist *np;

    np = hashtab[hash(name)];
    hashtab[hash(name)] = np->next;
    return np;
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

