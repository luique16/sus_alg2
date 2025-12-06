<h1 align="center"> Trabalho de Algoritmos e Estruturas de Dados - SUS </h1>

### Sobre

O projeto é uma CLI feita em C para simular o funcionamento de um sistema de saúde que armazena usuários, cria filas e administra procedimentos aos pacientes.

### Como usar

Para conseguir executar o programa, basta executar os seguintes comandos:

```bash
make all   # Compila os arquivos
make data  # Gera os arquivos de dados
make run   # Executa o programa
```

### Funcionamento

O programa é formado por três interfaces principais:

1. Interface de lista (cadastro geral)

Nessa interface, é possível cadastrar novos pacientes, listar os pacientes cadastrados, buscar pacientes e remover pacientes. 

2. Interface de fila (administração de fila)

Nessa interface, é possível adicionar pacientes à fila, listar os pacientes na fila e chamar os pacientes para a próxima interface.

3. Interface de paciente (administração de procedimentos)

Nessa interface, é possível listar os procedimentos realizados pelo paciente, adicionar novos procedimentos e remover procedimentos.

### Estruturas utilizadas

- Lista de pacientes
    - Lista duplamente encadeada
    - Armazena as estruturas reais dos pacientes
    - É ordenada por ID e não tem limite de tamanho pré-definido

- Fila
    - Fila encadeada (queue)
    - Armazena uma referência para os pacientes
    - Tem limite de tamanho pré-definido (15 pacientes)

- Paciente
    - Armazena informações sobre o paciente
        - Nome
        - Idade
        - Seu histórico de procedimentos

- Histórico de procedimentos
    - Pilha sequencial
    - Armazena os procedimentos realizados pelo paciente
    - Limite pré-definido de 10 procedimentos

### Arquivos de dados

Os arquivos de dados são do tipo JSON e são lidos no inicio do programa e armazenados na saída.
Enquanto o arquivo list.json armazena a lista de pacientes com um array de objetos com os campos:

- `id`: int
- `name`: string
- `history`: string (representada como uma lista de substrings separadas por `;`)

O arquivo queue.json armazena a fila com um array de inteiros representando os ids dos pacientes.

### Estruturas de arquivos

- `include`     Arquivos .h dos TADs
- `src`         Arquivos .c dos TADs
- `internal`    Arquivos do cliente (sistema)
- `main.c`      Arquivo principal do cliente

### Integrantes do grupo

- Luís Henrique Fonseca Aguilar - 16885720
- Fabio Ganum FIlho - 15450803
