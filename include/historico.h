#ifndef HISTORICO_H
#define HISTORICO_H

// HISTÓRICO DE PARTIDAS - LISTA CONTÍGUA (vetor dinâmico próprio)
// ADAPTAÇÃO: o esqueleto usava std::vector<Partida> {id, pontuacao, tempo}. O enunciado
// pede lista contígua alocada dinamicamente (acesso O(1) por índice) e registros
// {nome, pontuação}; o vetor passou a ser próprio (dobra a capacidade).
struct Entrada {
    char nome[21];   // até 20 caracteres + '\0'
    int pontos;
};

struct ListaContigua {
    Entrada* v = nullptr;
    int tam = 0;
    int cap = 0;
};

void inicializarLista(ListaContigua& l);
void acrescentar(ListaContigua& l, const Entrada& e);   // O(1) amortizado
void destruirLista(ListaContigua& l);

// Cópia independente (para ordenar sem alterar o original). O(n)
Entrada* copiarVetor(const ListaContigua& l);

// Lê o histórico (2 linhas por registro: nome, pontuação). Arquivo inexistente => lista
// vazia. Retorna o número de entradas lidas
int carregarHistorico(const char* arquivo, ListaContigua& l);

// Acrescenta UMA entrada ao final do arquivo (as partidas anteriores são preservadas)
bool anexarHistorico(const char* arquivo, const Entrada& e);

#endif
