# 📚 Fila Dinâmica

Implementação de fila dinâmica em C com operações básicas de inserção, remoção, consulta e exibição
Princípio de organização **FIFO (First-In / First-Out)**: Primeiro elemento a entrar, primeiro elemento a sair

## 📁 Estruturas do Projeto

```
Fila Dinamica/
├── include/
|   └── filaDinamica.h      # Declarações de estruturas e funções (.h)
├── src/
|   └── filaDinamica.c      # Implementação das funções/operações (.c)
├── main.c                  # Arquivo principal do projeto
└── README.md               # Documentação do projeto (este documento)
```

## 🚀 Funções Implementadas

| Função | Descrição |
|-|-|
| `enfileirar()` | Inserção de novo elemento ao fim da fila (enqueue) |
| `desenfileirar()` | Remoção do primeiro elemento da fila (dequeue) |
| `consultar()` | Consultar primeiro elemento da fila (seequeue) |
| `exibir()` | Exibir todos os elementos da fila |

## 📖 Conceitos Abordados

- Estruturas condicionais e laços de repetição;
- Manipulação de estruturas (structs);
- Gerenciamento de memória e manipulação de ponteiros (alocação e liberação);
- Tratamento de erros na manipulação de ponteiros;
- Operações em estrutura de dados (inserção, remoção, consulta);
- Validações para entradas de dados.

## 🛠️ Compilar e Executar o Código

### Pré-Requisitos

- Ter o GCC (GNU Compiler Collection) instalado;
- Sistema operacional Windows.

### Passo-a-Passo

1. Clone o repositório:

```bash
git clone https://github.com/rafaelbaratta/Projetos-em-C.git
```

2. Navegue até o diretório do projeto:

```bash
cd ".\Estrutura-de-Dados-em-C\Fila Dinamica"
```

3. Compile o código :

```bash
gcc -I./include main.c src/filaDinamica.c -o filaDinamica
```

4. Execute o programa :

```bash
filaDinamica.exe
```

[`Voltar ao README Principal/`](../README.md)

# 👤 Autor

### Rafael Vinicius Baratta

🔗 [GitHub](https://github.com/rafaelbaratta)

💼 [LinkedIn](https://www.linkedin.com/in/rafaelbaratta/)

📧 [rafaelbaratta@hotmail.com](mailto:rafaelbaratta@hotmail.com)
