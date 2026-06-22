#pragma once
#include "RepositorioMemoriaBase.h"
#include "Fornecedor.h"

class FornecedorRepositorio : public RepositorioMemoriaBase<Fornecedor> {
protected:
    void validarEntidade(const Fornecedor& entidade) const override;
    Fornecedor* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(Fornecedor* entidade) override;

private:
    string nomeArquivo = "fornecedores.txt";
    void carregarDados();
    void salvarDados() const;

public:
    FornecedorRepositorio();
    ~FornecedorRepositorio();
};