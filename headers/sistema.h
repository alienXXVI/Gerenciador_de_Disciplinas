#ifndef SISTEMA
#define SISTEMA

#include <stdio.h>

// Estrutura de cabeçalho do arquivo
typedef struct {
    int pos_cabeca; // posição do início da lista
    int pos_topo; // 1a posição não usada no fim do arquivo
    int pos_livre; // posição de início da lista de nós livres
} Cabecalho;

// Estrutura de cabeçalho para disciplina do arquivo
typedef struct {
    int pos_cabeca; // posição do início da lista
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
    int disciplinas; // posição de ínicio da lista de disciplinas
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

// Escreve no arquivo o cabeçalho contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: cabeçalho escrito no arquivo
void escrever_cabecalho(FILE *arq, Cabecalho *cab);

// Cria uma lista nova em arquivo, podendo ser de Curso, Disciplina,
// CadastroProfessor ou CadastroProfessorDisciplina
// Pré-condição: arquivo aberto para leitura/escrita
// Pós-condição: arquivo é inicializado com uma lista vazia
void criar_cabecalho_vazio(FILE* arq);

// Lê o cabeçalho do arquivo contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: retorna o ponteiro para o cabeçalho lido
Cabecalho* ler_cabecalho(FILE *arq);


// --------------------------- Sistema ---------------------------

// Verifica se o cabeçalho (a lista) é vazia
// Entrada: cabeçalho
// Saída: é vazia (1) ou não é vazia (0)
int vazia(Cabecalho *cab);

// Cria uma Disciplina contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente para o mesmo curso
// Pós-condição: retorna ponteiro para Disciplina
Disciplina* criar_disciplina(int codigo, char nome, int codcurso, int serie);

// Cria um Curso contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente de outro curso,
//      area deve ser 'E' (Exatas), 'H' (Humanas) ou 'B' (Biológicas)
// Pós-condição: retorna ponteiro para Curso
Curso* criar_curso(int codigo, char nome, char area);

// Cria um CadastroProfessor contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente de outro professor
// Pós-condição: retorna ponteiro para CadastroProfessor
CadastroProfessor* criar_cadastro_professor(int codigo, char nome);

// Cria um CadastroProfessorDisciplina contendo os dados fornecidos
// Pré-condição: os códigos fornecidos devem ser válidos
// Pós-condição: retorna ponteiro para CadastroProfessorDisciplina
CadastroProfessorDisciplina* criar_cadastro_professor_disciplina(int coddisciplina, int anoletivo, int codprofessor);

// Busca por uma disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
Disciplina* buscar_disciplina(FILE* arq, int codigo);

// Busca por um curso através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessor* buscar_curso(FILE* arq, int codigo);

// Busca por um cadastro de professor através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessor* buscar_cadastro_professor(FILE* arq, int codigo);

// Busca por um cadastro de distribuição de disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessorDisciplina* buscar_cadastro_professor_disciplina(FILE* arq, int codigo);


#endif