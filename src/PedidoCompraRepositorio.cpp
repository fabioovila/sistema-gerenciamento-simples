#include "PedidoCompraRepositorio.h"
#include "Funcs.h"
#include <sstream>

void PedidoCompraRepositorio::validarEntidade(const pedidoCompra& ped) const {
    if (ped.getValor() <= 0) 
        throw ValorInvalidoException("Valor Total");
    if (ped.getIdFornecedor() <= 0) 
        throw std::runtime_error("ID do Fornecedor invalido (deve ser > 0).");
}

pedidoCompra* PedidoCompraRepositorio::coletarDadosCriacao() {
    limparTerminal();
    cout << "--- CRIAR NOVO PEDIDO DE COMPRA ---" << endl;
    int idFornecedor;
    float valor;
    
    cout << "ID do Fornecedor: ";
    if (!(cin >> idFornecedor)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); throw std::invalid_argument("ID invalido."); }
    cout << "Valor Total: "; 
    if (!(cin >> valor)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); throw std::invalid_argument("Valor invalido."); }
    
    pedidoCompra* novo = new pedidoCompra(idFornecedor, valor);
    validarEntidade(*novo);
    return novo;
}

void PedidoCompraRepositorio::coletarDadosAtualizacao(pedidoCompra* existente) 
{
    limparTerminal();
    
    cout << "ALTERAR ESTADO DO PEDIDO (ID: " << existente->getId() << ")" << endl;
    cout << "Estado Atual: " << existente->getEstado() << endl << endl << endl;
    cout << "1 - Registrar Pagamento (-> PAGO)" << endl;
    cout << "2 - Despachar Pedido (-> ENVIADO)" << endl;
    cout << "3 - Confirmar Entrega (-> ENTREGUE)" << endl;
    cout << "4 - Cancelar Pedido (-> CANCELADO)" << endl;
    cout << "0 - Voltar sem alterar" << endl;
    cout << "Escolha uma opcao: ";

    int opEstado;
    if (!(cin >> opEstado))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    try
    {
        switch(opEstado)
        {
            case 1:
                existente->pagarPedido();
                cout << "\nPedido pago com sucesso!" << endl;
                break;
            case 2:
                existente->enviarPedido();
                cout << "\nPedido enviado para a transportadora." << endl;
                break;
            case 3:
                existente->entregarPedido();
                cout << "\nPedido entregue ao destino final." << endl;
                break;
            case 4:
                existente->cancelarPedido();
                cout << "\nPedido cancelado." << endl;
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida" << endl;
                break;
        }
    }
    catch(const TransicaoEstadoInvalidaException& e)
    {
        cout << "\n[ERRO DE VALIDACAO] " << e.what() << endl;
        cout << "A transicao foi bloqueada pelo sistema." << endl;
    }

    cout << "\nPressione Enter para continuar...";
    cin.get();
}

PedidoCompraRepositorio repoPedidosCompra;

void PedidosCompra() {
    int opcao = -1;
    while (opcao != 0) {
        menuGenerico("Pedido de Compra");
        if (!(cin >> opcao)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcao = -1; continue; }
        
        switch (opcao) {
            case 1: repoPedidosCompra.criar(); break;
            case 2: repoPedidosCompra.ler(); break;
            case 3: repoPedidosCompra.atualizar(); break;
            case 4: repoPedidosCompra.excluir(); break;
            case 0: break;
            default: cout << "Opcao invalida." << endl; break;
        }
    }
}