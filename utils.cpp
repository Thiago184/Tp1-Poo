#include "include/utils.h"
#include <fstream>
#include <sstream>

// ---- Aeronaves ----
vector<Aeronave> carregarAeronaves(const string& nomeArquivo) {
    vector<Aeronave> lista;
    ifstream arq(nomeArquivo);
    string linha;

    while (getline(arq, linha)) {
        if (!linha.empty())
            lista.push_back(Aeronave::fromCSV(linha));
    }

    return lista;
}

void salvarAeronaves(const vector<Aeronave>& lista, const string& nomeArquivo) {
    ofstream arq(nomeArquivo);
    for (const auto& a : lista) {
        arq << a.toCSV() << endl;
    }
}

// ---- Pessoas ----
vector<shared_ptr<Pessoa>> carregarPessoas(const string& nomeArquivo) {
    vector<shared_ptr<Pessoa>> lista;
    ifstream arq(nomeArquivo);
    string linha;

    while (getline(arq, linha)) {
        if (linha.find("PILOTO") == 0) {
            lista.push_back(make_shared<Piloto>(Piloto::fromCSV(linha)));
        } else if (linha.find("PASSAGEIRO") == 0) {
            lista.push_back(make_shared<Passageiro>(Passageiro::fromCSV(linha)));
        }
    }

    return lista;
}

void salvarPessoas(const vector<shared_ptr<Pessoa>>& lista, const string& nomeArquivo) {
    ofstream arq(nomeArquivo);
    for (const auto& pessoa : lista) {
        arq << pessoa->toCSV() << endl;
    }
}
