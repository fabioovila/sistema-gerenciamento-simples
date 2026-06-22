#pragma once
#include "RepositorioMemoriaBase.h"
#include "Categoria.h"

class CategoriaRepositorio : public RepositorioMemoriaBase<Categoria> {
protected:
    void validarEntidade(const Categoria& entidade) const override;
    Categoria* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(Categoria* entidade) override;

private:
    string nomeArquivo = "categorias.txt";
    void carregarDados();
    void salvarDados() const;

public:
    CategoriaRepositorio();
    ~CategoriaRepositorio();
};