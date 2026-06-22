#include "CategoriaRepositorio.h"
#include "Funcs.h"
#include <sstream>
#include <fstream>

CategoriaRepositorio::CategoriaRepositorio() : RepositorioMemoriaBase<Categoria>("Categoria") {
    carregarDados();
}

CategoriaRepositorio::~CategoriaRepositorio() {
    salvarDados();
}

void CategoriaRepositorio::carregarDados() {
    ifstream entrada(nomeArquivo);
    if (!entrada.is_open()) return;

    string linha;
    while (getline(entrada, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string nome, localizacao;

        if (!getline(ss, nome, ';')) continue;
        if (!getline(ss, localizacao, ';')) continue;

        Categoria* categoria = new Categoria(nome, localizacao);
        lista.push_back(categoria);
    }
}

void CategoriaRepositorio::salvarDados() const {
    ofstream saida(nomeArquivo);
    if (!saida.is_open()) return;

    for (const Categoria* categoria : lista) {
        saida << categoria->getNome() << ";" << categoria->getLocalizacao() << "\n";
    }
}

void CategoriaRepositorio::validarEntidade(const Categoria& cat) const {
    if (cat.getNome().empty()) throw CampoVazioException("Nome da Categoria");
    if (cat.getLocalizacao().empty()) throw CampoVazioException("Localizacao");
}

Categoria* CategoriaRepositorio::coletarDadosCriacao() {
    limparTerminal();
    cout << "--- CRIAR NOVA CATEGORIA ---" << endl;
    string nome, localizacao;
    
    cout << "Nome da Categoria: "; getline(cin, nome);
    cout << "Localizacao de Estoque: "; getline(cin, localizacao);
    
    Categoria* novaCategoria = new Categoria(nome, localizacao);
    validarEntidade(*novaCategoria);
    return novaCategoria;
}

void CategoriaRepositorio::coletarDadosAtualizacao(Categoria* existente) {
    string novoNome, novaLocalizacao;
    cout << "Novo Nome (Atual: " << existente->getNome() << "): "; getline(cin, novoNome);
    cout << "Nova Localizacao (Atual: " << existente->getLocalizacao() << "): "; getline(cin, novaLocalizacao);
    
    if (!novoNome.empty()) existente->setNome(novoNome);
    if (!novaLocalizacao.empty()) existente->setLocalizacao(novaLocalizacao);
}

CategoriaRepositorio repoCategorias;

void Categorias() {
    int opcao = -1;
    while (opcao != 0) {
        menuGenerico("Categoria");
        if (!(cin >> opcao)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcao = -1; continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (opcao) {
            case 1: repoCategorias.criar(); break;
            case 2: repoCategorias.ler(); break;
            case 3: repoCategorias.atualizar(); break;
            case 4: repoCategorias.excluir(); break;
            case 0: break;
            default: cout << "Opcao invalida." << endl; break;
        }
    }
}