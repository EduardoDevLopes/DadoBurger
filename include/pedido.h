#ifndef PEDIDO_H
#define PEDIDO_H
#include <string>
#include <random>
#include "lista.h"

// Representa um pedido cadastrado em pedidos.txt
// Propriedade da memória: a AVL é dona da receita; o cache hash guarda cópias rasas
struct Pedido {
    int id;               // chave de busca (AVL e hash)
    std::string nome;     // nome do lanche
    NoIng* receita;       // lista encadeada de ingredientes
};

int sortearPedido(std::mt19937 &geradorAleatorio, int min, int max);
void imprimirPedido(const Pedido& p);

#endif
