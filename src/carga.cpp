#include "carga.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include "constants.h"

using namespace std;

// CARGA NA AVL
bool carregarPedidos(const string& arquivo, NoAVL*& raiz, EstatAVL& est) {
    ifstream arq(arquivo);
    if (!arq) return false;

    auto t0 = chrono::steady_clock::now();

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
        catch (const exception& e) {
            return false;
        }
    }
    auto t1 = chrono::steady_clock::now();

    est.tempoCarga = chrono::duration<double>(t1 - t0).count();
    // TODO: contar nós (e talvez altura) da AVL durante a inserção dos nodos, para não precisar percorrer a árvore novamente
    est.nos = contarNosAVL(raiz);
    est.altura = alturaAVL(raiz);
    return true;
}
