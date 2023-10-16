#ifndef LOTES
#define LOTES

// OK
// Insere uma disciplina na lista (arquivo)
// Pré-condição: arq_disciplinas aberto para leitura
// Pós-condição: disciplina inserida no arquivo
void inserir_lote_disciplina(FILE *arq_disciplinas);

// OK
// Insere um curso na lista (arquivo)
// Pré-condição: arq_cursos aberto para leitura
// Pós-condição: curso inserido no arquivo
void inserir_lote_curso(FILE *arq_cursos);

// OK
// Insere um professor na lista (arquivo)
// Pré-condição: arq_professores aberto para leitura
// Pós-condição: professor inserido no arquivo
void inserir_lote_professor(FILE *arq_professores);

// OK
// Insere uma distribuição na lista (arquivo)
// Pré-condição: arq_professores_disciplinas aberto para leitura
// Pós-condição: distribuição inserida no arquivo
void inserir_lote_distribuicao(FILE *arq_professores_disciplinas, FILE *arq_cursos);

// Lê o arquivo inteiro dado pela string
// Pré-condições: string contendo o nome do arquivo.extensão e arquivos abertos de cada estrutura
// Pós-condições: nenhuma
void ler_arq_txt(char *str, FILE *arq_disciplinas, FILE *arq_cursos, FILE *arq_professores, FILE *arq_professores_disciplinas);

#endif