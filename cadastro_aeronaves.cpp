#include <iostream>
#include <fstream>
#include <vector>
#include "include/aeronave.h"

using namespace std;

// Carrega aeronaves de arquivo CSV
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

// Salva todas aeronaves no CSV
void salvarAeronaves(const vector<Aeronave>& lista, const string& nomeArquivo) {
    ofstream arq(nomeArquivo);

    for (const Aeronave& a : lista) {
        arq << a.toCSV() << endl;
    }
}

// Cadastra nova aeronave via terminal
void cadastrarAeronave(vector<Aeronave>& lista) {
    string codigo, modelo;
    int capacidade;
    double velocidade, autonomia;

    cout << "=== Cadastro de Aeronave ===\n";
    cout << "Código: ";
    cin >> codigo;

    // Verifica código duplicado
    for (const auto& a : lista) {
        if (a.getCodigo() == codigo) {
            cout << "Erro: Código de aeronave já cadastrado!\n";
            return;
        }
    }

    cin.ignore(); // limpar buffer
    cout << "Modelo: ";
    getline(cin, modelo);
    cout << "Capacidade (pessoas): ";
    cin >> capacidade;
    cout << "Velocidade média (milhas/h): ";
    cin >> velocidade;
    cout << "Autonomia (milhas): ";
    cin >> autonomia;

    Aeronave nova(codigo, modelo, capacidade, velocidade, autonomia);
    lista.push_back(nova);

    cout << "Aeronave cadastrada com sucesso!\n";
}

void listarAeronaves(const vector<Aeronave>& lista) {
    cout << "\n=== Lista de Aeronaves ===\n";
    for (const auto& a : lista) {
        cout << "Código: " << a.getCodigo()
             << ", Modelo: " << a.getModelo()
             << ", Capacidade: " << a.getCapacidade()
             << ", Velocidade: " << a.getVelocidadeMedia()
             << ", Autonomia: " << a.getAutonomia() << " milhas\n";
    }
}

int main() {
    vector<Aeronave> aeronaves = carregarAeronaves("aeronaves.csv");
    int opcao;

    do {
        cout << "\n=== Menu Aeronaves ===\n";
        cout << "1. Cadastrar nova aeronave\n";
        cout << "2. Listar aeronaves\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarAeronave(aeronaves);
                salvarAeronaves(aeronaves, "aeronaves.csv");
                break;
            case 2:
                listarAeronaves(aeronaves);
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }

    } while (opcao != 0);

    return 0;
}
