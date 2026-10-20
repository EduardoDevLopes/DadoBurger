#ifndef CARGA_H
#define CARGA_H
#include <string>
#include "avl.h"
#include "pedido.h"

// CARGA DO ARQUIVO pedidos.txt
// Formato assumido (1 pedido por linha): id;nome;ing1,ing2,ing3
// Linhas vazias ou iniciadas por '#' são ignoradas.
// Se o formato real for outro, só parsearLinhaPedido() precisa mudar.

// Converte uma linha em Pedido (receita alocada com new). Retorna false se inválida
bool parsearLinhaPedido(const std::string& linha, Pedido& p);

// Lê o arquivo inteiro e insere cada pedido na AVL, preenchendo as métricas de carga
// (nós, altura, rotações e tempo). Retorna false se o arquivo não abrir
bool carregarPedidos(const std::string& arquivo, NoAVL*& raiz, EstatAVL& est);

#endif
