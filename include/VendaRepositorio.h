#pragma once
#include "RepositorioMemoriaBase.h"
#include "Venda.h"

class VendaRepositorio : public RepositorioMemoriaBase<Venda> {
protected:
    void validarEntidade(const Venda& entidade) const override;
    Venda* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(Venda* entidade) override;

private:
    string nomeArquivo = "vendas.txt";
    void carregarDados();
    void salvarDados() const;

public:
    VendaRepositorio();
    ~VendaRepositorio();
};