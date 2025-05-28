//Pedro Miguel Dinis Sequeira - 2020132079

#include "Paragens.h"
#include "Linhas.h"

int menu(){
    int n;
    printf("\nQue informacao pretende acessar: ");
    printf("\n1 - Linhas");
    printf("\n2 - Paragens");
    printf("\n3 - Calculo de percursos");
    printf("\n4 - Sair");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}

int menuSavedFile(){
    int n;
    printf("\n1 - Sim");
    printf("\n2 - Nao");
    printf("\nOPCAO: ");
    scanf("%d", &n);
    printf("\n");
    return n;
}


int main(){
    int m, mSF, mP, mL;

    paragens *arrayParagens = NULL; //Cria o array dinâmico das paragens
    int total = 0; //numero de paragens armazenadas

    arrayParagens = malloc(sizeof(paragens));
    if (arrayParagens == NULL){
        printf("\nErro na alocacao de memoria para o array dinamico de paragens!\n");
        return 0;
    }

    pLinha listaLinhas = NULL;

    FILE *fp, *fl;
    fp = fopen("savedFile.dat", "rb");
    fl = fopen("dadosLinhas.dat", "rb");
    if(fp!=NULL){
        do{
            printf("\nExiste um ficheiro com dados de Paragens, deseja carrega-lo para o sistema? ");
            mSF = menuSavedFile();
            switch(mSF){
            case 1:
                arrayParagens = leDadosParagens(&total);
                if(fl!=NULL){
                    do{
                        printf("\nExiste um ficheiro com dados de Linhas, deseja carrega-lo para o sistema? ");
                        mSF = menuSavedFile();
                        switch(mSF){
                            case 1:
                                listaLinhas = leDadosLinhas();
                                break;
                            case 2:
                                break;
                            default:
                                printf("Por favor introduza uma opcao valida!\n");
                                break;
                        }
                    }while(mSF!=1 && mSF!=2);
                }
                break;
            case 2:
                break;
            default:
                printf("Por favor introduza uma opcao valida!\n");
                break;
            }
        }while(mSF!=1 && mSF!=2);
        fclose(fp);
        fclose(fl);
    }

    do{
        m = menu();
        switch(m){
            case 1:
                mL = menuLinhas();
                listaLinhas = trataLinhas(mL, listaLinhas, arrayParagens, &total);
                break;
            case 2:
                mP = menuParagens();
                arrayParagens = trataParagens(mP, arrayParagens, &total);
                break;
            case 3:
                calculaPercurso(listaLinhas, arrayParagens, &total);
                break;
            case 4:
                if(guardaDadosParagem(arrayParagens, total)!=1)
                    printf("\nErro no acesso ao ficheiro para escrita de Paragens\n");
                if(guardaDadosLinhas(listaLinhas)!=1)
                    printf("Erro no acesso ao ficheiro para escrita de Linhas");
                break;
            default:
                printf("Por favor introduza uma opcao valida!\n");
                break;
        }
    }while(m!=4);

    if(arrayParagens != NULL){
        free(arrayParagens);
        printf("Libertei o array dinamico de paragens\n");
    }

    if(listaLinhas != NULL){
        while (listaLinhas != NULL) {
            pLinha tempL = listaLinhas;
            while (listaLinhas->lista != NULL) {
                pParagemEmLinha tempP = listaLinhas->lista;
                listaLinhas->lista = listaLinhas->lista->prox;
                free(tempP);
            }
            listaLinhas = listaLinhas->prox;
            free(tempL);
        }
        printf("Libertei a lista de Linhas\n");
    }
    return 0;
}
