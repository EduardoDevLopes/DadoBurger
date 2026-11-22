#ifndef FILA_H
#define FILA_H

// FILA (FIFO) - balcão de atendimento
struct Cliente {
    int id;           // ordem de chegada (1..N)
    int idPedido;     // chave do pedido na AVL (preenchida quando chega à frente)
    int paciencia;    // turnos restantes antes de desistir
};

struct NoFila {
    Cliente c;
    NoFila* prox;
};

struct Fila {
    NoFila* ini = nullptr;
    NoFila* fim = nullptr;
    int tam = 0;
};

// Adiciona cliente no final da fila. Complexidade O(1)
void enfileirarCliente(Fila& f, const Cliente& c);

// Atende e remove o cliente da frente. Retorna false se vazia. O(1)
bool desenfileirarCliente(Fila& f, Cliente& out);

// Cliente da frente (nullptr se vazia). O(1)
Cliente* frenteFila(Fila& f);

// Imprime os clientes da frente ao final sem alterar a fila. O(n)
void imprimirFila(const Fila& f);

// ADAPTAÇÃO: o esqueleto decrementava a paciência de TODOS os clientes; o enunciado
// (§3.3) diz que só o da frente perde paciência. Decrementa 1 turno do cliente da frente
// e devolve a paciência restante (-1 se a fila está vazia). O(1)
int reduzirPacienciaFrente(Fila& f);

// Libera todos os nós da fila
void destruirFila(Fila& f);

#endif
