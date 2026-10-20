# Dado Burger

Trabalho prático final de **INF01203 - Estruturas de Dados** (UFRGS, 2026/2, Turma C).
Jogo de simulação de lanchonete em **C++17**, em dupla.

## Compilar e executar
```
make          # gera build/dadoburger (g++ -std=c++17 -Wall -Wextra)
make run      # executa com pedidos/pedidos.txt
make test     # testes de unidade de todas as estruturas
make leaks    # valgrind --leak-check=full
```
Outro arquivo de pedidos: `./build/dadoburger caminho/pedidos.txt`

## Estrutura do projeto
| Pasta / arquivo | Conteúdo |
|---|---|
| `include/` | Um `.h` por módulo, com comentário de cada função |
| `src/` | Um `.cpp` por módulo + `main.cpp` (apenas a máquina de estados) |
| `tests/` | Testes de unidade |
| `pedidos/` | Arquivos `pedidos.txt` (desenvolvimento e final) |
| `historico/` | Dados persistidos das partidas (futuro) |
| `relatorio/` | Relatório do trabalho (máx. 8 páginas) |
| `build/` | Objetos e executáveis (ignorado pelo Git) |

## Módulos
| Módulo | Estrutura | Papel no jogo |
|---|---|---|
| `lista` | Lista encadeada | Receita do pedido |
| `pilha` | Pilha | Chapa de montagem |
| `fila` | Fila | Balcão de clientes |
| `heap` | Heap mínimo | Validade dos lotes perecíveis |
| `avl` | Árvore AVL | Índice de pedidos |
| `tabela_hash` | Hash (encadeamento separado) | Cache de pedidos |
| `historico` | Heap Sort | Ordenação do histórico |
| `carga` | - | Leitura do `pedidos.txt` |
| `jogo` | - | Estado global e ciclo de vida |
| `menu` | - | Telas (console; depois raylib) |
| `constants.h` | - | Constantes e enum de estados |

## Convenções
- Constantes em `constants.h` (sem números mágicos no código).
- Funções por módulo seguem `inicializar / atualizar / desenhar`.
- Estado do jogo passado por referência (`Jogo&`), sem variáveis globais.
- A AVL é dona das receitas; o cache guarda cópias rasas. `encerrarJogo` destrói o cache antes da AVL.
- Git: feature branches; `main` só recebe código revisado.
