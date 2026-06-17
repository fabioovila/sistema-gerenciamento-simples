#include "pedidoCompra.h"
#include <sstream>

string pedidoCompra::toString() const {
    stringstream ss;
    ss << "ID: " << getId() 
       << " | Fornecedor ID: " << idFornecedor 
       << " | Valor Total: R$" << valor
       << " | Estado: " << estado;
    return ss.str();
}

int pedidoCompra::getIdFornecedor() const
{
    return idFornecedor;
}

float pedidoCompra::getValor() const
{
    return valor;
}

string pedidoCompra::getEstado() const 
{
    return estado;
}

void pedidoCompra::setValor(const float novoValor)
{
    if (novoValor < 0) {
        throw invalid_argument("O valor do pedido nao pode ser negativo.");
    }
    valor = novoValor;
}

// Maquina de Estados

void pedidoCompra::pagarPedido() 
{
    if (this->estado != "ACEITO") 
    {
        throw TransicaoEstadoInvalidaException("O pedido so pode ser pago se o estado atual for ACEITO");
    }
    this->estado = "PAGO";
}

void pedidoCompra::enviarPedido()
{
    if (this->estado != "PAGO") 
    {
        throw TransicaoEstadoInvalidaException("O pedido so pode ser aceito se o estado atual for PAGO");
    }
    this->estado = "ENVIADO";
}

void pedidoCompra::entregarPedido() 
{
    if (this->estado != "ENVIADO") 
    {
        throw TransicaoEstadoInvalidaException("O pedido so pode ser alterado para ENTREGUE se o estado atual for ENVIADO");
    }
    this->estado = "ENTREGUE";
}
void pedidoCompra::cancelarPedido()
{
    if (this->estado != "ENTREGUE") 
    {
        throw TransicaoEstadoInvalidaException("Nao e possivel CANCELAR um pedido que ja foi ENTREGUE");
    }
    this->estado = "CANCELADO";
}


// Gerenciamento de itens

void pedidoCompra::adicionarItem(int idPeca, int quantidade) 
{
    if (this->estado != "ACEITO")
    {
        throw runtime_error("Nao e possivel adicionar itens a um pedido que ja foi aceito.");
    }

    if (quantidade <= 0) 
    {
        throw invalid_argument("A quantidade de itens deve ser maior que zero.");
    }

    itens.push_back(make_pair(idPeca, quantidade));
}

const vector<pair<int, int>>& pedidoCompra::getItens() const 
{
    return itens;
}