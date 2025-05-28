//Pedro Miguel Dinis Sequeira - 2020132079

#ifndef LINHAS_H_INCLUDED
#define LINHAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Paragens.h"

typedef struct dados linha, *pLinha;
typedef struct pel paragemEmLinha, *pParagemEmLinha;

struct dados{
    char nome[TAMNOME];
    int numeroParagens;
    pParagemEmLinha lista;
    pLinha prox;
};

struct pel{
    paragens paragem;
    pParagemEmLinha prox;
};

int menuLinhas();                                               //ll 5
int menuSearch();                                               //ll 19
int menuEdit();                                                 //ll 32
int menuAdd();                                                  //ll 45
pLinha trataLinhas(int mL, pLinha *pL, paragens *tab, int *n);  //ll 58
void visualizaLinhas(pLinha p, char *nomelinha);                //ll 139
pLinha adicionaLinha(pLinha p);                                 //ll 177
pLinha adicionaLinhaFromFile(pLinha p, paragens *tab, int *n);  //ll 215
void addParagem(pLinha p, paragens *tab, int *n);               //ll 317
pLinha removeParagem(pLinha p, paragens *tab, int *n);          //ll 368
int guardaDadosLinhas(pLinha p);                                //ll 426
pLinha leDadosLinhas();                                         //ll 450
void calculaPercurso(pLinha p, paragens *tab, int *n);          //ll 518

#endif // LINHAS_H_INCLUDED
