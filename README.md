# 📦 Sistema de Gestão de Estoque e Vendas (CRUD)
**Projeto Final de Disciplina** **Autor:** Fábio Augusto V. de S. Vila  
**Professor:** Jefferson Gomes Dutra  

---

## 📝 Visão Geral
Esta aplicação é um sistema de gestão robusto desenvolvido em **C++**, focado na aplicação prática dos pilares da **Programação Orientada a Objetos (POO)**: Abstração, Encapsulamento, Herança e Polimorfismo. O sistema permite o gerenciamento completo (CRUD) de estoque e vendas.

---


## 🚀 Como Rodar a Aplicação

Para compilar e executar o projeto no GitHub Codespaces ou em um terminal Linux, utilize os comandos abaixo:

1. **Compilar o projeto:**
   ```bash
   make
   make run

---

## ✅ Requisitos e Implementação

### 🏗️ Arquitetura de Classes
O projeto supera o requisito mínimo de 11 classes, contando com **20 Classes/Interfaces Próprias**:
* **8 Entidades:** Categoria, Cliente, Fornecedor, Funcionario, Localizacao, Peca, pedidoCompra e Venda.
* **8 Repositórios Concretos:** Responsáveis pela persistência e lógica de cada entidade.
* **2 Classes Abstratas** e **2 Interfaces de Programação**.

### 🛡️ Encapsulamento e Herança
* **Privacidade:** Todos os atributos são `private` ou `protected`, com acesso restrito via *getters* e *setters*.
* **Otimização:** A classe `Pessoa` utiliza atributos `protected` para facilitar a herança, garantindo que classes filhas acessem dados essenciais de forma eficiente.
* **Independência:** Toda a lógica de herança e implementação da `CrudInterface` utiliza apenas código proprietário, sem dependências externas.

### 🧪 Tratamento de Exceções e Validação
O sistema garante a integridade dos dados através de um robusto sistema de exceções:
* **Exceções Customizadas:** Como `CampoVazioException` e `ValorInvalidoException`.
* **Validação Ativa:** Os Repositórios validam regras de negócio (ex: preços obrigatoriamente positivos) antes de persistir os dados.

### 💾 Persistência e Personalização
* O `FuncionarioRepositorio` gerencia o arquivo `usuarios.txt`.
* Salva e carrega automaticamente o **Nome de Exibição** e a preferência de **Tema (Claro/Escuro)** do usuário ao iniciar a aplicação.

---

## 📊 Modelagem (UML)
O design do sistema foi planejado utilizando diagramas de classe para visualizar as relações de herança e polimorfismo.

🔗 **[Visualizar Diagrama de Classes (Mermaid)](https://www.mermaidchart.com/app/projects/69ceeb0f-547c-483b-bf58-ea52512b0b25/diagrams/f3b10483-6f2a-4620-8c1d-efd6449cdf47/version/v0.1/edit)**

---
