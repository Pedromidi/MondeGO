MondeGO 
 
Organização do programa

![image](https://github.com/user-attachments/assets/196387d6-2fdf-4275-9d6b-efc0f3702f36)

As linhas estão guardadas numa lista de listas ligadas onde as paragens de cada linha
são armazenadas na lista ligada secundária.
As paragens são armazenadas num array dinâmico.

Organização dos ficheiros utilizados pelo programa

![image](https://github.com/user-attachments/assets/fedd6c0e-f680-4a30-9d6f-8857c862c96b)

main.c: ficheiro que trata da parte inicial do programa (menus), cria o array dinâmico
de paragens e a lista ligada de linhas, faz a ligação entre funções relacionadas com paragens e
linhas.

Paragens.c: contém funções essenciais ao funcionamento das paragens no programa,
tem acesso ao header file das paragens.

Paragens.h: contém a estrutura para guardar a informação relativa a paragens, a
guardar no array dinâmico criado na função main; a estrutura “paragens” contém o nome da
paragem, o seu código e o número de linhas a que pertence.

Linhas.c: contém funções essenciais ao funcionamento das linhas no programa, tem
acesso aos header files das linhas e paragens.

Linhas.h: contém as estruturas para a lista de lista ligadas; a estrutura da lista principal
“linha”, que contém o nome da linha, número de paragens na linha, um ponteiro para a lista
secundária e um ponteiro para o próximo elemento da lista principal. A estrutura
“paragemEmLinha” contém um elemento do tipo “paragens” e um ponteiro para o próximo
elemento da lista secundária.
