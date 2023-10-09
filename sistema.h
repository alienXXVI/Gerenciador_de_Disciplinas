#ifndef SISTEMA
#define SISTEMA

#include <stdio.h>

// Estrutura de cabeçalho do arquivo
typedef struct {
    int pos_cabeca; // posição do início da lista
    int pos_topo; // 1a posição não usada no fim do arquivo
    int pos_livre; // posição de início da lista de nós livres
} Cabecalho;

// Estrutura para Disciplina
typedef struct {
    int codigo;
    char nome[50];
    int codcurso;
    int serie;
    int prox;
} Disciplina;

// Estrutura para Curso
typedef struct {
    int codigo;
    char nome[50];
    char area; // Exatas, Humanas, Biológicas
    int disciplinas;
    int prox;
} Curso;

// Estrutura para Cadastro de Professor
typedef struct {
    int codigo;
    char nome[50];
    int prox;
} CadastroProfessor;

// Estrutura para Cadastro de Professor-Disciplina
typedef struct {
    int codigo;
    int coddisciplina;
    int anoletivo;
    int codprofessor;
    int prox;
} CadastroProfessorDisciplina;

// ---------------------------- ARQUIVO ----------------------------

// Cria uma lista nova em arquivo
// Pr´e-condi¸c~ao: arquivo aberto para leitura/escrita
// P´os-condi¸c~ao: arquivo ´e inicializado com uma lista vazia
void cria_lista_vazia(FILE* arq);


#endif