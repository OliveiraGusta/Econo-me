#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// Tools 
void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}
void menu(int userId){
  printf("\nEscolha uma opcao:\n");
  diviser();
  printf("1 - Consultar Informacoes e Saldo do Usuario\n");
  printf("2 - Consultar Extrato\n");
  printf("3 - Depositar na Carteira(R$)\n");
  printf("4 - Sacar da Carteira(R$)\n");
  printf("5 - Comprar Criptomoedas\n");
  printf("6 - Vender Criptomoedas\n");
  printf("7 - Ver Cotacao Atual\n");
  printf("8 - Sair\n");
  diviser();
}
void diviser() { printf("-----------------------\n"); }
void loginOrRegister(User *user) {
  int option = 0;
  printf("Faca seu Login ou Cadastro:\n");
  printf("1 - Cadastro\n");
  printf("2 - Login\n");
  diviser();
  printf("Digite sua escolha: ");
  scanf("%i", &option);
  if (option == 1)
    registerUser(user);
  else if (option == 2)
    loginUser(user);
  else {
    diviser();
    printf("\nOpcao invalida\n");
    diviser();
    loginOrRegister(user);
  }
}

// User
void loginUser(User *user) {
  char cpf[12];
  char password[6];
  int isUser = 0;
  User tempUser;

  printf("\nFaca seu Login\n");
  diviser();
  printf("Digite o CPF (apenas numeros): ");
  scanf("%11s", cpf);

  printf("Digite a senha: ");
  scanf("%5s", password);

  FILE *file = fopen("users_account.dat", "rb");
  if (!file) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
// PROCURA UM USUÁRIO COM O CPF E SENHA, CASO ENCONTRAR É UM USUÁRIO
  while (fread(&tempUser, sizeof(User), 1, file) == 1) {
          if (strcmp(tempUser.cpf, cpf) == 0 && strcmp(tempUser.password, password) == 0){
              *user = tempUser; 
              isUser = 1;
              break;
          }
      }

      fclose(file);

      if (isUser) {
          diviser();
          printf("Seja Bem Vindo!\n");
          diviser();
      } else {
          diviser();
          printf("Usuário não encontrado.\nCPF ou Senha incorretos.\n");
          diviser();
          loginOrRegister(user);
      }
  }
