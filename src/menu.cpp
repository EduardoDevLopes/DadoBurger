#include "menu.h"
#include "metricas.h"
#include "ordenacao.h"
#include "partida.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

// Lê uma linha da entrada padrão (sem '\n'); false em EOF.
// Toda a leitura usa getline para não misturar com cin >> (que deixa '\n' no buffer)
static bool lerLinha(char* buf, int n) {
    string s;
    if (!getline(cin, s)) return false;
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
    strncpy(buf, s.c_str(), (size_t)n - 1);
    buf[n - 1] = '\0';
    return true;
}

// MENU
void desenharMenu() {
    cout << "\n=== DADO BURGER ===\n"
         << "1. Novo jogo\n"
         << "2. Como jogar\n"
         << "3. Historico\n"
         << "4. Sair\n"
         << "Escolha: " << flush;
}

void atualizarMenu(EstadoJogo& estadoAtual) {
    char b[64];
    if (!lerLinha(b, sizeof b)) { estadoAtual = ESTADO_SAIR; return; }   // entrada encerrada
    switch (atoi(b)) {
        case 1: estadoAtual = ESTADO_JOGANDO;    break;
        case 2: estadoAtual = ESTADO_COMO_JOGAR; break;
        case 3: estadoAtual = ESTADO_HISTORICO;  break;
        case 4: estadoAtual = ESTADO_SAIR;       break;
        default: cout << "Opcao invalida.\n";    break;
    }
}

// COMO JOGAR
void desenharComoJogar() {
    printf("\n=== COMO JOGAR ===\n");
    printf("Voce e o mais novo funcionario do Dado Burger e atende uma fila de %d clientes.\n\n", NUM_CLIENTES);
    printf("Objetivo: montar, de baixo para cima, o hamburguer do cliente da frente da fila.\n\n");
    printf("O pao de baixo ja esta no prato. Fechar com o pao de cima (z) entrega o pedido se ele conferir.\n\n");
    printf("Ingredientes (simbolo):\n");
    printf("  Sem preparo (infinitos):\npao de cima = z | ketchup = k | mostarda = m | picles = p | alface = a\n");
    printf("  Preparo (nao perecivel):\nqueijo suico = s | queijo cheddar = q | cebola = c | tomate = t\n");
    printf("  Preparo (perecivel):\ncarne n (%d turnos) | ovo frito o (%d) | bacon b (%d)\n", VALIDADE_CARNE, VALIDADE_OVO, VALIDADE_BACON);
    printf("  (perecivel preparado no turno T vence no turno T + validade; vencidos sao descartados)\n\n");
    printf("Acoes (cada uma consome 1 turno):\n");
    printf("  (p 'X')  preparar o ingrediente X (so os que exigem preparo)\n");
    printf("  (a 'X')  adicionar o ingrediente X ao hamburguer (empilha)\n");
    printf("  (r)      remover o ingrediente do topo (e descartado)\n\n");
    printf("Consultas (nao consomem turno): \ne = estoque detalhado, \no = pedido, \n? = ajuda");
    printf("  \ns = desistir da partida\n\n");
    printf("Paciencia:cada cliente aguarda %d turnos, mas so a do cliente da frente diminui.\n", PACIENCIA_INICIAL);
    printf("Derrota : a paciencia do cliente da frente chega a zero (pontuacao = clientes atendidos).\n");
    printf("Vitoria : todos os clientes atendidos (pontuacao = %d).\n", NUM_CLIENTES);
    printf("\nPressione ENTER para voltar..."); fflush(stdout);
    char b[16]; lerLinha(b, sizeof b);
}

// PARTIDA
static void imprimirReceita(const NoIng* r) {
    for (const NoIng* a = r; a != nullptr; a = a->prox)
        printf("%s%c(%s)", a == r ? "" : " > ", a->simbolo, nomeIngrediente(a->simbolo) ? nomeIngrediente(a->simbolo) : "?");
    printf("\n");
}

static void imprimirEstoque(const Partida& p, bool detalhado) {
    printf("Estoque:\nqueijo suico(s)=%d \ncheddar(q)=%d \ncebola(c)=%d \ntomate(t)=%d \ncarne(n)=%d \novo(o)=%d \nbacon(b)=%d\n\n",
           p.estoque.perenes[0], p.estoque.perenes[1], p.estoque.perenes[2], p.estoque.perenes[3],
           p.estoque.heaps[0].tam, p.estoque.heaps[1].tam, p.estoque.heaps[2].tam);
    if (detalhado) {
        static const char* nm[3] = {"carne", "ovo frito", "bacon"};
        for (int i = 0; i < 3; i++) {
            const Heap& h = p.estoque.heaps[i];
            if (h.tam > 0) printf("  %s: %d un., a mais antiga vence no turno %d (turno atual %d)\n", nm[i], h.tam, h.v[0].turnoVencimento, p.turno);
            else printf("  %s: 0 un.\n", nm[i]);
        }
        printf("  Nao pereciveis infinitos: z k m p a\n");
    }
}

static void desenharTurno(Jogo& j) {
    Partida& p = j.partida;
    Cliente* c = frenteFila(p.balcao);
    printf("\n------------------------------------------------------------\n");
    printf("Turno %d | Cliente %d/%d | Atendidos: %d | Na fila: %d\n", p.turno, p.clienteAtual, NUM_CLIENTES, p.pontuacao, p.balcao.tam);
    printf("Paciencia do cliente: %d/%d\n", c->paciencia, PACIENCIA_INICIAL);
    printf("Pedido  (base > topo): "); imprimirReceita(p.pedido->receita);
    printf("Prato   (base > topo): [pao]");
    char buf[64]; int n = copiarPilha(p.chapa, buf, 64);
    for (int i = 0; i < n; i++) printf(" %c", buf[i]);
    printf("\n");
    imprimirEstoque(p, false);
    if (p.msg[0]) printf(">> %s\n", p.msg);
}

