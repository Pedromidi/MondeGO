//Pedro Miguel Dinis Sequeira - 2020132079

#include "Paragens.h"

int menuParagens(){
    int n;
    printf("\n***** PARAGENS *****");
    printf("\nO que pretende fazer: ");
    printf("\n1 - Visualizar Paragens");
    printf("\n2 - Adicionar Paragem");
    printf("\n3 - Eliminar Paragem");
    printf("\n4 - Voltar");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}



paragens* trataParagens(int mP, paragens *tab, int *n){
    do{
        switch(mP){
            case 1:
                visualizaParagens(tab, *n);
                break;
            case 2:
                tab = adicionaParagem(tab, n);
                break;
            case 3:
                tab = eliminaParagem(tab, n);
                break;
            case 4:
                break;
            default:
                printf("Por favor introduza uma opcao valida!\n");
                break;
            return tab;
        }
        if(mP!=4)
            mP = menuParagens();
    }while(mP!=4);
    return tab;
}



void visualizaParagens(paragens *tab, int n){
    if(n==0){
        printf("Nao existem paragens a listar\n");
    }
    for(int i=0; i<n; ++i){
        printf("Paragem:\n\tNome: %s\n\tCodigo: %s\n\tLinhas a que pertence: %d\n",tab[i].nome,tab[i].codigo, tab[i].nlinhas);
    }
}


paragens* adicionaParagem(paragens *tab, int *n){
    paragens *p;
    char nome[TAMNOME];
    char cod[TAMCOD];
    int flagN=1, flagC=1, i, j, pos;
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    do{
        printf("Nome da paragem a adicionar: ");
        scanf(" %99[^\n]", &nome);
        for(i=0; i<(*n); i++){
            if((*n)==0){
                flagN=0;
                break;
            }
            else if(strcmp(nome, tab[i].nome)==0){
                printf("\nJa existe uma paragem com este nome, por favor introduza outro!\n");
                break;
            }
        }
        if(i==(*n))
            flagN=0;
    }while(flagN==1);

    do{
        srand(time(NULL));

        for (j=0; j<TAMCOD-1; j++) {
            pos = rand() % 36;
            cod[j] = digits[pos];
        }
        cod[TAMCOD-1] = '\0';

        for(i=0; i<(*n); i++){
            if((*n)==0){
                flagC=0;
                break;
            }
            else if(strcmp(cod, tab[i].codigo)==0){
                printf("\nCódigo já existe. A gerar novo codigo...\n");
                break;
            }
        }
        if(i==(*n))
            flagC=0;
    }while(flagC==1);

    p = realloc(tab, sizeof(paragens) * (*n+1));

    if(p != NULL){
        tab = p;
        strcpy(tab[*n].nome, nome);
        strcpy(tab[*n].codigo, cod);
        tab[*n].nlinhas = 0;
        ++(*n);
    }
    else{
        printf("\nErro na alocacao de memória para nova Paragem\n");
    }

    return tab;
}



paragens* eliminaParagem(paragens *tab, int *n){
    char st[TAMCOD];
    int i;
    paragens *aux, t;

    printf("Codigo da paragem a eliminar: ");
    scanf(" %s", st);

    for(i=0; i<*n && strcmp(st, tab[i].codigo)!=0; i++);
    if(i==*n){
        printf("\nParagem requesitada nao existe\n");
        return tab;
    }
    else if(*n==1){
        if(tab[i].nlinhas!=0){
            printf("\nParagem nao pode ser removida pois encontra-se numa linha\n");
            return tab;
        }
        free(tab);
        *n=0;
        return NULL;
    }
    else{
        if(tab[i].nlinhas!=0){
            printf("\nParagem nao pode ser removida pois encontra-se numa ou mais linhas\n");
            return tab;
        }

        t = tab[i];
        tab[i] = tab[*n-1];
        aux = realloc(tab, sizeof(paragens) * (*n-1));

        if(aux!=NULL){
            tab = aux;
            (*n)--;
        }
        else
            tab[i] = t;

        return tab;
    }
}


int guardaDadosParagem(paragens *tab, int total){
    FILE *f;
    int i;

    f = fopen("savedFile.dat", "wb");
    if(f==NULL){
        return 0;
    }

    fwrite(&total, sizeof(int), 1, f);
    fwrite(tab, sizeof(paragens), total, f);
    fclose(f);

    return 1;
}


paragens* leDadosParagens(int *total){
    FILE *f;
    paragens *tab = NULL;
    *total = 0;

    f = fopen("savedFile.dat", "rb");
    if(f==NULL){
        printf("Erro no acesso ao ficheiro para criacao de paragens\n");
        return NULL;
    }

    fread(total, sizeof(int), 1, f);

    tab = malloc(sizeof(paragens) * (*total));
    if(tab == NULL){
        fclose(f); *total = 0;
        return NULL;
    }

    fread(tab, sizeof(paragens), *total, f);
    fclose(f);

    return tab;
}
