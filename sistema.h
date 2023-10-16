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

// OK
// Cria uma lista nova em arquivo, podendo ser de Curso, Disciplina,
// CadastroProfessor ou CadastroProfessorDisciplina
// Pré-condição: arquivo aberto para leitura/escrita
// Pós-condição: arquivo é inicializado com uma lista vazia
void criar_cabecalho_vazio(FILE* arq);

// OK
// Lê o cabeçalho do arquivo contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: retorna o ponteiro para o cabeçalho lido
Cabecalho* ler_cabecalho(FILE *arq);

// OK
// Escreve no arquivo o cabeçalho contendo as informações da lista
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: cabeçalho escrito no arquivo
void escrever_cabecalho(FILE *arq, Cabecalho *cab);


// --------------------------- Sistema ---------------------------

// OK
// Verifica se o cabeçalho (a lista) é vazia
// Entrada: cabeçalho
// Saída: é vazia (1) ou não é vazia (0)
int vazia(Cabecalho *cab);

// OK
// Cria uma Disciplina contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente para o mesmo curso
// Pós-condição: retorna ponteiro para Disciplina
Disciplina* criar_disciplina(int codigo, char *nome, int codcurso, int serie);

// OK
// Cria um Curso contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente de outro curso,
//      area deve ser 'E' (Exatas), 'H' (Humanas) ou 'B' (Biológicas)
// Pós-condição: retorna ponteiro para Curso
Curso* criar_curso(int codigo, char *nome, char area);

// OK
// Cria um CadastroProfessor contendo os dados fornecidos
// Pré-condição: o código fornecido deve ser diferente de outro professor
// Pós-condição: retorna ponteiro para CadastroProfessor
CadastroProfessor* criar_cadastro_professor(int codigo, char *nome);

// OK
// Cria um CadastroProfessorDisciplina contendo os dados fornecidos
// Pré-condição: os códigos fornecidos devem ser válidos
// Pós-condição: retorna ponteiro para CadastroProfessorDisciplina
CadastroProfessorDisciplina* criar_cadastro_professor_disciplina(int codigo, int coddisciplina, int anoletivo, int codprofessor);

// OK
// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_disciplina(FILE *arq, Disciplina *d);

// OK
// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_curso(FILE *arq, Curso *c);

// OK
// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_cadastro_professor(FILE *arq, CadastroProfessor *cp);

// OK
// Insere o nó na lista do arquivo
// Pré-condição: arquivo deve estar aberto para escrita
// Pós-condição: arquivo com novo nó
void inserir_cadastro_professor_disciplina(FILE *arq, CadastroProfessorDisciplina *cpd);

// OK
// Busca por uma disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
Disciplina* buscar_disciplina(FILE* arq, int codigo);

// OK
// Busca por um curso através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
Curso* buscar_curso(FILE* arq, int codigo);

// OK
// Busca por um cadastro de professor através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessor* buscar_cadastro_professor(FILE* arq, int codigo);

// OK
// Busca por um cadastro de distribuição de disciplina através do seu código
// Pré-condição: arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: ponteiro para nó lido é retornado
CadastroProfessorDisciplina* buscar_cadastro_professor_disciplina(FILE* arq, int codigo);

// OK
// Imprime a lista de disciplinas
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_disciplinas(FILE *arq);

// OK
// Imprime a lista de cursos
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_cursos(FILE *arq);

// OK
// Imprime a lista de cadastro de professores
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_cadastros_professor(FILE *arq);

// OK
// Imprime a lista de cadastros de distribuições de disciplina
// Pré-condição: arquivo aberto para leitura
// Pós-condição: nenhuma
void imprimir_cadastros_professor_disciplina(FILE *arq);

// Imprime a lista de distribuição de disciplinas organizada por cursos
// Pré-condição: arquivos de distribuição de disciplinas e de cursos abertos para leitura
// Pós-condição: nenhuma
void imprimir_distribuicao_ordenada(FILE *arq_professores_disciplinas, FILE *arq_cursos);


#endif