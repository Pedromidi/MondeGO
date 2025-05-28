//Pedro Miguel Dinis Sequeira - 2020132079

#include "Linhas.h"

int menuLinhas(){
    int n;
    printf("\n***** LINHAS *****");
    printf("\nO que pretende fazer: ");
    printf("\n1 - Visualizar Linhas");
    printf("\n2 - Adicionar Linha");
    printf("\n3 - Atualizar Linha");
    printf("\n4 - Voltar");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}

int menuSearch(){
    int n;
    printf("\n***** LINHAS *****");
    printf("\nO que pretende fazer: ");
    printf("\n1 - Visualizar todas as Linhas");
    printf("\n2 - Visualizar Paragens de uma Linha");
    printf("\n3 - Voltar");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}

int menuEdit(){
    int n;
    printf("\n***** LINHAS *****");
    printf("\nO que pretende fazer: ");
    printf("\n1 - Adicionar Paragem a uma Linha");
    printf("\n2 - Remover Paragem de uma Linha");
    printf("\n3 - Voltar");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}

int menuAdd(){
    int n;
    printf("\n***** LINHAS *****");
    printf("\nO que pretende fazer: ");
    printf("\n1 - Adicionar Linha manualmente");
    printf("\n2 - Adicionar Linha atraves de ficheiro de texto");
    printf("\n3 - Voltar");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}

pLinha trataLinhas(int mL, pLinha *p, paragens *tab, int *n){
    int mVL, mEL, mAL;
    char lin[TAMNOME];
    do{
        switch(mL){
            case 1:
                mVL = menuSearch();
                do{
                    switch(mVL){
                    case 1:
                        visualizaLinhas(p, NULL);
                        break;
                    case 2:
                        printf("Nome da Linha a pesquisar: ");
                        scanf(" %99[^\n]", &lin);
                        visualizaLinhas(p, &lin);
                        break;
                    case 3:
                        break;
                    default:
                        printf("Por favor introduza uma opcao valida!\n");
                        break;
                    }
                    if(mVL!=3)
                        mVL = menuSearch();
                }while(mVL!=3);
                break;
            case 2:
                mAL = menuAdd();
                do{
                    switch(mAL){
                    case 1:
                        p = adicionaLinha(p);
                        break;
                    case 2:
                        p = adicionaLinhaFromFile(p, tab, n);
                        break;
                    case 3:
                        break;
                    default:
                        printf("Por favor introduza uma opcao valida!\n");
                        break;
                    }
                    if(mAL!=3)
                        mAL = menuAdd();
                }while(mAL!=3);
                break;
            case 3:
                mEL = menuEdit();
                do{
                    switch(mEL){
                    case 1:
                        addParagem(p, tab, n);
                        break;
                    case 2:
                        p = removeParagem(p, tab, n);
                        break;
                    case 3:
                        break;
                    default:
                        printf("Por favor introduza uma opcao valida!\n");
                        break;
                    }
                    return p;
                    if(mEL!=3)
                        mEL = menuEdit();
                }while(mEL!=3);
                break;
            case 4:
                break;
            default:
                printf("Por favor introduza uma opcao valida!\n");
                break;
        }
        if(mL!=4)
            mL = menuLinhas();
    }while(mL!=4);
    return p;
}


void visualizaLinhas(pLinha p, char *nomelinha){
    if(p==NULL){
        printf("\nNao existem Linhas a listar\n");
        return;
    }

    pLinha first = p;
    if(nomelinha == NULL){
        while(first != NULL){
            pParagemEmLinha aux = first->lista;
            printf("\nLinha: %s, Numero de paragens: %d\n", first->nome, first->numeroParagens);
            while(aux != NULL){
                printf("Paragem:\n\tNome: %s\n\tCodigo: %s\n\tLinhas a que pertence: %d\n", aux->paragem.nome, aux->paragem.codigo, aux->paragem.nlinhas);
                aux = aux->prox;
            }
            first = first->prox;
        }
    }

    else{
        while(first != NULL && strcmp(first->nome, nomelinha) != 0)
            first = first->prox;

        if(first!=NULL){
            pParagemEmLinha aux = first->lista;
            printf("\nLinha: %s, Numero de paragens: %d\n", first->nome, first->numeroParagens);
            aux = first->lista;
            while(aux != NULL){
                printf("Paragem:\n\tNome: %s\n\tCodigo: %s\n", aux->paragem.nome, aux->paragem.codigo);
                aux = aux->prox;
            }
        }
        else
            printf("\nLinha requirida nao existe no sistema\n");
    }
}


pLinha adicionaLinha(pLinha p){
    int flagN=1;
    pLinha novo;
    pLinha aux = p;

    char st[TAMNOME];
    novo = malloc(sizeof(linha));

    if(novo == NULL)
        return p;

    do{
        printf("Nome da linha a adicionar: ");
        scanf(" %99[^\n]", &st);
        while(p != NULL){
            if(strcmp(st, p->nome)==0){
                printf("\nJa existe uma linha com este nome, por favor introduza outro!\n");
                flagN=1;
                break;
            }
            p = p->prox;
        }
        if(p == NULL)
            flagN=0;
    }while(flagN==1);

    p=aux;
    strcpy(novo->nome, st);
    novo->numeroParagens = 0;
    novo->lista = NULL;
    novo->prox = p;
    p = novo;

    printf("\nLinha adicionada\n");
    return p;
}


