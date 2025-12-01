# 📚 Estrutura de Dados em C

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)

Repositório de projetos que implementam estruturas de dados em linguagem C, estruturados em módulos independentes, utilizados como material de estudo e prática da lógica de programação

## 🎯 Objetivos

- Praticar lógica de programação e estrutura de dados em linguagem C;
- Aplicação dos conceitos básicos de programação e organização do código;
- Criar projetos de pequeno e médio porte para fixar os conhecimentos aprendidos;
- Ter uma base de exemplos de projetos funcionais para consultas futuras.

## 📁 Estruturas Implementadas

Cada pasta desse repositório contém uma estrutura de dados específica.

| Estrutura | Descrição | Link |
|-|-|-|
| Árvore Binária | Estrutura de árvore binária clássica sem auto-balanceamento | [`Arvore Binaria/`](./Arvore%20Binaria) |
| Árvore Genérica | Implementação de árvores genéricas simulando um sistema de diretórios | [`Arvore Generica/`](./Arvore%20Generica) |
| Fila Dinâmica | Implementação de fila dinâmica com princípio de organização FIFO | [`Fila Dinamica/`](./Fila%20Dinamica) |
| Fila Estática Circular | Fila armazenada com vetores e organização circular | [`Fila Estatica Circular/`](./Fila%20Estatica%20Circular) |
| Fila Estática | Semelhante à fila dinâmica, mas com uso de vetores | [`Fila Estatica/`](./Fila%20Estatica) |
| Lista Dinâmica Circular | Lista dinâmica com organização circular | [`Lista Dinamica Circular/`](./Lista%20Dinamica%20Circular) |
| Lista Dinâmica Duplamente Encadeada | Lista dinâmica com navegação bidirecional | [`Lista Dinamica Duplamente Encadeada/`](./Lista%20Dinamica%20Duplamente%20Encadeada) |
| Lista Dinâmica Encadeada | Lista dinâmica com navegação unidirecional | [`Lista Dinamica Encadeada/`](./Lista%20Dinamica%20Encadeada) |
| Lista Estática | Lista estática com implementação de vetores | [`Lista Estatica/`](./Lista%20Estatica) |
| Notação Polonesa Reversa | Organização e resolução de expressões matemáticas com o uso da notação pós-fixa | [`Notacao Polonesa Reversa/`](./Notacao%20Polonesa%20Reversa) |
| Pilha Dinâmica | Implementação de pilha dinâmica com princípio de organização LIFO | [`Pilha Dinamica/`](./Pilha%20Dinamica) |
| Pilha Estática | Semelhante à pilha dinâmica, mas com uso de vetores | [`Pilha Estatica/`](./Pilha%20Estatica) |

### Dentro dos Projetos

```
Nome do Projeto/
├── include/    # Arquivos de cabeçalho (.h)
├── src/        # Implementação das funções (.c)
├── main.c      # Arquivo principal do projeto
└── README.md   # Documentação do projeto
```

## 🚀 Tecnologias Utilizadas

- **Linguagem:** C
- **Compilador:** GCC (GNU Compiler Collection)
- **IDE/Editor:** Visual Studio Code e CodeBlocks
- **Sistema**: Windows
- **Controle de Versão**: Git & GitHub

## 📖 Conceitos Abordados

- Estruturas condicionais (if/else) e laços de repetição (while/for);
- Funções e recursividade;
- Manipulação de dados em arquivos;
- Manipulação de vetores (arrays) e estruturas (structs);
- Gerenciamento de memória e manipulação de ponteiros (alocação e liberação);
- Tratamento de erros na manipulação de ponteiros;
- Operações em estrutura de dados (inserção, remoção, alteração, busca);
- Validações para entradas de dados;
- Algoritmos de ordenação.

## 🛠️ Compilar e Executar o Código

### Pré-Requisitos

- Ter o GCC (GNU Compiler Collection) instalado;
- Sistema operacional Windows.

### Passo-a-Passo

1. Clone o repositório:

```bash
git clone https://github.com/rafaelbaratta/Projetos-em-C.git
```

2. Navegue até o diretório da estrutura desejada:

```bash
cd ".\Estrutura-de-Dados-em-C\{Nome-do-Projeto}"
```

3. Compile o código :

```bash
gcc -I./include main.c src/*.c -o programa
```

4. Execute o programa :

```bash
programa.exe
```

# 👤 Autor

### Rafael Vinicius Baratta

🔗 [GitHub](https://github.com/rafaelbaratta)

💼 [LinkedIn](https://www.linkedin.com/in/rafaelbaratta/)

📧 [rafaelbaratta@hotmail.com](mailto:rafaelbaratta@hotmail.com)