void registerUser(User *user) {
    FILE *file = fopen("users_account.dat", "rb");
    if (!file) {
        file = fopen("users_account.dat", "wb");
        if (!file) {
            printf("Erro ao abrir o arquivo de usuários.\n");
            return;
        }
    }

    int userCount = 0;
    User tempUser;

    while (fread(&tempUser, sizeof(User), 1, file) == 1) {
        userCount++;
    }
    fclose(file);

    if (userCount >= 10) {
        diviser();
        printf("\nLimite de 10 usuários atingido\n");
        diviser();
        loginOrRegister(user);  
        return;
    }

    // GERA ID UNICO
    user->id = 1; 
    file = fopen("users_account.dat", "rb");  
    if (file != NULL) {
        while (fread(&tempUser, sizeof(User), 1, file) == 1) {
            if (tempUser.id >= user->id) {
                user->id = tempUser.id + 1; 
            }
        }
        fclose(file);
    }

    // COLETA INFORMAÇOES
    printf("\nFaça seu Cadastro\n");
    diviser();
    printf("Digite seu nome: ");
    scanf("%14s", user->name);
    diviser();
    printf("Digite o CPF (apenas números): ");
    scanf("%11s", user->cpf);  

    printf("Digite a senha (até 5 dígitos): ");
    scanf("%5s", user->password);  

    user->balanceReal = 0.0;
    user->cryptoCount = 0; 
    for (int i = 0; i < 100; i++) {
        user->balances[i].cryptoId = -1; 
        user->balances[i].balance = 0.0;
    }

    file = fopen("users_account.dat", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(user, sizeof(User), 1, file);
    fclose(file);

    printf("\nUsuário Registrado e Logado com Sucesso!\n");
    diviser();
}
void checkUserInfos(int userId) {
    User user;
    int found = 0;
    FILE *file = fopen("users_account.dat", "r+b"); 
    if (file == NULL) {
        printf("Erro ao verificar seu saldo\n");
        return;
    }

    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (user.id == userId) { 
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Usuário não encontrado.\n");
        fclose(file);
        return;
    }
    printf("%s\n", user.name);
    printf("%s\n", user.cpf);
    diviser();

    // CARTEIRA
    printf("\nSua Carteira\n");
    diviser();
    printf("\nSaldo\n");
    diviser();
    printf("R$%.2f\n", user.balanceReal);

    // SALDO
    for (int i = 0; i < user.cryptoCount; i++) {
        int cryptoId = user.balances[i].cryptoId;
        float balance = user.balances[i].balance;

        FILE *cryptoFile = fopen("criptos.dat", "rb");
        if (cryptoFile == NULL) {
            printf("Erro ao carregar a lista de criptomoedas.\n");
            fclose(file);
            return;
        }

        Cripto cripto;
        char cryptoName[15] = "---";  
        char cryptoAbrev[6] = "---"; 

        while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
            if (cripto.id == cryptoId) {
                strncpy(cryptoName, cripto.name, sizeof(cryptoName) - 1);
                strncpy(cryptoAbrev, cripto.abrev, sizeof(cryptoAbrev) - 1);
                break;
            }
        }
        fclose(cryptoFile);

        // SALDO CRIPTOS
        printf("%s (%s): %.7f\n", cryptoName, cryptoAbrev, balance);
    }
    diviser();
    
    fclose(file);
}
void deposit(int userId) {
  User user;
  int found = 0;
  float amount = 0;
  
  FILE *file = fopen("users_account.dat", "r+b"); 
  if (file == NULL) {
      printf("Erro ao verificar seu saldo\n");
      return;
  }

  while (fread(&user, sizeof(User), 1, file) == 1) {
      if (user.id == userId) { 
          found = 1;
          break;
      }
  }
  if (!found) {
      printf("Usuario nao encontrado.\n");
      fclose(file);
      return;
  }
  diviser();
  printf("Saldo Atual: R$%.2f\n", user.balanceReal);
  
  
  printf("\nQual valor do deposito ou digite 0 para cancelar?\n");
  diviser();
  printf("R$ ");
  scanf("%f", &amount);
  diviser();
  
  if (amount == 0){
    return;
  }
  if (amount < 0) {
      printf("Seu deposito nao pode ser negativo ou zero.\n");
      fclose(file);
      deposit(userId); 
  } else {
      user.balanceReal += amount;
      //REESCREVE O ARQUIVO
      fseek(file, -sizeof(User), SEEK_CUR);
      fwrite(&user, sizeof(User), 1, file);
      //ADICIONA A TRANSAÇÃO AO ARQUIVO BASEADO NO ID DO USUÁRIO
      addTransaction(userId, "Deposito", amount, 0, "");
      printf("Saldo Atualizado: R$ %.2f\n", user.balanceReal);
      diviser();
      
      fclose(file);
  }
}
void withdraw(int userId){
  User user;
  int found = 0;
  float amount = 0;
  
  FILE *file = fopen("users_account.dat", "r+b"); 
  if (file == NULL) {
      printf("Erro ao verificar seu saldo\n");
      return;
  }

  while (fread(&user, sizeof(User), 1, file) == 1) {
      if (user.id == userId) { 
          found = 1;
          break;
      }
  }
  if (!found) {
      printf("Usuario nao encontrado.\n");
      fclose(file);
      return;
  }
  diviser();
  printf("Saldo Atual: R$%.2f\n", user.balanceReal);

  printf("\nQual valor de saque ou digite 0 para cancelar?\n");
  diviser();
  printf("R$ ");
  scanf("%f", &amount);
  diviser();

  if (amount == 0){
    return;
  }
  if (amount > user.balanceReal) {
      printf("Saque maior que o saldo.\n");
      fclose(file);
      deposit(userId); 
  } else {
      user.balanceReal -= amount;

      fseek(file, -sizeof(User), SEEK_CUR);
      fwrite(&user, sizeof(User), 1, file);

      addTransaction(userId, "Saque", amount, 0, "");
      printf("Saldo Atualizado: R$ %.2f\n", user.balanceReal);
      diviser();
      
      fclose(file);
  }
}

