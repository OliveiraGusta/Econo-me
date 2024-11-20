

# README.MD
## Objetivo do projeto
- Criar uma exchenge de Criptomoedas funcional na linguagem C, que possua users e admins.
- Aprofundar os conhecimentos na prática em Ponteiros, Alocação de memória, Manipulação de arquivos e uso do Git e Github.
- Desenvolver habilidades em grupo ligadas ao uso do Github Workflow.



## Forma de Compilação e Execução para Usuário
- Passos para conseguir executar a Exchange de Criptos USER .
 1. ```gcc user.c user_main.c -o user``` 
 2. ```./user``` 

## Forma de Uso da Exchange para Usuários

### Cadastro e Login 
 Primeiramente, é preciso efetuar um cadastro, se ja possuir um usuário criado, efetue login.

### 1 - Consultar Informações e Saldo do Usuário
 É exibido na tela seu CPF e seus saldos na conta (Reais, Bitcoin, Ethereum e Ripple).

### 2 - Consultar Extrato
 É exibido na tela um histórico com as ultimas 100 operações efetuadas (Depósito, Saque, Compra de Cripto e Venda de Cripto), juntamente com data e hora.

### 3 - Depositar na Carteira 
 É exibido seu saldo atual em Reais e é preciso escolher o valor do seu depósito (Depósito).

### 4 - Sacar da Carteira
 É exibido seu saldo atual em Reais e é preciso escolher o valor do seu saque (Saque).

### 5 - Comprar Criptomoedas
 É exibido seus saldos atuais das Criptomoedas e é preciso escolher o valor de compra em Reais (Compra).

### 6 - Vender Criptomoedas
 É exibido seus saldos atuais das Criptomoedas e é preciso escolher o valor de conversão para Reais (Venda).

### 7 - Ver Cotacao Atual
 É exibido as cotações atuais das Criptomoedas.

### 8 - Sair
 Essa opção fecha o programa (Encerrando Sessão...)


## Forma de Compilação e Execução para Administradores
- Passos para conseguir executar a Exchange de Criptos ADMIN.
 1. ```gcc admin.c admin_main.c -o admin``` 
 2. ```./admin``` 


## Forma de Uso da Exchange para Administradores

### Cadastro e Login 
 Primeiramente, é preciso efetuar um cadastro para seu perfil de ADMIN, se ja possuir um, efetue login.

### 1 - Cadastro de novo Investidor
 É perguntado o Nome, CPF e Senha do seu novo usuário a que esta criando.

### 2 - Listar Usuários
 Serão exibidos na tela todos os usuários da exchange, com Nome, CPF e Senha.

### 3 - Excluir Investidos
 É perguntado o CPF do usuário que deseja excluir, logo após é necessário uma confimação de exclusão.

### 4 - Cadastro de Criptomoeda
 É perguntado o Nome, Sigla, Cotação Inicial, Taxa de Compra e Taxa de Venda da sua nova Cripto.

### 5 - Excluir Criptomoedas
 É preciso digitar a Sigla da Cripto que deseja excluir, logo após é necessário uma confimação de exclusão.

### 6 - Consultar saldo de um Investidor
 É necessário digitar o CPF do usuário que deseja consultar, após isso é exibído o saldo.

### 7 - Consultar extrato de um Investidor
 É necessário digitar o CPF do usuário que deseja consultar, após isso é exibído o extrato.

### 8 - Ver e Atualizar cotação de Criptomoedas
 É exibído na tela as atuais cotações das Criptos, logo após digite a Sigla de qual Cripto deseja atualizar a cotação

### 9 - Sair
 Essa opção fecha o programa (Encerrando Sessão...)




## Devs

### [@OliveiraGusta](https://www.github.com/OliveiraGusta)
Gustavo Rodrigues Oliveira - RA 22.222.007-1

### [@kenezb](https://www.github.com/kenezb)
Bruno Kenez Bergamasco Endo - RA 22.124.021-1


