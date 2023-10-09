#include "../headers/sistema.h"
#include <stdlib.h>

// Escreve no arquivo o cabeçalho contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: cabeçalho escrito no arquivo
void escrever_cabecalho(FILE *arq, Cabecalho *cab){
    fseek(arq, 0, SEEK_SET); // posiciona no início do arquivo
    fwrite(cab, sizeof(Cabecalho), 1, arq);
}

// Cria uma lista nova em arquivo, podendo ser de Curso, Disciplina,
// CadastroProfessor ou CadastroProfessorDisciplina
// Pré-condição: arquivo aberto para leitura/escrita
// Pós-condição: arquivo é inicializado com uma lista vazia
void criar_lista_vazia(FILE* arq){
    Cabecalho *cab = (Cabecalho*) malloc(sizeof(Cabecalho));

    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escreve_cabecalho(arq,cab);
    free(cab);
}

// Lê o cabeçalho do arquivo contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: retorna o ponteiro para o cabeçalho lido
Cabecalho* ler_cabecalho(FILE *arq) {
    Cabecalho *cab = (Cabecalho*) malloc(sizeof(Cabecalho));
    fseek(arq, 0, SEEK_SET); // posiciona no in´ıcio do arquivo
    fread(cab, sizeof(Cabecalho), 1, arq);
    return cab;
}

// Lê um  em uma determinada posi¸c~ao do arquivo
// Pr´e-condi¸c~ao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posi¸c~ao v´alida da lista
// P´os-condi¸c~ao: ponteiro para n´o lido ´e retornado
Disciplina* buscar_disciplina(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    Disciplina* d = (Disciplina*) malloc(sizeof(Disciplina));

    

    return d;
}

// l^e um n´o em uma determinada posi¸c~ao do arquivo
// Pr´e-condi¸c~ao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posi¸c~ao v´alida da lista
// P´os-condi¸c~ao: ponteiro para n´o lido ´e retornado
Curso* le_no(FILE* arq, int pos) {
    no* x = malloc(sizeof(no));
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no),SEEK_SET);
    fread(x,sizeof(no),1,arq);
    return x;
}

CadastroProfessor* le_no(FILE* arq, int pos) {
    no* x = malloc(sizeof(no));
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no),SEEK_SET);
    fread(x,sizeof(no),1,arq);
    return x;
}

CadastroProfessorDisciplina* le_no(FILE* arq, int pos) {
    no* x = malloc(sizeof(no));
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no),SEEK_SET);
    fread(x,sizeof(no),1,arq);
    return x;
}