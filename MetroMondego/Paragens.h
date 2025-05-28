//Pedro Miguel Dinis Sequeira - 2020132079

#ifndef PARAGENS_H_INCLUDED
#define PARAGENS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMNOME 100
#define TAMCOD 5

typedef struct{
    char nome[TAMNOME];
    char codigo[TAMCOD];
    int nlinhas;
}paragens;

int menuParagens();                                     //ll 5
paragens* trataParagens(int mP, paragens *tab, int *n); //ll 21
void visualizaParagens(paragens *tab, int n);           //ll 48
paragens* adicionaParagem(paragens *tab, int *n);       //ll 58
paragens* eliminaParagem(paragens *tab, int *n);        //ll 123
int guardaDadosParagem(paragens *tab, int total);       //ll 167
paragens* leDadosParagens(int *total);                  //ll 184


#endif // PARAGENS_H_INCLUDED
