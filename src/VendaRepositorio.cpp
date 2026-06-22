#include "VendaRepositorio.h"
#include "Funcs.h"
#include <sstream>
#include <fstream>

VendaRepositorio::VendaRepositorio() : RepositorioMemoriaBase<Venda>("Venda") {
    carregarDados();
}

VendaRepositorio::~VendaRepositorio() {
    salvarDados();
}

void VendaRepositorio::carregarDados() {
    ifstream entrada(nomeArquivo);
    if (!entrada.is_open()) return;

    string linha;
    while (getline(entrada, linha)) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string subTotalStr, idFuncionarioStr, idClienteStr, dataCompra;

        if (!getline(ss, subTotalStr, ';')) continue;
        if (!getline(ss, idFuncionarioStr, ';')) continue;
        if (!getline(ss, idClienteStr, ';')) continue;
        if (!getline(ss, dataCompra, ';')) continue;

        float subTotal = stof(subTotalStr);
        int idFuncionario = stoi(idFuncionarioStr);
        int idCliente = stoi(idClienteStr);

        Venda* venda = new Venda(subTotal, idFuncionario, idCliente, dataCompra);
        lista.push_back(venda);
    }
}

void VendaRepositorio::salvarDados() const {
    ofstream saida(nomeArquivo);
    if (!saida.is_open()) return;

    for (const Venda* venda : lista) {
        saida << venda->getSubTotal() << ";" << venda->getIdFuncionario() << ";" << venda->getIdCliente() << ";" << venda->getDataCompra() << "\n";
    }
}

void VendaRepositorio::validarEntidade(const Venda& v) const {
    if (v.getSubTotal() <= 0) 
        throw ValorInvalidoException("SubTotal");
    if (v.getIdFuncionario() <= 0 || v.getIdCliente() <= 0) 
        throw std::runtime_error("ID de Funcionario ou Cliente invalido (deve ser > 0).");
    if (v.getDataCompra().empty())
        throw CampoVazioException("Data da Compra");
}

Venda* VendaRepositorio::coletarDadosCriacao() {
    limparTerminal();
    cout << "--- CRIAR NOVA VENDA ---" << endl;
    float subTotal;
    int idFuncionario, idCliente;
    string dataCompra;
    
    cout << "ID do Funcionario: ";
    if (!(cin >> idFuncionario)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); throw std::invalid_argument("ID invalido."); }
    cout << "ID do Cliente: "; 
    if (!(cin >> idCliente)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); throw std::invalid_argument("ID invalido."); }
    cout << "SubTotal: ";
    if (!(cin >> subTotal)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); throw std::invalid_argument("SubTotal invalido."); }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Data da Compra (DD/MM/AAAA): "; getline(cin, dataCompra);
    
    Venda* novo = new Venda(subTotal, idFuncionario, idCliente, dataCompra);
    validarEntidade(*novo);
    return novo;
}

void VendaRepositorio::coletarDadosAtualizacao(Venda* existente) {
    float novoSubTotal = -1.0f;
    string novaDataCompra;

    cout << "Novo SubTotal (Atual: R$" << existente->getSubTotal() << ", deixe 0 ou vazio para não alterar): ";
    string totalInput;
    getline(cin, totalInput);
    if (!totalInput.empty() && totalInput != "0") {
        try {
            novoSubTotal = stof(totalInput);
            if (novoSubTotal <= 0) throw ValorInvalidoException("SubTotal");
        } catch (...) {
            throw std::invalid_argument("SubTotal invalido.");
        }
    }
    
    cout << "Nova Data da Compra (Atual: " << existente->getDataCompra() << "): ";
    getline(cin, novaDataCompra);

    if (novoSubTotal > 0) existente->setSubTotal(novoSubTotal);
    if (!novaDataCompra.empty()) existente->setDataCompra(novaDataCompra);
}

VendaRepositorio repoVendas;

void Vendas() {
    int opcao = -1;
    while (opcao != 0) {
        menuGenerico("Venda");
        if (!(cin >> opcao)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcao = -1; continue; }
        
        switch (opcao) {
            case 1: repoVendas.criar(); break;
            case 2: repoVendas.ler(); break;
            case 3: repoVendas.atualizar(); break;
            case 4: repoVendas.excluir(); break;
            case 0: break;
            default: cout << "Opcao invalida." << endl; break;
        }
    }
}