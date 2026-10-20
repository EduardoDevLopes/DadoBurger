#ifndef LISTA_H
#define LISTA_H
#include <string>

// LISTA ENCADEADA - receita de um pedido
// Cada nó representa um ingrediente, na ordem de montagem (base -> topo)
struct NoIng {
    std::string nome;   // Nome do ingrediente
    NoIng* prox;        // Próximo ingrediente (nullptr no último)
};

// Insere um ingrediente no final da receita. Complexidade O(n)
void inserirIngredienteFim(NoIng*& ini, const std::string& nome);

// Percorre e libera todos os nós com delete; deixa ini = nullptr
void destruirLista(NoIng*& ini);

#endif
