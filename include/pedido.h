#ifndef PEDIDO_H
#define PEDIDO_H
#include <random>
#include "lista.h"

// Representa um pedido cadastrado em pedidos.txt (código + receita)
// Propriedade da memória: a AVL é dona da receita; o cache hash guarda cópias rasas
// (o campo 'nome' do esqueleto foi removido: o arquivo real não tem nome, e o campo
//  custaria ~27 MB com 837 mil pedidos)
struct Pedido {
    int id;               // chave de busca (AVL e hash)
    NoIng* receita;       // lista encadeada de ingredientes (base -> topo)
};

// Inteiro uniforme em [min, max]
int sortearPedido(std::mt19937 &geradorAleatorio, int min, int max);
void imprimirPedido(const Pedido& p);

#endif