pLinha adicionaLinhaFromFile(pLinha p, paragens *tab, int *n){
    char nomeLinha[TAMNOME], fullline[TAMNOME];
    char cod[TAMCOD];
    pLinha novo, aux=p;
    pParagemEmLinha novaPar;
    int i;

    novo = malloc(sizeof(linha));
    if(novo == NULL)
        return p;

    FILE *f = fopen("NovaLinha.txt", "rt");
    if(f){
        fgets(nomeLinha, TAMNOME, f);
        nomeLinha[strlen(nomeLinha) - 1] = '\0';

            while(p != NULL){
                if(strcmp(nomeLinha, p->nome)==0){
                    printf("\nJa existe uma linha com o nome apresentado no ficheiro, por favor verifique o ficheiro de texto!\n");
                    fclose(f);
                    return p;
                }
                    p = p->prox;
            }

        p=aux;
        strcpy(novo->nome, nomeLinha);
        novo->numeroParagens = 0;
        novo->lista = NULL;
        novo->prox = NULL;

        if(p == NULL)
            p = novo;

        else{
            pLinha ultimaLinha = p;
            while(ultimaLinha->prox != NULL){
                ultimaLinha = ultimaLinha->prox;
            }
            ultimaLinha->prox = novo;
        }

        while(fgets(fullline, TAMNOME, f)!=NULL){
            if(*n==0){
                printf("\nNao existem Paragens registadas no sistema, por favor verifique o ficheiro de texto!\n");
                return p;
            }

            novaPar = malloc(sizeof(pParagemEmLinha));
            if(novaPar == NULL)
                return p;

            const char* separatorPos = strchr(fullline, '#');
            strncpy(cod, separatorPos + 1, sizeof(cod) - 1);
            cod[4] = '\0';
            novaPar->prox = NULL;

            for(i=0; i<(*n); ++i){
                if(strcmp(tab[i].codigo, cod) == 0){
                    tab[i].nlinhas++;
                    strcpy(novaPar->paragem.nome, tab[i].nome);
                    strcpy(novaPar->paragem.codigo, tab[i].codigo);
                    novaPar->paragem.nlinhas = tab[i].nlinhas;
                    break;
                }
            }
            if(i==*n){
                printf("\nParagem requirida no ficheiro nao existe no sistema, por favor verifique o ficheiro de texto!\n");
                return;
            }

            printf("\n////ANTES///\n");
            printf("nome: %s", novaPar->paragem.nome);
            printf("codigo: %s", novaPar->paragem.codigo);
            printf("nr lins: %d", novaPar->paragem.nlinhas );

            p->numeroParagens++;
            pParagemEmLinha atual;
            atual = p->lista;

            if (p->lista == NULL) {
                p->lista = novaPar;
            }
            else{
                while (atual->prox != NULL)
                    atual = atual->prox;

                atual->prox = novaPar;
            }
        }

        printf("\nLinha adicionada\n");
        visualizaLinhas(p, NULL);
    }
    else
        printf("Erro ao abrir o ficheiro");

    fclose(f);
    return p;
}


void addParagem(pLinha p, paragens *tab, int *n){
    char st[TAMNOME];
    char cod[TAMCOD];
    int i;
    pLinha aux = p;
    pParagemEmLinha novo;

    if(*n==0){
        printf("\nNao existem Paragens registadas no sistema\n");
        return;
    }

    printf("\nQue Linha deseja atualizar: ");
    scanf(" %99[^\n]", &st);

    while(aux != NULL && strcmp(aux->nome, st) != 0)
        aux = aux->prox;

    if(aux != NULL){
        printf("\nQual o codigo da Paragem que deseja adicionar a Linha: ");
        scanf(" %99[^\n]", &cod);

        novo = malloc(sizeof(pParagemEmLinha));
        if(novo == NULL)
                return;

        for(i=0; i<(*n); ++i){
            if(strcmp(tab[i].codigo, cod) == 0){
                strcpy(novo->paragem.nome, tab[i].nome);
                strcpy(novo->paragem.codigo, tab[i].codigo);
                tab[i].nlinhas++;
                novo->paragem.nlinhas = tab[i].nlinhas;
                break;
            }
        }
        if(i==*n){
            printf("\nParagem requirida nao existe no sistema\n");
            return;
        }
        else{
            novo->prox = aux->lista; /*insere no inicio*/
            aux->lista = novo;
            aux->numeroParagens++;
        }
    }

    else
        printf("\nLinha requirida nao existe no sistema\n");
}


