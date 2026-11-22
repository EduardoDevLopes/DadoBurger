#include "historico.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

void inicializarLista(ListaContigua& l) { l.v = nullptr; l.tam = 0; l.cap = 0; }

void acrescentar(ListaContigua& l, const Entrada& e) {
    if (l.tam == l.cap) {
        int nc = l.cap == 0 ? 1024 : l.cap * 2;
        Entrada* nv = new Entrada[nc];
        if (l.tam > 0) memcpy(nv, l.v, sizeof(Entrada) * l.tam);
        delete[] l.v;
        l.v = nv; l.cap = nc;
    }
    l.v[l.tam++] = e;
}

void destruirLista(ListaContigua& l) { delete[] l.v; inicializarLista(l); }

Entrada* copiarVetor(const ListaContigua& l) {
    Entrada* c = new Entrada[l.tam > 0 ? l.tam : 1];
    if (l.tam > 0) memcpy(c, l.v, sizeof(Entrada) * l.tam);
    return c;
}

static void cortarFim(char* s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) s[--n] = '\0';
}

int carregarHistorico(const char* arquivo, ListaContigua& l) {
    FILE* f = fopen(arquivo, "r");
    if (!f) return 0;
    char nome[256], pts[256];
    int lidos = 0;
    while (fgets(nome, sizeof nome, f) && fgets(pts, sizeof pts, f)) {
        cortarFim(nome);
        Entrada e;
        strncpy(e.nome, nome, 20);
        e.nome[20] = '\0';
        e.pontos = atoi(pts);
        acrescentar(l, e);
        lidos++;
    }
    fclose(f);
    return lidos;
}

bool anexarHistorico(const char* arquivo, const Entrada& e) {
    /* garante que o arquivo termine com '\n' antes de anexar */
    bool precisaQuebra = false;
    FILE* r = fopen(arquivo, "rb");
    if (r) {
        if (fseek(r, -1, SEEK_END) == 0) precisaQuebra = (fgetc(r) != '\n');
        fclose(r);
    }
    FILE* f = fopen(arquivo, "a");
    if (!f) return false;
    if (precisaQuebra) fputc('\n', f);
    fprintf(f, "%s\n%d\n", e.nome, e.pontos);
    fclose(f);
    return true;
}
