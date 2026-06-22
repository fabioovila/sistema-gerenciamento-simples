# 📦 Sistema de Gestão de Estoque e Vendas (CRUD)
**Projeto Final de Disciplina** | **Autor:** Fábio Augusto V. de S. Vila | **Professor:** Jefferson Gomes Dutra  

---

## 📝 Visão Geral
Esta aplicação é um sistema de gestão robusto desenvolvido em **C++**, focado na aplicação prática dos pilares da **Programação Orientada a Objetos (POO)**: Abstração, Encapsulamento, Herança e Polimorfismo. O sistema permite o gerenciamento completo (CRUD) de estoque e vendas com persistência em arquivos.

---

## 🚀 Como Rodar a Aplicação

### Compilação e Execução
```bash
make clean   # Remove arquivos compilados anteriores
make         # Compila o projeto
./main       # Executa a aplicação
```

### Primeiro Login
Use um dos seguintes logins pré-cadastrados em `dados/usuarios.txt`:
- **Login:** `fabioovila` | **Senha:** (basta digitar o login)
- **Login:** `jerff` | **Senha:** (basta digitar o login)

### Estrutura de Pastas
```
dados/                 # Arquivos de persistência
├── usuarios.txt      # Dados de funcionários (login, nome, telefone, tema)
├── categorias.txt    # Categorias de peças
├── clientes.txt      # Clientes do sistema
├── fornecedores.txt  # Fornecedores
├── localizacoes.txt  # Localizações de estoque
├── pecas.txt         # Peças/produtos
├── pedidos.txt       # Pedidos de compra (com estado e itens)
└── vendas.txt        # Vendas realizadas
```

---

## ✅ Requisitos do Professor - Implementação

### 🏗️ 1. Mínimo 11 Classes
**Status:** ✅ 20 Classes Implementadas

- **8 Entidades:** `Base`, `Pessoa`, `Cliente`, `Fornecedor`, `Funcionario`, `Localizacao`, `Peca`, `pedidoCompra`, `Venda`, `Categoria`
- **8 Repositórios Concretos:** `CategoriaRepositorio`, `ClienteRepositorio`, `FornecedorRepositorio`, `FuncionarioRepositorio`, `LocalizacaoRepositorio`, `PecaRepositorio`, `PedidoCompraRepositorio`, `VendaRepositorio`
- **2 Interfaces:** `CrudInterface`, `FileInterface`
- **2 Classes Base Genéricas:** `RepositorioBase<T>`, `RepositorioMemoriaBase<T>`

### 🛡️ 2. Encapsulamento
**Status:** ✅ Totalmente Implementado

- Todos os atributos são `private` ou `protected`
- Acesso controlado via *getters* e *setters*
- Classe `Pessoa` usa `protected` para facilitar herança sem expor dados

### 🔄 3. Polimorfismo (Comportamentos Específicos)
**Status:** ✅ 2+ Hierarquias Implementadas

**Hierarquia 1 - Herança de Pessoas:**
```
Base
└── Pessoa
    ├── Cliente        (atributo: preferencia)
    ├── Fornecedor     (atributo: tipo)
    └── Funcionario    (atributos: login, tema)
```
Cada classe filha sobrescreve `toString()` com comportamento específico.

**Hierarquia 2 - Repositórios Polimórficos:**
```
CrudInterface (interface)
├── RepositorioMemoriaBase<T>
│   ├── CategoriaRepositorio
│   ├── ClienteRepositorio
│   ├── ... (6 repositórios mais)
│   └── VendaRepositorio
```
Cada repositório implementa validação e coleta de dados com regras específicas.

### 📋 4. Regras de Negócio (≥5)
**Status:** ✅ 7+ Regras Implementadas

1. **Validação de Campos Obrigatórios:** Nenhum campo pode ser vazio (exceção: `CampoVazioException`)
2. **Preços Sempre Positivos:** Peças, vendas e pedidos devem ter valor > 0 (exceção: `ValorInvalidoException`)
3. **Login Único:** Não permite dois funcionários com o mesmo login (exceção: `LoginDuplicadoException`)
4. **Máquina de Estados (Pedido):**
   - Estado inicial: `ACEITO`
   - Transições válidas: `ACEITO` → `PAGO` → `ENVIADO` → `ENTREGUE`
   - `CANCELADO` é permitido apenas de estados `ACEITO` ou `PAGO`
   - Exceção: `TransicaoEstadoInvalidaException`
5. **Itens do Pedido:** Só podem ser adicionados quando o pedido está em estado `ACEITO`
6. **ID de Entidades Deve ser Positivo:** Não permite IDs inválidos em relações
7. **Persistência Automática:** Todos os dados são salvos ao encerrar a aplicação

### ⚠️ 5. Tratamento de Exceções
**Status:** ✅ Exceções Customizadas + Validação

