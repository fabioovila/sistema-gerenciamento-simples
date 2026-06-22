#include "FornecedorRepositorio.h"
#include "Funcs.h"
#include <sstream>
#include <fstream>

FornecedorRepositorio::FornecedorRepositorio() : RepositorioMemoriaBase<Fornecedor>("Fornecedor") {
    carregarDados();
}

FornecedorRepositorio::~FornecedorRepositorio() {
    salvarDados();
}

void FornecedorRepositorio::carregarDados() {
    ifstream entrada(nomeArquivo);
    if (!entrada.is_open()) return;

    string linha;
    while (getline(entrada, linha)) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string nome, telefone, tipo;

        if (!getline(ss, nome, ';')) continue;
        if (!getline(ss, telefone, ';')) continue;
        if (!getline(ss, tipo, ';')) continue;

        Fornecedor* fornecedor = new Fornecedor(nome, telefone, tipo);
        lista.push_back(fornecedor);
    }
}

void FornecedorRepositorio::salvarDados() const {
    ofstream saida(nomeArquivo);
    if (!saida.is_open()) return;

    for (const Fornecedor* fornecedor : lista) {
        saida << fornecedor->getNome() << ";" << fornecedor->getTelefone() << ";" << fornecedor->getTipo() << "\n";
    }
}

void FornecedorRepositorio::validarEntidade(const Fornecedor& forn) const {
    if (forn.getNome().empty() || forn.getTelefone().empty() || forn.getTipo().empty()) 
        throw CampoVazioException("Nome, Telefone ou Tipo");
}

Fornecedor* FornecedorRepositorio::coletarDadosCriacao() {
    limparTerminal();
    cout << "--- CRIAR NOVO FORNECEDOR ---" << endl;
    string nome, telefone, tipo;
    
    cout << "Nome do Fornecedor: "; getline(cin, nome);
    cout << "Telefone: "; getline(cin, telefone);
    cout << "Tipo de Produto/Servico: "; getline(cin, tipo);
    
    Fornecedor* novo = new Fornecedor(nome, telefone, tipo);
    validarEntidade(*novo);
    return novo;
}

void FornecedorRepositorio::coletarDadosAtualizacao(Fornecedor* existente) {
    string novoNome, novoTelefone, novoTipo;
    cout << "Novo Nome (Atual: " << existente->getNome() << "): "; getline(cin, novoNome);
    cout << "Novo Telefone (Atual: " << existente->getTelefone() << "): "; getline(cin, novoTelefone);
    cout << "Novo Tipo (Atual: " << existente->getTipo() << "): "; getline(cin, novoTipo);
    
    if (!novoNome.empty()) existente->setNome(novoNome);
    if (!novoTelefone.empty()) existente->setTelefone(novoTelefone);
    if (!novoTipo.empty()) existente->setTipo(novoTipo);
}

FornecedorRepositorio repoFornecedores;

void Fornecedores() {
    int opcao = -1;
    while (opcao != 0) {
        menuGenerico("Fornecedor");
        if (!(cin >> opcao)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcao = -1; continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (opcao) {
            case 1: repoFornecedores.criar(); break;
            case 2: repoFornecedores.ler(); break;
            case 3: repoFornecedores.atualizar(); break;
            case 4: repoFornecedores.excluir(); break;
            case 0: break;
            default: cout << "Opcao invalida." << endl; break;
        }
    }
}