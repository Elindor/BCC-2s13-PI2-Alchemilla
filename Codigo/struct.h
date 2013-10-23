#ifndef Aaargh   /* Proteção */
#define Aaargh


struct element{
    int ElNum;
    char ElName[30];
    int ElType;
    struct element *prox;;
};
typedef struct element lista;

#endif
