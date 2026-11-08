#include "pedido.h"
#include "tabela_hash.h"
#include <iostream>
#include <random>
//#include <format>
using namespace std;

// sorteia pedido
int sortearPedido(mt19937 &geradorAleatorio, int min, int max) {

    uniform_int_distribution<int> dist(min, max);

    return dist(geradorAleatorio);
}


void imprimirPedido(const Pedido& pedido) {
    cout << "Pedido sorteado: id: " << pedido.id << ", receita: ";

    if (pedido.receita == nullptr) {
        cout << "(vazia)";
    } else {
        for (const NoIng* ingrediente = pedido.receita;
             ingrediente != nullptr;
             ingrediente = ingrediente->prox) {
            cout << ingrediente->simbolo;
            if (ingrediente->prox != nullptr) cout << ' ';
        }
    }

    cout << endl;
}