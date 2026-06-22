#pragma once
#include "RepositorioMemoriaBase.h"
#include "Cliente.h"

class ClienteRepositorio : public RepositorioMemoriaBase<Cliente> {
protected:
    void validarEntidade(const Cliente& entidade) const override;
    Cliente* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(Cliente* entidade) override;

private:
    string nomeArquivo = "clientes.txt";
    void carregarDados();
    void salvarDados() const;

public:
    ClienteRepositorio();
    ~ClienteRepositorio();
};