pLinha removeParagem(pLinha aux, paragens *tab, int *n){
    char st[TAMNOME];
    char cod[TAMCOD];
    int i;
    pLinha p = aux;

    printf("\nQue Linha deseja atualizar: ");
    scanf(" %99[^\n]", &st);

    while(p != NULL && strcmp(p->nome, st) != 0){
        p = p->prox;
    }

    if(p != NULL){
        printf("\nQual o codigo da Paragem que deseja remover da Linha %s: ", p->nome);
        scanf(" %99[^\n]", &cod);

        for(i=0; i<(*n); ++i){
            if(strcmp(tab[i].codigo, cod) == 0){
                tab[i].nlinhas--;
                break;
            }
        }
        if(i==*n){
            printf("\nParagem requirida nao existe no sistema\n");
            return p;
        }

        else{
            pParagemEmLinha atual = p->lista, anterior = NULL;

            while (atual != NULL) {
                if (strcmp(atual->paragem.codigo, cod) == 0) {
                    if (anterior == NULL) {
                        p->lista = atual->prox;
                    }
                    else{
                        anterior->prox = atual->prox;
                    }
                    free(atual);
                    p->numeroParagens--;
                    printf("\nRetirei paragem\n");
                    return aux;
                }

                anterior = atual;
                atual = atual->prox;
            }
        }
    }

    else
        printf("\nLinha requirida nao existe no sistema\n");

    return aux;
}


int guardaDadosLinhas(pLinha p){
    pParagemEmLinha aux;

    FILE *f;
    f = fopen("dadosLinhas.dat", "wb");
    if(f==NULL)
        return -1;

    while(p != NULL){
        aux = p->lista;
        fwrite(p, sizeof(linha), 1, f);

        while(aux != NULL){
            fwrite(aux, sizeof(paragemEmLinha), 1, f);
            aux = aux->prox;
        }
        p = p->prox;
    }

    fclose(f);
    return 1;
}


pLinha leDadosLinhas(){
    pLinha novo, p=NULL;
    pParagemEmLinha n;
    linha lin;
    paragemEmLinha par;
    int count=0, flag = 0;

    FILE *f;

    f = fopen("dadosLinhas.dat", "rb");
    if(f == NULL)
        return NULL;

    while(fread(&lin, sizeof(linha), 1, f) == 1){
        novo = malloc(sizeof(linha));
        if(novo == NULL){
            fclose(f);
            return p;
        }

        *novo = lin;
        novo->prox = NULL;
        novo->lista = NULL;

        if(p == NULL)
            p = novo;

        else{
            pLinha ultimaLinha = p;
            while(ultimaLinha->prox != NULL){
                ultimaLinha = ultimaLinha->prox;
            }
            ultimaLinha->prox = novo;
        }

        count=0;
        pLinha aux = p;

        while((count < novo->numeroParagens) && (fread(&par, sizeof(paragemEmLinha), 1, f) == 1)){
            count++;
            n = malloc(sizeof(paragemEmLinha));
            if(n == NULL){
                break;
            }

            *n = par;
            n->prox = NULL;

            if(aux->lista == NULL)
                aux->lista = n;

            else{
                pParagemEmLinha ultimaPar = aux->lista;
                while(ultimaPar->prox != NULL){
                    ultimaPar = ultimaPar->prox;
                }
                ultimaPar->prox = n;
            }
        }
        aux = aux->prox;
    }

    fclose(f);
    visualizaLinhas(p, NULL);
    return p;
}


void calculaPercurso(pLinha p, paragens *tab, int *n){
    char codi[TAMCOD];
    char codf[TAMCOD];
    pParagemEmLinha aux;
    pLinha init = p;
    int flagi=0, flagf=0, i;

    if(p == NULL){
        printf("\nNao existem Linhas registadas no sistema\n");
        return;
    }

    printf("\nCodigo da Paragem inicial: ");
    scanf(" %99[^\n]", &codi);

    for(i=0; i<(*n); ++i){
        if(strcmp(tab[i].codigo, codi) == 0){
            break;
        }
    }
    if(i==*n){
        printf("\nParagem requirida nao existe no sistema\n");
        return;
    }

    printf("\nCodigo da Paragem final: ");
    scanf(" %99[^\n]", &codf);

    for(i=0; i<(*n); ++i){
        if(strcmp(tab[i].codigo, codf) == 0){
            break;
        }
    }
    if(i==*n){
        printf("\nParagem requirida nao existe no sistema\n");
        return;
    }

    while(p != NULL){
        if(p->numeroParagens != 0){
            aux = p->lista;
            while(aux != NULL){
                if(strcmp(aux->paragem.codigo, codi) == 0){
                    flagi = 1;
                }
                if((strcmp(aux->paragem.codigo, codi) == 0) && (flagi == 1)){
                    flagf = 1;
                }
                aux = aux->prox;
            }
        }
        flagi=0;
        flagf=0;
        p = p->prox;
    }

    if(flagf == 1){
        p = init;
        while(p != NULL){
            aux = p->lista;
            do{
                if(strcmp(aux->paragem.codigo, codi) == 0){
                    while(aux != NULL){
                        printf("Paragem:\n\tNome: %s\n\tCodigo: %s\n", aux->paragem.nome, aux->paragem.codigo);
                        aux = aux->prox;
                    }
                }
            }while(aux != NULL);

            p = p->prox;
        }
    }
}
