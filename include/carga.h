#ifndef CARGA_H
#define CARGA_H
#include <string>
#include "avl.h"
#include "pedido.h"

// CARGA DO ARQUIVO DE PEDIDOS
// Formato (2 linhas por pedido): 1ª linha = código inteiro único; 2ª = receita (5 a 7
// símbolos da Tabela 1, de baixo para cima, terminando em 'z'). Linhas vazias entre os
// pedidos são ignoradas. O tamanho do arquivo não é assumido.

// Lê o arquivo inteiro e insere cada pedido na AVL, preenchendo as métricas de carga
// (nós, altura, rotações e tempo). Retorna false se o arquivo não abrir ou estiver malformado
bool carregarPedidos(const std::string& arquivo, NoAVL*& raiz, EstatAVL& est);

#endif
