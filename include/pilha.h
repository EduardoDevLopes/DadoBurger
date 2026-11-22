#ifndef PILHA_H
#define PILHA_H
#include <string>
#include "lista.h"

// PILHA (LIFO) - chapa de montagem do hambúrguer
struct NoPilha {
    char ing;
    char ing;
    NoPilha* prox;
};

struct Pilha {
    NoPilha* topo = nullptr;
    int tam = 0;
};

// Empilha um ingrediente. Complexidade O(1)
void pushIngrediente(Pilha& p, const char& ing);
void pushIngrediente(Pilha& p, const char& ing);

// Desempilha o topo (correção de erro). Retorna false se estava vazia.
// Se 'removido' != nullptr, recebe o ingrediente retirado. O(1)
bool popIngrediente(Pilha& p, char* removido = nullptr);

// Ingrediente do topo, ou '\0' se vazia. O(1)
char topoIngrediente(const Pilha& p);

// Copia a pilha de baixo para cima em 'buf' (capacidade 'cap'), sem destruí-la. Devolve o
// número de elementos copiados. O(n). Usada para exibir o prato
int copiarPilha(const Pilha& p, char* buf, int cap);

// Libera todos os nós da pilha
void destruirPilha(Pilha& p);

// Valida se a pilha (base -> topo) coincide exatamente com a receita. O(n)
// Recebe const Pilha& porque copiar uma pilha encadeada por valor duplicaria ponteiros
bool verificarPedido(const Pilha& p, const NoIng* receita);

#endif
