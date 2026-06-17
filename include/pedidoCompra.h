#pragma once

#include "Base.h"
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

class TransicaoEstadoInvalidaException : public std::runtime_error {
public:
    TransicaoEstadoInvalidaException(const string& mensagem)
        : std::runtime_error("Erro de Regra de Negocio: " + mensagem) {}
};

class pedidoCompra : public Base {
private:
    int idFornecedor;
    float valor;
    string estado; // "ACEITO", "PAGO", "ENVIADO", "CANCELADO" e "ENTREGUE"
    vector<pair<int, int>> itens;
public:
    pedidoCompra(int idFornecedor, float valor) 
        : Base(), idFornecedor(idFornecedor), valor(valor), estado("ACEITO") {}
    
    int getIdFornecedor() const;
    float getValor() const;
    string getEstado() const;

    void setValor(const float novoValor);
    
    // Metodos da maquina de estados
    void pagarPedido();
    void enviarPedido();
    void entregarPedido();
    void cancelarPedido();

    // Metodos para gerenciar itens
    void adicionarItem(int idPeca, int quantidade);
    const vector<pair<int, int>>& getItens() const;

    virtual string toString() const override;
};  