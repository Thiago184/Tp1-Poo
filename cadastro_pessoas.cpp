#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "include/pessoa.h"

using namespace std;

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

void Piloto::cadastrarPiloto(vector<shared_ptr<Pessoa>>& lista) {
    string nome, matricula, breve;
    double horas;

    cout << "Nome: ";
    getline(cin, nome);
    cout << "Matrícula: ";
    getline(cin, matricula);
    cout << "Breve: ";
    getline(cin, breve);
    cout << "Horas de voo: ";
    cin >> horas;

    lista.push_back(make_shared<Piloto>(nome, matricula, breve, horas));
    cout << "Piloto cadastrado com sucesso!\n";
}

void Passageiro::cadastrarPassageiro(vector<shared_ptr<Pessoa>>& lista) {
    string nome, cpf, bilhete;

    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << "CPF: ";
    getline(cin, cpf);
    cout << "Bilhete: ";
    getline(cin, bilhete);

    lista.push_back(make_shared<Passageiro>(nome, cpf, bilhete));
    cout << "Passageiro cadastrado com sucesso!\n";
}

void listarPessoas(const vector<shared_ptr<Pessoa>>& lista) {
    cout << "\n=== Lista de Pessoas ===\n";
    for (const auto& p : lista) {
        if (auto piloto = dynamic_pointer_cast<Piloto>(p)) {
            cout << "[PILOTO] " << piloto->getNome()
                 << " | Matrícula: " << piloto->getMatricula()
                 << " | Breve: " << piloto->getBreve()
                 << " | Horas: " << piloto->getHorasVoo() << endl;
        } else if (auto passageiro = dynamic_pointer_cast<Passageiro>(p)) {
            cout << "[PASSAGEIRO] " << passageiro->getNome()
                 << " | CPF: " << passageiro->getCPF()
                 << " | Bilhete: " << passageiro->getBilhete() << endl;
        }
    }
}

// int main() {
//     vector<shared_ptr<Pessoa>> pessoas = carregarPessoas("pessoas.csv");
//     int opcao;

//     do {
//         cout << "\n=== Menu Pessoas ===\n";
//         cout << "1. Cadastrar Piloto\n";
//         cout << "2. Cadastrar Passageiro\n";
//         cout << "3. Listar Pessoas\n";
//         cout << "0. Sair\n";
//         cout << "Escolha: ";
//         cin >> opcao;

//         switch (opcao) {
//             case 1:
//                 cadastrarPiloto(pessoas);
//                 salvarPessoas(pessoas, "pessoas.csv");
//                 break;
//             case 2:
//                 cadastrarPassageiro(pessoas);
//                 salvarPessoas(pessoas, "pessoas.csv");
//                 break;
//             case 3:
//                 listarPessoas(pessoas);
//                 break;
//             case 0:
//                 cout << "Encerrando...\n";
//                 break;
//             default:
//                 cout << "Opção inválida.\n";
//         }

//     } while (opcao != 0);

//     return 0;
// }
