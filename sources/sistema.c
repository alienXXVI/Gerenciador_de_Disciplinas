#include "../headers/sistema.h"
#include <stdlib.h>

// ------------------------------- Arquivo -------------------------------

// Escreve no arquivo o cabeçalho contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: cabeçalho escrito no arquivo
void escrever_cabecalho(FILE *arq, Cabecalho *cab){
    fseek(arq, 0, SEEK_SET); // posiciona no início do arquivo
    fwrite(cab, sizeof(Cabecalho), 1, arq);
}

// Cria uma lista (cabeçalho) nova em arquivo, podendo ser de Curso, Disciplina,
// CadastroProfessor ou CadastroProfessorDisciplina
// Pré-condição: arquivo aberto para leitura/escrita
// Pós-condição: arquivo é inicializado com uma lista vazia
void criar_lista_vazia(FILE* arq){
    Cabecalho *cab = (Cabecalho*) malloc(sizeof(Cabecalho));

    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escrever_cabecalho(arq, cab);
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

// --------------------------- Sistema ---------------------------

// Verifica se o cabeçalho (a lista) é vazia
// Entrada: cabeçalho
// Saída: é vazia (1) ou não é vazia (0)
int vazia(Cabecalho *cab) {
    return cab->pos_cabeca == -1;
}

// Busca por uma disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
Disciplina* buscar_disciplina(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    Disciplina* d = (Disciplina*) malloc(sizeof(Disciplina));

    if(!vazia(cab->pos_cabeca)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * cab->pos_cabeca, SEEK_SET);
        fread(d, sizeof(Disciplina), 1, arq);
        while(d->codigo != codigo && d->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(Disciplina) * d->prox, arq);
            fread(d, sizeof(Disciplina), 1, arq);
        }
        if(d->codigo == codigo) {
            free(cab);
            return d;
        }
    }
    free(cab);
    free(d);
    return NULL;
}

// Busca por um curso através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessor* buscar_curso(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessor* cadastro = (CadastroProfessor*) malloc(sizeof(CadastroProfessor));

    if(!vazia(cab->pos_cabeca)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cab->pos_cabeca, SEEK_SET);
        fread(cadastro, sizeof(CadastroProfessor), 1, arq);
        while(cadastro->codigo != codigo && cadastro->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cadastro->prox, arq);
            fread(cadastro, sizeof(CadastroProfessor), 1, arq);
        }
        if(cadastro->codigo == codigo) {
            free(cab);
            return cadastro;
        }
    }
    free(cab);
    free(cadastro);
    return NULL;
}

// Busca por um cadastro de professor através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessor* buscar_cadastro_professor(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessor* cadastro = (CadastroProfessor*) malloc(sizeof(CadastroProfessor));

    if(!vazia(cab->pos_cabeca)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cab->pos_cabeca, SEEK_SET);
        fread(cadastro, sizeof(CadastroProfessor), 1, arq);
        while(cadastro->codigo != codigo && cadastro->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessor) * cadastro->prox, arq);
            fread(cadastro, sizeof(CadastroProfessor), 1, arq);
        }
        if(cadastro->codigo == codigo) {
            free(cab);
            return cadastro;
        }
    }
    free(cab);
    free(cadastro);
    return NULL;
}

// Busca por um cadastro de distribuição de disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessorDisciplina* buscar_cadastro_professor_disciplina(FILE* arq, int codigo) {
    Cabecalho *cab = ler_cabecalho(arq);
    CadastroProfessorDisciplina* cadastro = (CadastroProfessorDisciplina*) malloc(sizeof(CadastroProfessorDisciplina));

    if(!vazia(cab->pos_cabeca)) {
        fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cab->pos_cabeca, SEEK_SET);
        fread(cadastro, sizeof(CadastroProfessorDisciplina), 1, arq);
        while(cadastro->codigo != codigo && cadastro->prox != -1) {
            fseek(arq, sizeof(Cabecalho) + sizeof(CadastroProfessorDisciplina) * cadastro->prox, arq);
            fread(cadastro, sizeof(CadastroProfessorDisciplina), 1, arq);
        }
        if(cadastro->codigo == codigo) {
            free(cab);
            return cadastro;
        }
    }
    free(cab);
    free(cadastro);
    return NULL;
}