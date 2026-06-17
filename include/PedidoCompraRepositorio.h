#pragma once
#include "RepositorioMemoriaBase.h"
#include "pedidoCompra.h"

class PedidoCompraRepositorio : public RepositorioMemoriaBase<pedidoCompra> {
protected:
    void validarEntidade(const pedidoCompra& entidade) const override;
    pedidoCompra* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(pedidoCompra* entidade) override;
public:
    PedidoCompraRepositorio() : RepositorioMemoriaBase<pedidoCompra>("Pedido de Compra") {}
};

extern PedidoCompraRepositorio repoPedidosCompra;
void PedidosCompra();