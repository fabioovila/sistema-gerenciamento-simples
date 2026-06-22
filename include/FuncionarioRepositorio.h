#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Funcionario.h"
#include "Excecoes.h"

using namespace std;

class FuncionarioRepositorio {
private:
    vector<Funcionario*> listaFuncionarios;
    string nomeArquivo = "dados/usuarios.txt";
    bool dadosAlterados = false;

    void carregarDados();
    void salvarDados();

public:
    FuncionarioRepositorio();
    ~FuncionarioRepositorio();

    Funcionario* fazerLogin(const string login);
    Funcionario* buscarPorLogin(const string login);
    
    void adicionar(const Funcionario& novoFuncionario);
    void atualizar(const Funcionario& funcionarioAtualizado);
    bool removerPorLogin(const std::string &login);

    const vector<Funcionario*>& listarFuncionarios() const { return listaFuncionarios; }
    bool houveAlteracao() const { return dadosAlterados; }
};