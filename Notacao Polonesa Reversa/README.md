# 📚 Notação Polonesa Reversa

Implementação da notação polonesa reversa em linguagem C com a organização e resolução de expressões numéricas.

## 📁 Estruturas do Projeto

```
Notacao Polonesa Reversa/
├── include/
|   └── notacao.h      # Declarações de estruturas e funções (.h)
├── src/
|   └── notacao.c      # Implementação das funções/operações (.c)
├── main.c                  # Arquivo principal do projeto
└── README.md               # Documentação do projeto (este documento)
```

## 🚀 Funções Implementadas

| Função | Descrição |
|-|-|
| `lerExpressao()` | Leitura da entrada da expressão do usuário |
| `limparEspacos()` | Limpar os espaços entre os valores da expressão, se houver |
| `expressaoValida()` | Verificação se a expressão inserida pelo usuário é válida |
| `organizarExpressao()` | Organização da expressão para a notação pós-fixa |
| `calcular()` | Cálculo da expressão utilizando como base a notação pós-fixa |
| `operacoes()` | Operações com dois valores e um operador |

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
cd ".\Estrutura-de-Dados-em-C\Notacao Polonesa Reversa"
```

3. Compile o código :

```bash
gcc -I./include main.c src/notacao.c -o notacao
```

4. Execute o programa :

```bash
notacao.exe
```

[`Voltar ao README Principal/`](../README.md)

# 👤 Autor

### Rafael Vinicius Baratta

🔗 [GitHub](https://github.com/rafaelbaratta)

💼 [LinkedIn](https://www.linkedin.com/in/rafaelbaratta/)

📧 [rafaelbaratta@hotmail.com](mailto:rafaelbaratta@hotmail.com)
