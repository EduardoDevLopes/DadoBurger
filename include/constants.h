#ifndef CONSTANTS_H
#define CONSTANTS_H

// Estados principais do jogo para navegação entre telas
// (máquina de estados controlada em main.cpp)
enum EstadoJogo {
    ESTADO_MENU,        // Menu inicial com opções
    ESTADO_JOGANDO,     // Partida em andamento
    ESTADO_HISTORICO,   // Tela de histórico de partidas (ordenado)
    ESTADO_SAIR         // Encerrar aplicação
};

// ARQUIVOS E FORMATO DE DADOS
// Caminho padrão do arquivo de pedidos (pode ser sobrescrito por argv[1])
constexpr const char* ARQUIVO_PEDIDOS = "pedidos/pedidos.txt";
// Formato assumido de cada linha: id;nome;ing1,ing2,ing3
constexpr char SEPARADOR_CAMPO = ';';
constexpr char SEPARADOR_INGREDIENTE = ',';

// TABELA HASH (cache de pedidos)
// m primo, evita colisões sistemáticas do método da divisão
constexpr int TAMANHO_HASH = 211;
// Máximo de pedidos mantidos no cache antes de evictar
constexpr int CAPACIDADE_CACHE = 150;

// PARÂMETROS DA SIMULAÇÃO (ajustar e justificar no relatório)
constexpr int PACIENCIA_INICIAL = 10;   // turnos que um cliente espera
constexpr int VALIDADE_PADRAO = 8;      // turnos de validade de um lote perecível

// INTERFACE
constexpr int HISTORICO_EXIBIDO = 10;   // linhas mostradas na tela de histórico

#endif
