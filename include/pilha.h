#ifndef PILHA_H
#define PILHA_H
#include <string>
#include "lista.h"

// PILHA (LIFO) - chapa de montagem do hambúrguer
struct NoPilha {
    std::string ing;
    NoPilha* prox;
};

struct Pilha {
    NoPilha* topo = nullptr;
    int tam = 0;
};

// Empilha um ingrediente. Complexidade O(1)
void pushIngrediente(Pilha& p, const std::string& ing);

// Desempilha o topo (correção de erro). Retorna false se estava vazia.
// Se 'removido' != nullptr, recebe o ingrediente retirado. O(1)
bool popIngrediente(Pilha& p, std::string* removido = nullptr);

// Libera todos os nós da pilha
void destruirPilha(Pilha& p);

// Valida se a pilha (base -> topo) coincide exatamente com a receita. O(n)
// Recebe const Pilha& porque copiar uma pilha encadeada por valor duplicaria ponteiros
bool verificarPedido(const Pilha& p, const NoIng* receita);

#endif
