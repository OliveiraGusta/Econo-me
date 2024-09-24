
# Econo-me Cripto 
## Projeto 1 - Exchange de Criptomoedas
Uma criptomoeda é um tipo de dinheiro – como outras moedas com as quais convivemos cotidianamente – com a diferença de ser totalmente digital. Além disso, ela não emitida por nenhum governo (como é o caso do real ou do dólar, por exemplo)​. O projeto consiste na criação da sua propria Exchange de Criptomoedas, uma plataforma onde é possível comprar e vender criptomoedas​.

Especificações
A sua Exchange deve trabalhar com 3 tipos de criptomoedas: ​

Bitcoin:​
Cobra uma taxa de 2% na compra de bitcoin​
Cobra uma taxa de 3% na venda de bitcoin​
Ethereum:​
Cobra uma taxa de 1% na compra de ethereum​
Cobra uma taxa de 2% na venda de ethereum​
Ripple:​
Cobra uma taxa de 1% na compra de ripple​
Cobra uma taxa de 1% na venda de ripple
Você deverá criar uma aplicação em C com funcionalidades para o usuário investidor conseguir as seguintes operações via console:​

Efetuar login​ usando CPF e senha: o menu principal deve aparecer apenas se estas informações estiverem corretas
Consultar saldo de reais, bitcoin, ethereum e ripple da carteira de investimentos​: exibir dados do usuário e os saldos 
Consultar extrato de operações da carteira de investimentos​: salvar em arquivo texto os dados do usuário e todas as informações de transações (data, valores e taxas)
Depositar reais na carteira de investimento​: usuário deve informar apenas os valores
Sacar reais da carteira de investimento​: usuário deve informar o valor do saque e a senha deve ser validada antes de realizar o saque
Comprar criptomoedas: usuário deve informar valor da compra e senha para validação. caso os dados estiverem corretos e a compra for possível, exibir as informações da compra (incluindo a taxa cobrada) e pedir a confirmação do usuário
Vender criptomoedas: caso os dados estiverem corretos, exibir as informações da venda (incluindo a taxa cobrada) e pedir a confirmação do usuário
Atualizar cotação das criptomoedas: usar valores aleatórios pra gerar mudanças de no máximo 5% e mínimo -5% do valor atual
O programa deve armazenar os dados de no máximo 10 usuários e o histórico das últimas 100 transações realizadas por cada usuário. Para garantir que os dados não serão perdidos, seu programa deve usar arquivos binários para o armazenamento das carteiras dos usuários.

## O que deve ser entregue
O link para um repositório do github/gitlab contendo todo o código desenvolvido para resolver o problema e um README.md contendo:

### 1. o objetivo do projeto
a forma de compilação e execução
uma breve explicação sobre a forma de uso do programa
lista com os nomes e matrícula dos participantes do grupo (o projeto pode ser feitos em duplas ou trios)
Critérios de avaliação
Implementação das funcionalidades (2.5 pontos):
    - será apenas considerado o que está na branch principal do repositório (main ou master) e não serão considerados funcionalidades em outras branches
    - a pontuação será dividida da seguinte forma: 0.25 para cada uma das 8 funcionalidades listadas acima, 0.5 pelo armazenamento (leitura e escrita) dos dados em arquivo binário
### 2. Uso correto do sistema de versionamento (2.5 pontos):
    - Uso do GitHub Workflow e branches para cada funcionalidade do projeto (1 ponto)
    - Commits com partes que do projeto que funcionam (1 ponto)
    - README.md contendo descrição do projeto, como compilar e executar (0.5 ponto)

### 3. Desenvolvimento do código (5 pontos)
    - A correção do código será feita pelo que foi implementado em cada branch. Projetos sem branches receberão zero nesta parte
    - Cada funcionalidade é implementada em uma função
    - As funções não utilizam variáveis globais, a não ser que seja a única forma de resolver o problema
    - As funcionalidades implementadas seguem o que foi pedido
    - Variáveis declaradas com nomes que podem ser entendidos
    - Código que pode ser facilmente estendido
    - Sem loops, desvios condicionais, funções e variáveis desnecessárias
    - Tratamento de erros que podem ocorrer durante a execução do programa
    - Uso de tipos corretos para dados
    - Tratamento correto dos dados inseridos pelo usuário

Critérios para zerar o projeto:

    1. Plágio ou cópia mesmo que parcial
    2. Programa que não compila/executa no replit
    3. Entrega sem o uso de sistema de versionamento ou de outra forma (arquivo zip ou link para replit)
    4. Upload de todo o código direto no repositório
    5. Entrega apenas do binário, sem o código
    6. Apenas receberão notas os participantes do projeto que tiverem commits que foram feito merge na branch main/master. Integrantes que não tiverem commits que tiveram merge na main não receberão nota
    7. O projeto possui commits realizados após o horário final da entrega do projeto

