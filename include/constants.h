#ifndef CONSTANTS_H
#define CONSTANTS_H

// Estados principais do jogo para navegação entre telas
// (máquina de estados controlada em main.cpp)
enum EstadoJogo {
    ESTADO_MENU,        // Menu inicial com opções
    ESTADO_JOGANDO,     // Partida em andamento
    ESTADO_COMO_JOGAR,  // Tela estática com as regras
    ESTADO_HISTORICO,   // Tela de histórico de partidas (ordenado)
    ESTADO_SAIR         // Encerrar aplicação
};

// ARQUIVOS (os nomes de entrada vêm de argv[1] e argv[2]; nada é fixo)
constexpr const char* ARQUIVO_LOG = "medicoes.log";   // recriado a cada execução

// TABELA HASH (cache de pedidos, encadeamento separado)
// m primo, ~4x o número de pedidos esperados por sessão (~50): evita colisões sistemáticas
constexpr int TAMANHO_HASH = 211;
// Máximo de pedidos mantidos no cache antes de evictar
constexpr int CAPACIDADE_CACHE = 150;

// PARÂMETROS DA SIMULAÇÃO (justificados no relatório, §2)
constexpr int NUM_CLIENTES = 10;        // clientes por partida
constexpr int PACIENCIA_INICIAL = 18;   // turnos; o pior pedido exige 13 (7 adições + 6 preparos)
constexpr int VALIDADE_CARNE = 6;       // turnos de validade (vence em preparo + validade)
constexpr int VALIDADE_OVO   = 4;
constexpr int VALIDADE_BACON = 5;

// INTERFACE
constexpr int HISTORICO_EXIBIDO = 10;   // linhas mostradas na tela de histórico
constexpr int MAX_NOME = 20;            // tamanho máximo do nome do jogador

// INGREDIENTES (Tabela 1 do enunciado): símbolo de cada tipo especial
constexpr char ING_PAO_CIMA = 'z';

#endif
