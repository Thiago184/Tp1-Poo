#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include "include/Voo.h"
#include "include/Aeronave.h"
#include "include/Pessoa.h"
#include "include/utils.h"

using namespace std;

vector<Voo> voos;

Aeronave* encontrarAeronave(vector<Aeronave>& aeronaves, const string& codigo) {
    for (auto& a : aeronaves) {
        if (a.getCodigo() == codigo) return &a;
    }
    return nullptr;
}

Piloto* encontrarPiloto(vector<shared_ptr<Pessoa>>& pessoas, const string& matricula) {
    for (auto& p : pessoas) {
        Piloto* piloto = dynamic_cast<Piloto*>(p.get());
        if (piloto && piloto->getMatricula() == matricula) return piloto;
    }
    return nullptr;
}

Passageiro* encontrarPassageiro(vector<shared_ptr<Pessoa>>& pessoas, const string& cpf) {
    for (auto& p : pessoas) {
        Passageiro* passageiro = dynamic_cast<Passageiro*>(p.get());
        if (passageiro && passageiro->getCPF() == cpf) return passageiro;
    }
    return nullptr;
}

void cadastrarVoo(vector<Aeronave>& aeronaves, vector<shared_ptr<Pessoa>>& pessoas) {
    string codigo, origem, destino, hora, codAeronave, matricula1, matricula2;
    double distancia;

    cout << "=== Cadastro de Voo ===\n";
    cout << "Código do voo: ";
    cin >> codigo;
    cin.ignore();
    cout << "Origem: ";
    getline(cin, origem);
    cout << "Destino: ";
    getline(cin, destino);
    cout << "Distância (milhas): ";
    cin >> distancia;
    cin.ignore();
    cout << "Hora de saída (ex: 14:30): ";
    getline(cin, hora);
    cout << "Código da Aeronave: ";
    getline(cin, codAeronave);

    Aeronave* aeronave = encontrarAeronave(aeronaves, codAeronave);
    if (!aeronave) {
        cout << "Aeronave não encontrada!\n";
        return;
    }

    cout << "Matrícula do comandante: ";
    getline(cin, matricula1);
    Piloto* comandante = encontrarPiloto(pessoas, matricula1);
    if (!comandante) {
        cout << "Comandante não encontrado!\n";
        return;
    }

    cout << "Matrícula do primeiro oficial: ";
    getline(cin, matricula2);
    Piloto* primeiroOficial = encontrarPiloto(pessoas, matricula2);
    if (!primeiroOficial) {
        cout << "Primeiro oficial não encontrado!\n";
        return;
    }

    Voo voo(codigo, origem, destino, distancia, hora, aeronave, comandante, primeiroOficial);
    voos.push_back(voo);

    cout << "Voo cadastrado com sucesso!\n";
}

void salvarVoosCSV() {
    ofstream arq("voos.csv");
    for (const auto& v : voos) {
        arq << v.toCSV() << endl;
    }
    cout << "Voos salvos em voos.csv\n";
}

void listarVoos() {
    cout << "\n=== Lista de Voos ===\n";
    for (const auto& v : voos) {
        string horaSaida = v.getHoraSaida();
        double tempoEstimado = v.getTempoEstimado();

        // Calcular hora de chegada prevista
        int hora, minuto;
        char sep;
        istringstream iss(horaSaida);
        iss >> hora >> sep >> minuto;
        int totalMin = hora * 60 + minuto + static_cast<int>(tempoEstimado * 60);
        int horaChegada = (totalMin / 60) % 24;
        int minutoChegada = totalMin % 60;

        cout << "Voo: " << v.getCodigo()
             << " | Aeronave: " << v.getAeronave()->getCodigo()
             << " (" << v.getAeronave()->getModelo() << ")"
             << " | Comandante: " << v.getComandante()->getMatricula()
             << " | Origem: " << v.getOrigem()
             << " | Destino: " << v.getDestino()
             << " | Passageiros: " << v.getPassageiros().size()
             << " | Saída: " << horaSaida
             << " | Chegada prevista: "
             << setfill('0') << setw(2) << horaChegada << ":"
             << setfill('0') << setw(2) << minutoChegada
             << endl;
    }
}

void associarPassageiroAoVoo(vector<shared_ptr<Pessoa>>& pessoas) {
    string codigoVoo, cpf;
    cout << "Código do voo: ";
    cin >> codigoVoo;
    Voo* voo = nullptr;

    for (auto& v : voos) {
        if (v.getCodigo() == codigoVoo) {
            voo = &v;
            break;
        }
    }

    if (!voo) {
        cout << "Voo não encontrado.\n";
        return;
    }

    cout << "CPF do passageiro: ";
    cin >> cpf;
    Passageiro* passageiro = encontrarPassageiro(pessoas, cpf);

    if (!passageiro) {
        cout << "Passageiro não encontrado.\n";
        return;
    }

    if (voo->adicionarPassageiro(passageiro)) {
        cout << "Passageiro adicionado com sucesso!\n";
    } else {
        cout << "Capacidade da aeronave atingida.\n";
    }
}

void listarPassageirosDoVoo() {
    string codigoVoo;
    cout << "Código do voo: ";
    cin.ignore(); // Garante que o buffer está limpo
    getline(cin, codigoVoo);

    // Remove espaços extras do início/fim
    codigoVoo.erase(0, codigoVoo.find_first_not_of(" \t\r\n"));
    codigoVoo.erase(codigoVoo.find_last_not_of(" \t\r\n") + 1);

    // Procura o voo pelo código
    Voo* voo = nullptr;
    for (auto& v : voos) {
        if (v.getCodigo() == codigoVoo) {
            voo = &v;
            break;
        }
    }

    if (!voo) {
        cout << "Voo não encontrado.\n";
        return;
    }

    cout << "Voo: " << voo->getCodigo()
         << " | Aeronave: " << voo->getAeronave()->getCodigo()
         << " (" << voo->getAeronave()->getModelo() << ")\n";

    const auto& passageiros = voo->getPassageiros();
    if (passageiros.empty()) {
        cout << "Nenhum passageiro neste voo.\n";
    } else {
        cout << "Passageiros:\n";
        for (const auto& p : passageiros) {
            cout << "- " << p->getNome() << endl;
        }
    }
}

int main() {
    // Simulando carregamento:
    vector<Aeronave> aeronaves = carregarAeronaves("aeronaves.csv");
    vector<shared_ptr<Pessoa>> pessoas = carregarPessoas("pessoas.csv");

    int opcao;
    do {
        cout << "\n=== Menu de Voos ===\n";
        cout << "1. Cadastrar voo\n";
        cout << "2. Listar voos\n";
        cout << "3. Associar passageiro ao voo\n";
        cout << "4. Salvar voos\n";
        cout << "5. Listar passageiros de um voo\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarVoo(aeronaves, pessoas); break;
            case 2: listarVoos(); break;
            case 3: associarPassageiroAoVoo(pessoas); break;
            case 4: salvarVoosCSV(); break;
            case 5: listarPassageirosDoVoo(); break;
            case 0: break;
            default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);

    return 0;
}
