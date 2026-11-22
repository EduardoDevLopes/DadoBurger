#include "carga.h"
#include "timer.hpp"
#include <fstream>
#include <stdexcept>
#include "constants.h"

using namespace std;

// CARGA NA AVL
bool carregarPedidos(const string& arquivo, NoAVL*& raiz, EstatAVL& est) {
    ifstream arq(arquivo);
    if (!arq) return false;

    Timer cronometro;
    timer_iniciar(&cronometro);

    string linhaId, linhaReceita;

    while (getline(arq, linhaId)) {

        if (!linhaId.empty() && linhaId.back() == '\r') linhaId.pop_back();
        if (linhaId.empty()) continue;

        try {
            
            if (!getline(arq, linhaReceita)) {
                throw runtime_error("Arquivo de pedidos incompleto: esperava a linha da receita.");
            }

            if (!linhaReceita.empty() && linhaReceita.back() == '\r') linhaReceita.pop_back();

            if (linhaReceita.empty()) {
                throw runtime_error("Arquivo de pedidos incompleto: linha da receita está vazia.");
            }

            Pedido p;
            p.id = stoi(linhaId);
            p.receita = nullptr;

            for (char ing : linhaReceita) {
                inserirIngredienteFim(p.receita, ing);
            }

            raiz = inserirAVL(raiz, p, est.rotacoes);
        }
        catch (const exception&) {
            return false;
        }
    }
    est.tempoCarga = timer_parar(&cronometro);
    est.nos = contarNosAVL(raiz);   // O(1): campo tam da raiz (duplicados não entram)
    est.altura = alturaAVL(raiz);
    return true;
}
