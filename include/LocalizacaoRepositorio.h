#pragma once
#include "RepositorioMemoriaBase.h"
#include "Localizacao.h"

class LocalizacaoRepositorio : public RepositorioMemoriaBase<Localizacao> {
protected:
    void validarEntidade(const Localizacao& entidade) const override;
    Localizacao* coletarDadosCriacao() override;
    void coletarDadosAtualizacao(Localizacao* entidade) override;

private:
    string nomeArquivo = "dados/localizacoes.txt";
    void carregarDados();
    void salvarDados() const;

public:
    LocalizacaoRepositorio();
    ~LocalizacaoRepositorio();
};