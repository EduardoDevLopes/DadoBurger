#include "pedido.h"
#include <iostream>
#include <random>

using namespace std;

// sorteia inteiro uniforme em [min, max]
int sortearPedido(mt19937 &geradorAleatorio, int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(geradorAleatorio);
}

void imprimirPedido(const Pedido& pedido) {
    cout << "Pedido: id: " << pedido.id << ", receita: ";
    if (pedido.receita == nullptr) {
        cout << "(vazia)";
    } else {
        for (const NoIng* ingrediente = pedido.receita; ingrediente != nullptr; ingrediente = ingrediente->prox) {
            cout << ingrediente->simbolo;
            if (ingrediente->prox != nullptr) cout << ' ';
        }
    }
    cout << endl;
}