static void lerNome(char* nome) {
    printf("Seu nome (max %d caracteres): ", MAX_NOME); fflush(stdout);
    char b[256];
    if (!lerLinha(b, sizeof b)) b[0] = '\0';
    char* ini = b; while (*ini == ' ') ini++;
    size_t ln = strlen(ini); if (ln > (size_t)MAX_NOME) ln = MAX_NOME;
    memcpy(nome, ini, ln); nome[ln] = '\0';
    while (ln > 0 && nome[ln - 1] == ' ') nome[--ln] = '\0';
    if (nome[0] == '\0') strcpy(nome, "Anonimo");
}

void executarPartida(Jogo& j) {
    Entrada e;
    lerNome(e.nome);
    iniciarPartida(j);
    Partida& p = j.partida;
    printf("\nBom trabalho, %s! Digite ? para ver os comandos.\n", e.nome);

    while (p.estado == EM_ANDAMENTO) {
        desenharTurno(j);
        p.msg[0] = '\0';
        printf("> "); fflush(stdout);
        char b[128];
        if (!lerLinha(b, sizeof b)) { acaoSair(j); break; }
        char cmd = 0, arg = 0;
        sscanf(b, " %c %c", &cmd, &arg);
        switch (cmd) {
            case 'p': case 'P': if (!arg) snprintf(p.msg, sizeof p.msg, "Use: p <simbolo>. "); else acaoPreparar(j, arg); break;
            case 'a': case 'A': if (!arg) snprintf(p.msg, sizeof p.msg, "Use: a <simbolo>. "); else acaoAdicionar(j, arg); break;
            case 'r': case 'R': acaoRemoverTopo(j); break;
            case 'e': case 'E': printf("\n"); imprimirEstoque(p, true); snprintf(p.msg, sizeof p.msg, "(consulta: nao consumiu turno) "); break;
            case 'o': case 'O': printf("\nPedido: "); imprimirReceita(p.pedido->receita); snprintf(p.msg, sizeof p.msg, "(consulta: nao consumiu turno) "); break;
            case '?': case 'h': case 'H':
                snprintf(p.msg, sizeof p.msg, "p X preparar | a X adicionar | r remover topo | e estoque | o pedido | s sair. Simbolos: z k m p a s q c t n o b. "); break;
            case 's': case 'S': acaoSair(j); break;
            default: snprintf(p.msg, sizeof p.msg, "Comando desconhecido. Digite ? para ajuda. "); break;
        }
    }

    const char* motivo = p.estado == VITORIA ? "VITORIA" : p.estado == DERROTA ? "DERROTA" : "saida voluntaria";
    if (p.estado == VITORIA) printf("\n*** VITORIA! Todos os %d clientes foram atendidos. ***\n", p.pontuacao);
    else if (p.estado == DERROTA) printf("\n*** DERROTA: o cliente %d perdeu a paciencia. Atendidos: %d ***\n", p.clienteAtual, p.pontuacao);
    else printf("\nPartida encerrada. Atendidos: %d\n", p.pontuacao);

    e.pontos = p.pontuacao;
    if (!anexarHistorico(j.arqHistorico.c_str(), e)) printf("(aviso: nao foi possivel gravar em %s)\n", j.arqHistorico.c_str());
    acrescentar(j.historico, e);

    printf("\n");
    imprimirRelatorio(stdout, j);
    registrarRelatorioNoLog(j, motivo, p.pontuacao);
    reiniciarPartida(j);   // libera fila, prato e estoque
}

// HISTÓRICO
void desenharHistorico(Jogo& j) {
    printf("\n=== HISTORICO (%d partidas) ===\n1. Ordem alfabetica\n2. Pontuacao decrescente\n0. Voltar\nEscolha: ", j.historico.tam);
    fflush(stdout);
    char b[64];
    if (!lerLinha(b, sizeof b)) return;
    int o = atoi(b);
    if (o != 1 && o != 2) return;
    CriterioEntrada criterio = o == 1 ? ordemAlfabetica : maiorPontuacao;
    Entrada* ord = nullptr;
    double t = medirOrdenacao(j.historico, criterio, &ord);   // ordena COPIA: arquivo e lista intactos
    j.estatOrd.acessos++;
    j.estatOrd.tamanho = j.historico.tam;
    j.estatOrd.tempo = t;
    j.estatOrd.criterio = o == 1 ? "alfabetica" : "pontuacao decrescente";
    int lim = j.historico.tam < HISTORICO_EXIBIDO ? j.historico.tam : HISTORICO_EXIBIDO;
    printf("\n%-4s %-22s %s\n", "#", "Nome", "Pontos");
    for (int i = 0; i < lim; i++) printf("%-4d %-22s %d\n", i + 1, ord[i].nome, ord[i].pontos);
    if (j.historico.tam > lim) printf("... (exibindo %d de %d)\n", lim, j.historico.tam);
    printf("\nOrdenacao (Merge Sort, %s): %.6f s para %d entradas\n", j.estatOrd.criterio, t, j.historico.tam);
    delete[] ord;
    registrarOrdenacaoNoLog(j);
}