void updateCryptoPrices() {
    srand(time(0));  
    FILE *file = fopen("criptos.dat", "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo de Criptos.\n");
        return;
    }

    Cripto cripto;
    int foundCripto = 0;

    printf("\nCotacao Atual de Criptomoedas\n");
    diviser();

    while (fread(&cripto, sizeof(Cripto), 1, file) == 1) {
        float oldCriptoPrice = cripto.price;

        // ATUALIZA O PREÇO
        cripto.price += cripto.price * ((rand() % 11 - 5) / 100.0);

        // INFOMRÇÕES CRIPTO
        printf("1 %s (%s) : R$ %.2f ", cripto.name, cripto.abrev, cripto.price);
        if (oldCriptoPrice != 0) {
            if (cripto.price > oldCriptoPrice) {
                printf("(+%.2f%%)\n", ((cripto.price - oldCriptoPrice) / oldCriptoPrice) * 100);
            } else if (cripto.price < oldCriptoPrice) {
                printf("(-%.2f%%)\n", ((oldCriptoPrice - cripto.price) / oldCriptoPrice) * 100);
            } else {
                printf("(=)\n");
            }
        } else {
            printf("\n");
        }

        printf("Taxa de Compra: %.2f%%\n", cripto.buyFee);
        printf("Taxa de Venda: %.2f%%\n", cripto.sellFee);

        diviser();
        foundCripto = 1;

        fseek(file, -sizeof(Cripto), SEEK_CUR);

        fwrite(&cripto, sizeof(Cripto), 1, file);

        fflush(file);
    }

    if (!foundCripto) {
        printf("Nenhuma cripto encontrada.\n");
    }

    fclose(file);
}

