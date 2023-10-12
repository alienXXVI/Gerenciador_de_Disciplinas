#include <stdio.h>
#include "sistema.h"

int main() {
    Disciplina *d = criar_disciplina(1, "Matematica", 10, 1);
    Disciplina *d2 = criar_disciplina(2, "Ciencia", 11, 1);
    FILE *arq_disciplinas = fopen("disciplinas.bin", "w+b");

    criar_cabecalho_vazio(arq_disciplinas);
    inserir_disciplina(arq_disciplinas, d);
    inserir_disciplina(arq_disciplinas, d2);
    imprimir_disciplinas(arq_disciplinas);
    fclose(arq_disciplinas);

    return 0;
}