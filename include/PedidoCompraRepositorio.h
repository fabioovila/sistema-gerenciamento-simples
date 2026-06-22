#pragma once
#include "RepositorioMemoriaBase.h"
#include "pedidoCompra.h"

class PedidoCompraRepositorio : public RepositorioMemoriaBase<pedidoCompra> {
protected:
    void validarEntidade(const pedidoCompra& entidade) const override;
    pedidoCompra* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(pedidoCompra* entidade) override;

private:
    string nomeArquivo = "dados/pedidos.txt";
    void carregarDados();
    void salvarDados() const;

public:
    PedidoCompraRepositorio();
    ~PedidoCompraRepositorio();
};

extern PedidoCompraRepositorio repoPedidosCompra;
void PedidosCompra();