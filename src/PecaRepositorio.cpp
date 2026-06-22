#include "PecaRepositorio.h"
#include "Funcs.h"
#include <sstream>
#include <fstream>

PecaRepositorio::PecaRepositorio() : RepositorioMemoriaBase<Peca>("Peca") {
    carregarDados();
}

PecaRepositorio::~PecaRepositorio() {
    salvarDados();
}

void PecaRepositorio::carregarDados() {
    ifstream entrada(nomeArquivo);
    if (!entrada.is_open()) return;

    string linha;
    while (getline(entrada, linha)) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string nome, categoria;
        string precoStr;

        if (!getline(ss, nome, ';')) continue;
        if (!getline(ss, categoria, ';')) continue;
        if (!getline(ss, precoStr, ';')) continue;

        float preco = stof(precoStr);
        Peca* peca = new Peca(nome, preco, categoria);
        lista.push_back(peca);
    }
}

void PecaRepositorio::salvarDados() const {
    ofstream saida(nomeArquivo);
    if (!saida.is_open()) return;

    for (const Peca* p : lista) {
        saida << p->getNome() << ";" << p->getCategoria() << ";" << p->getPreco() << "\n";
    }
}

void PecaRepositorio::validarEntidade(const Peca& p) const {
    if (p.getNome().empty() || p.getCategoria().empty()) 
        throw CampoVazioException("Nome ou Categoria");
    if (p.getPreco() <= 0) 
        throw ValorInvalidoException("Preco");
}

Peca* PecaRepositorio::coletarDadosCriacao() {
    limparTerminal();
    cout << "--- CRIAR NOVA PEÇA ---" << endl;
    string nome, categoria;
    float preco;
    
    cout << "Nome da Peca: "; getline(cin, nome);
    cout << "Categoria: "; getline(cin, categoria);
    cout << "Preco: "; 
    if (!(cin >> preco)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); throw std::invalid_argument("Preco deve ser um numero."); }
    
    Peca* novo = new Peca(nome, preco, categoria);
    validarEntidade(*novo);
    return novo;
}

void PecaRepositorio::coletarDadosAtualizacao(Peca* existente) {
    string novoNome, novaCategoria;
    float novoPreco = -1.0f;

    cout << "Novo Nome (Atual: " << existente->getNome() << "): "; getline(cin, novoNome);
    cout << "Nova Categoria (Atual: " << existente->getCategoria() << "): "; getline(cin, novaCategoria);
    cout << "Novo Preco (Atual: R$" << existente->getPreco() << ", deixe 0 ou vazio para não alterar): "; 
    
    string precoInput;
    getline(cin, precoInput);
    if (!precoInput.empty() && precoInput != "0") {
        try {
            novoPreco = stof(precoInput);
            if (novoPreco <= 0) throw ValorInvalidoException("Preco");
        } catch (...) {
            throw std::invalid_argument("Preco invalido.");
        }
    }

    if (!novoNome.empty()) existente->setNome(novoNome);
    if (!novaCategoria.empty()) existente->setCategoria(novaCategoria);
    if (novoPreco > 0) existente->setPreco(novoPreco);
}

PecaRepositorio repoPecas;

void Pecas() {
    int opcao = -1;
    while (opcao != 0) {
        menuGenerico("Peca");
        if (!(cin >> opcao)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcao = -1; continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (opcao) {
            case 1: repoPecas.criar(); break;
            case 2: repoPecas.ler(); break;
            case 3: repoPecas.atualizar(); break;
            case 4: repoPecas.excluir(); break;
            case 0: break;
            default: cout << "Opcao invalida." << endl; break;
        }
    }
}