**Exceções Customizadas (em `include/Excecoes.h`):**
```cpp
- CampoVazioException      → Campo obrigatório vazio
- IdNaoEncontradoException → ID não encontrado em busca
- ValorInvalidoException   → Valor negativo ou zero inválido
- LoginDuplicadoException  → Login já existe no sistema
- TransicaoEstadoInvalidaException → Transição de estado inválida em pedido
```

**Exemplos de Uso:**
- Criar cliente sem nome → `CampoVazioException`
- Criar peça com preço ≤ 0 → `ValorInvalidoException`
- Pagar pedido já pago → `TransicaoEstadoInvalidaException`

### 💾 6. Persistência em Arquivo
**Status:** ✅ Todos os Repositórios Persistem

Cada repositório automaticamente:
- **Carrega:** Lê dados do arquivo `dados/*.txt` ao inicializar
- **Salva:** Escreve dados ao destruir o objeto (fim da aplicação)

Formatos:
- **Simples:** `campo1;campo2;campo3` (Categoria, Localizacao, Peca)
- **Composto:** Login + dados pessoais + preferências (Funcionario, Cliente, Fornecedor)
- **Complexo:** Pedido com estado + lista de itens serializada (pedidoCompra)

### 🔀 7. Estado Dinâmico
**Status:** ✅ Máquina de Estados (Pedido)

**Classe:** `pedidoCompra`

**Estados:** `ACEITO` → `PAGO` → `ENVIADO` → `ENTREGUE` / `CANCELADO`

**Métodos de Transição:**
```cpp
void pagarPedido()      // ACEITO → PAGO
void enviarPedido()     // PAGO → ENVIADO
void entregarPedido()   // ENVIADO → ENTREGUE
void cancelarPedido()   // ACEITO/PAGO → CANCELADO
```

**Validações:** Cada transição valida se o estado atual permite a mudança (arquivo: `src/pedidoCompra.cpp`).

### 🔄 8. CRUD Completo
**Status:** ✅ Implementado para Todas as Entidades

Cada repositório oferece:
- **Criar:** Coleta dados do usuário e valida com exceções
- **Ler:** Lista todos os registros
- **Atualizar:** Busca por ID e permite modificação de campos
- **Excluir:** Remove por ID com confirmação de existência

### 👤 9. Interação com Usuário
**Status:** ✅ Menu Terminal Completo

- Login obrigatório no início
- Menu principal com 8 setores
- Submenu genérico para cada setor (CRUD)
- Suporte a tema claro/escuro (salvo em preferência do usuário)

---

## 📊 Diagrama de Classes
O design foi modelado em UML:

🔗 **[Visualizar no Mermaid](https://www.mermaidchart.com/app/projects/69ceeb0f-547c-483b-bf58-ea52512b0b25/diagrams/f3b10483-6f2a-4620-8c1d-efd6449cdf47/version/v0.1/edit)**

---

## 📂 Estrutura de Código

```
include/              # Headers (definições de classes)
├── Base.h           # Classe abstrata base com ID auto-incremento
├── Pessoa.h         # Classe abstrata para pessoas
├── [Cliente|Fornecedor|Funcionario].h  # Heranças de Pessoa
├── [Categoria|Peca|Localizacao|Venda|pedidoCompra].h  # Entidades
├── [*Repositorio].h # Repositórios com persistência
├── CrudInterface.h  # Interface CRUD
├── FileInterface.h  # Interface de I/O
├── Excecoes.h       # Exceções customizadas
├── RepositorioMemoriaBase.h  # Template base para repositórios
└── Funcs.h          # Funções auxiliares e menu

src/                 # Implementações
├── *.cpp           # Implementação de cada classe

dados/              # Arquivos de persistência (gerados em tempo de execução)
└── *.txt           # Dados salvos

Makefile            # Build configuration
main.cpp            # Ponto de entrada
```

---

## 🎯 Conceitos POO Demonstrados

| Conceito | Implementação | Arquivo |
|----------|---------------|---------|
| **Encapsulamento** | Atributos `private/protected`, acesso via getters/setters | Todas as classes |
| **Herança** | `Pessoa` → `Cliente`, `Fornecedor`, `Funcionario` | `include/Pessoa.h` |
| **Polimorfismo** | `toString()` override; métodos virtuais em repositórios | Classes entidade + repositórios |
| **Abstração** | Classes abstratas `Base`, `Pessoa`, interfaces `CrudInterface` | `include/Base.h`, `include/Pessoa.h` |
| **Exceções** | Customizadas para validações de negócio | `include/Excecoes.h` |
| **Templates** | `RepositorioMemoriaBase<T>`, `RepositorioBase<T>` | `include/RepositorioMemoriaBase.h` |

---

## 🔧 Compilação e Limpeza

```bash
make         # Compila tudo
make run     # Compila e executa
make clean   # Remove arquivos .o e executável
```

---

## 📝 Notas de Desenvolvimento

- **Linguagem:** C++11
- **Compilador:** g++
- **IDE Suportadas:** VS Code, CLion, CodeBlocks
- **Dependências:** Nenhuma externa (apenas stdlib)
- **Formato de Persistência:** Arquivos de texto delimitados por `;`

---
