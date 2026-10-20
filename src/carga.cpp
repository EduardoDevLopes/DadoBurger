#include "carga.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include "constants.h"

using namespace std;

// PARSING DE UMA LINHA
bool parsearLinhaPedido(const string& linha, Pedido& p) {
    if (linha.empty() || linha[0] == '#') return false;

    stringstream ss(linha);
    string sId, nome, ings;
    if (!getline(ss, sId, SEPARADOR_CAMPO) || !getline(ss, nome, SEPARADOR_CAMPO) || !getline(ss, ings))
        return false;
    try { p.id = stoi(sId); } catch (...) { return false; }

    p.nome = nome;
    p.receita = nullptr;
    stringstream si(ings);
    string ing;
    while (getline(si, ing, SEPARADOR_INGREDIENTE)) {
        if (!ing.empty() && ing.back() == '\r') ing.pop_back();   // arquivos com CRLF
        if (!ing.empty()) inserirIngredienteFim(p.receita, ing);
    }
    return true;
}

// CARGA NA AVL
bool carregarPedidos(const string& arquivo, NoAVL*& raiz, EstatAVL& est) {
    ifstream arq(arquivo);
    if (!arq) return false;

    auto t0 = chrono::steady_clock::now();
    string linha;
    while (getline(arq, linha)) {
        Pedido p;
        if (parsearLinhaPedido(linha, p)) raiz = inserirAVL(raiz, p, est.rotacoes);
    }
    auto t1 = chrono::steady_clock::now();

    est.tempoCarga = chrono::duration<double>(t1 - t0).count();
    est.nos = contarNosAVL(raiz);
    est.altura = alturaAVL(raiz);
    return true;
}