void buyCrypto(int userId) {
    updateCryptoPrices(); 
    User user;
    Cripto cripto;
    int foundUser = 0, optionCripto = 0, confirmBuy = 0;
    float amount = 0, fee = 0, totalCost = 0;
    
    FILE *file = fopen("users_account.dat", "r+b");
    if (file == NULL) {
        printf("Erro ao verificar seu saldo.\n");
        return;
    }


    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (user.id == userId) {
            foundUser = 1;
            break;
        }
    }

    if (!foundUser) {
        printf("Usuário não encontrado.\n");
        fclose(file);
        return;
    }

    printf("\nSaldo Atual\n");
    printf("R$ %.2f (Reais)\n", user.balanceReal);
    printf("\nSaldo Atual de Criptomoedas\n");
    diviser();
    
    FILE *cryptoFile = fopen("criptos.dat", "rb");
    if (cryptoFile == NULL) {
        printf("Erro ao carregar lista de criptomoedas.\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < user.cryptoCount; i++) {
        while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
            if (cripto.id == user.balances[i].cryptoId) {
                printf("%s (%s): Saldo %.7f\n", cripto.name, cripto.abrev, user.balances[i].balance);
                break;
            }
        }
        fseek(cryptoFile, 0, SEEK_SET); 
    }
    diviser();

    // LISTA CRIPTOS PARA COMPRA
    printf("\nFaça sua compra\n");
    while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
        printf("%d - %s (%s)\n", cripto.id, cripto.name, cripto.abrev);
    }
    fclose(cryptoFile);

    printf("Digite o ID da criptomoeda que deseja comprar: ");
    scanf("%d", &optionCripto);

    printf("Digite o valor que deseja comprar em R$: ");
    scanf("%f", &amount);

    // LOCALIZA A CRIPTO
    cryptoFile = fopen("criptos.dat", "rb");
    Cripto selectedCripto;
    int foundCrypto = 0;
    while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
        if (cripto.id == optionCripto) {
            selectedCripto = cripto;
            foundCrypto = 1;
            break;
        }
    }
    fclose(cryptoFile);

    if (!foundCrypto) {
        printf("Criptomoeda não encontrada.\n");
        fclose(file);
        return;
    }

    // CALCULA CUSTO TOTAL COM TAXA
    fee = amount * selectedCripto.buyFee;
    totalCost = amount + fee;

    if (totalCost > user.balanceReal) {
        printf("\nSaldo insuficiente para realizar a compra.\n");
        fclose(file);
        return;
    }

    printf("\nVocê deseja comprar R$ %.2f em %s (%s) + taxa R$ %.2f?\n", 
        amount, selectedCripto.name, selectedCripto.abrev, fee);
    printf("1 - Sim\n2 - Não\n");
    scanf("%d", &confirmBuy);

    if (confirmBuy != 1) {
        printf("\nCompra cancelada!\n");
        fclose(file);
        return;
    }

    // ATUALIZA SALDO
    user.balanceReal -= totalCost;
    int cryptoBalanceIndex = -1;
    for (int i = 0; i < user.cryptoCount; i++) {
        if (user.balances[i].cryptoId == selectedCripto.id) {
            cryptoBalanceIndex = i;
            break;
        }
    }

    if (cryptoBalanceIndex == -1) { 
        cryptoBalanceIndex = user.cryptoCount;
        user.balances[cryptoBalanceIndex].cryptoId = selectedCripto.id;
        user.balances[cryptoBalanceIndex].balance = 0;
        user.cryptoCount++;
    }

    user.balances[cryptoBalanceIndex].balance += amount / selectedCripto.price;

    printf("\nCompra realizada!\n");
    printf("Novo saldo de %s: %.7f\n", selectedCripto.abrev, user.balances[cryptoBalanceIndex].balance);


    addTransaction(user.id, "Compra", totalCost, amount / selectedCripto.price, selectedCripto.name);


    fseek(file, -sizeof(User), SEEK_CUR);
    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
}
void sellCrypto(int userId) {
    updateCryptoPrices();
    User user;
    int found = 0, optionCripto = 0, confirmSell = 0;
    float amount = 0, fee = 0, totalCost = 0;

    FILE *file = fopen("users_account.dat", "r+b");
    if (file == NULL) {
        printf("Erro ao verificar seu saldo\n");
        return;
    }

    // LOCALIZA USER
    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (user.id == userId) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Usuário não encontrado.\n");
        fclose(file);
        return;
    }

    // SALDOS
    printf("\nVender Criptomoedas\n");
    diviser();

    printf("Saldo Atual\n");
    printf("R$ %.2f (Reais)\n", user.balanceReal);
    printf("\nSaldo Atual de Criptos\n");
    diviser();

    // CRIPTOS
    for (int i = 0; i < user.cryptoCount; i++) {
        int cryptoId = user.balances[i].cryptoId;
        float balance = user.balances[i].balance;

        FILE *cryptoFile = fopen("criptos.dat", "rb");
        if (cryptoFile == NULL) {
            printf("Erro ao carregar a lista de criptomoedas.\n");
            fclose(file);
            return;
        }

        Cripto cripto;
        // INICIA COM VALORES PADROES
        char cryptoName[15] = "---";
        char cryptoAbrev[6] = "---";

        // BUSCA PELO NOME E SIGLA
        while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
            if (cripto.id == cryptoId) {
                strncpy(cryptoName, cripto.name, sizeof(cryptoName) - 1);
                strncpy(cryptoAbrev, cripto.abrev, sizeof(cryptoAbrev) - 1);
                break;
            }
        }
        fclose(cryptoFile);

        // SALDO DA CRIPTO
        printf("%s (%s): %.7f\n", cryptoName, cryptoAbrev, balance);
    }
    diviser();

    printf("\nFaça sua venda\n");
    printf("Digite o número da criptomoeda que deseja vender: ");
    scanf("%i", &optionCripto);

    if (optionCripto < 1 || optionCripto > user.cryptoCount) {
        diviser();
        printf("\nOpção inválida\n");
        diviser();
        sellCrypto(user.id);
        return;
    }

    // VALOR A SER VENDIDO
    printf("Digite o valor que deseja vender em ");
    int cryptoId = user.balances[optionCripto - 1].cryptoId; 
    float balance = user.balances[optionCripto - 1].balance;

    FILE *cryptoFile = fopen("criptos.dat", "rb");
    if (cryptoFile == NULL) {
        printf("Erro ao carregar a lista de criptomoedas.\n");
        fclose(file);
        return;
    }

    Cripto cripto;
    float cryptoPrice = 0;
    float sellFee = 0;
    while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
        if (cripto.id == cryptoId) {
            cryptoPrice = cripto.price;  
            sellFee = cripto.sellFee;   
            break;
        }
    }
    fclose(cryptoFile);

    printf("Digite o valor que deseja vender: ");
    scanf("%f", &amount);
    diviser();

    // VERIRICA SE SALDO É SUFICIENTE
    fee = (amount * cryptoPrice) * sellFee;
    totalCost = (amount * cryptoPrice) - fee;

    if (totalCost > balance * cryptoPrice) {
        printf("\nSaldo insuficiente!\nCusto Total + Taxa (R$%.2f): R$%.2f\n", fee, totalCost);
        fclose(file);
        return;
    }

    // CONFIRMAÇÃO DE VENDA
    printf("\nVocê deseja vender %.7f em ", amount);
    printf("%s (%s) + taxa R$%.2f?\n", cripto.name, cripto.abrev, fee);
    diviser();

    printf("\nConfirmação\n");
    diviser();
    printf("1 - Sim\n");
    printf("2 - Não\n");
    diviser();
    scanf("%i", &confirmSell);

    if (confirmSell == 1) {
        // ATUALIZA SALDO
        user.balanceReal += totalCost;
        user.balances[optionCripto - 1].balance -= amount;

        printf("\nSaldo Atual %s: %.7f\n", cripto.name, user.balances[optionCripto - 1].balance);
        addTransaction(user.id, "Venda", totalCost, amount, cripto.name);

        diviser();

        printf("\nSaldo Atual R$: %.2f\n", user.balanceReal);

        fseek(file, -sizeof(User), SEEK_CUR);
        fwrite(&user, sizeof(User), 1, file);
        fclose(file);

        printf("\nVenda realizada!\n");
    } else {
        printf("\nVenda Cancelada!\n");
    }
}
void addTransaction(int userId, const char *transactionType,  float amount, float cryptoAmount, const char *cryptoType) {
      FILE *file = fopen("transactions.dat", "rb+"); 
      Transaction transactions[100];
      int transactionCount = 0;
      if (file != NULL) {
          while (fread(&transactions[transactionCount], sizeof(Transaction), 1, file) == 1) {
              transactionCount++;
          }
          fclose(file);
      }
      //VERIFICA SE TEM 100 LINHAS DE EXTRATO POR USUÁRIO  
      if (transactionCount == 100) {
          for (int i = 1; i < 100; i++) {
              transactions[i - 1] = transactions[i];
          }
          transactionCount = 99;
      }
      //SALVA AS VARIÁVEIS DA TRANSAÇÃO NA STRUCT TRANSICTION
      Transaction transaction;
      transaction.userId = userId;
      strcpy(transaction.transactionType, transactionType);
      transaction.amount = amount;
      transaction.cryptoAmount = cryptoAmount;
    
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      strcpy(transaction.cryptoType, cryptoType);
      // SALVA DATA E HORÁRIO DA TRANSAÇÃO
      snprintf(transaction.date, sizeof(transaction.date), "%02d/%02d/%04d %02dh%02d", 
              tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
  
      transactions[transactionCount] = transaction;
      file = fopen("transactions.dat", "wb");
        if (file != NULL) {
            fwrite(transactions, sizeof(Transaction), transactionCount + 1, file);
            fclose(file);
        }
  }
void showTransactionHistory(int userId) {
    FILE *file = fopen("transactions.dat", "rb");
    if (file == NULL) {
        printf("Erro ao acessar o arquivo de transações.\n");
        return;
    }

    Transaction transaction;
    int found = 0;
    printf("\nSeu Extrato\n");
    diviser();
  // LOOP E VERIFICÃÇÃO PARA EXIBIR O EXTRATO FORMATADO DO USUÁRIO
    while (fread(&transaction, sizeof(Transaction), 1, file) == 1) {
        if (transaction.userId == userId) {
            found = 1;
            printf("%s\n", transaction.transactionType);
            if (strcmp(transaction.transactionType, "Deposito") == 0 || strcmp(transaction.transactionType, "Saque") == 0) {
                printf("%cR$ %.2f\n", (strcmp(transaction.transactionType, "Saque") == 0) ? '-' : '+', transaction.amount);
            } else if (strcmp(transaction.transactionType, "Compra") == 0 || strcmp(transaction.transactionType, "Venda") == 0) {
                printf("%cR$ %.2f %c%s %.4f\n",
                       (strcmp(transaction.transactionType, "Compra") == 0) ? '-' : '+',
                       transaction.amount,
                       (strcmp(transaction.transactionType, "Compra") == 0) ? '+' : '-',
                       transaction.cryptoType, transaction.cryptoAmount);
            }
          
            printf("%s\n", transaction.date);
            diviser();
        }
    }

    if (!found) {
        printf("Nenhuma transacao encontrada.\n");
    }
    fclose(file);
}

// Files
FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (!file) {
    printf("Erro ao abrir o arquivo %s.\n", filename);
    return NULL;
  }
  return file;
}
