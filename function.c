#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

float bitcoinPrice = 0, ethereumPrice = 0, ripplePrice = 0;
float oldBitcoinPrice = 0, oldEthereumPrice = 0, oldRipplePrice = 0;

// Tools 
void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}
void menu(int userId){
  printf("\nEscolha uma opcao:\n");
  diviser();
  printf("1 - Listar Usuarios\n");
  printf("2 - Consultar Informacoes e Saldo do Usuario\n");
  printf("3 - Consultar Extrato\n");
  printf("4 - Depositar na Carteira(R$)\n");
  printf("5 - Sacar da Carteira(R$)\n");
  printf("6 - Comprar Criptomoedas\n");
  printf("7 - Vender Criptomoedas\n");
  printf("8 - Ver Cotacao Atual\n");
  printf("9 - Sair\n");
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
void listUsers() {
  FILE *file = openFile("users.dat", "rb");
  if (!file) {
    return;
  }
  
  User user;
  printf("\nLista de Usuarios:\n");
  diviser();

  while (fread(&user, sizeof(User), 1, file) == 1) {
    printf("ID: %d\n", user.id);
    printf("CPF: %s\n", user.cpf);
    printf("Senha: %s\n", user.password);
    printf("Saldo em Reais: %.2f\n", user.balanceReal);
    printf("Saldo em Bitcoin: %.7f\n", user.balanceBitcoin);
    printf("Saldo em Ethereum: %.7f\n", user.balanceEthereum);
    printf("Saldo em Ripple: %.7f\n", user.balanceRipple);
    diviser();
  }

  fclose(file);
}

// User
void loginUser(User *user) {
  char cpf[11];
  char password[5];
  int isUser = 0;
  User tempUser;

  printf("\nFaca seu Login\n");
  diviser();
  printf("Digite o CPF (apenas numeros): ");
  scanf("%s", cpf);

  printf("Digite a senha: ");
  scanf("%s", password);

  FILE *file = fopen("users.dat", "rb");
  if (!file) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (fread(&user, sizeof(User), 1, file) == 1) {
    if (strcmp(tempUser.cpf, cpf) == 0 && strcmp(tempUser.password, password) == 0) {
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
    printf("Usuario nao encontrado.\nCPF ou Senha Incorretos.\n");
    diviser();
    loginOrRegister(user);
  }
}
void registerUser(User *user) {
  FILE *file = openFile("users.dat", "rb");
  if (!file) {
    return;
  }
  
  int userCount = 0;
  User tempUser;

  while (fread(&tempUser, sizeof(User), 1, file) == 1) {
    userCount++;
  }
  fclose(file);

  if (userCount >= 10) {
    diviser();
    printf("\nLimite de 10 usuarios atingido\n");
    diviser();
    loginOrRegister(user);
  }

  user->id = 1;
  file = fopen("users.dat", "rb");
  if (file != NULL) {
    User tempUser;  
    while (fread(&tempUser, sizeof(User), 1, file) == 1) {
      if (tempUser.id >= user->id) {
        user->id = tempUser.id + 1; 
      }
    }
    fclose(file);
  }
  
  printf("\nFaca seu Cadastro\n");
  diviser();
  printf("Digite o CPF (apenas numeros): ");
  scanf("%s", user->cpf);

  printf("Digite a senha: ");
  scanf("%s", user->password);

  user->balanceReal = 0;
  user->balanceBitcoin = 0;
  user->balanceEthereum = 0;
  user->balanceRipple = 0;
  
  
  file = openFile("users.dat", "ab");
  if (!file) {
    return;
  }

  fwrite(user, sizeof(User), 1, file);
  fclose(file);
  printf("\nUsario Registrado e Logado com Sucesso!\n");
  diviser();
}
void checkUserInfos(int userId){
  User user;
  int found = 0;
  FILE *file = fopen("users.dat", "r+b"); 
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
    
    printf("\nSua Carteira\n");
    diviser();
    fread(&user, sizeof(User), 1, file);
    printf("CPF: %s\n", user.cpf);
    printf("\nSaldo\n");
    diviser();
    printf("Reais: %.2f\n", user.balanceReal);
    printf("Bitcoin: %.7f\n", user.balanceBitcoin);
    printf("Ethereum: %.7f\n", user.balanceEthereum);
    printf("Ripple: %.7f\n", user.balanceRipple);
    diviser();
    
    
    fclose(file);
}
void deposit(int userId) {
  User user;
  int found = 0;
  float amount = 0;
  
  FILE *file = fopen("users.dat", "r+b"); 
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

      fseek(file, -sizeof(User), SEEK_CUR);
      fwrite(&user, sizeof(User), 1, file);

      printf("Saldo Atualizado: R$ %.2f\n", user.balanceReal);
      diviser();
      
      fclose(file);
  }
}
void withdraw(int userId){
  User user;
  int found = 0;
  float amount = 0;
  
  FILE *file = fopen("users.dat", "r+b"); 
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

      printf("Saldo Atualizado: R$ %.2f\n", user.balanceReal);
      diviser();
      
      fclose(file);
  }
}

// Cryptos
void updateCryptoPrices() {
    srand(time(0));

    oldBitcoinPrice = bitcoinPrice;
    oldEthereumPrice = ethereumPrice;
    oldRipplePrice = ripplePrice;

    bitcoinPrice = (rand() % 11 - 5) / 100.0 * BITCOIN_INITIAL + BITCOIN_INITIAL;
    ethereumPrice = (rand() % 11 - 5) / 100.0 * ETHEREUM_INITIAL + ETHEREUM_INITIAL;
    ripplePrice = (rand() % 11 - 5) / 100.0 * RIPPLE_INITIAL + RIPPLE_INITIAL;

    
    printf("\nCotacao Atual de Criptomoedas\n");
    diviser();
    
    // Bitcoin
    printf("1 Bitcoin: R$ %.2f ", bitcoinPrice);
    if (oldBitcoinPrice != 0) {
      if (bitcoinPrice > oldBitcoinPrice) {
          printf("(+%.2f%%)\n", ((bitcoinPrice - oldBitcoinPrice) / oldBitcoinPrice) * 100);
      } else if (bitcoinPrice < oldBitcoinPrice) {
          printf("(-%.2f%%)\n", ((oldBitcoinPrice - bitcoinPrice) / oldBitcoinPrice) * 100);
      } else {
          printf("(=)\n");
      }
    }
    else{
      printf("\n");
    }
    // Ethereum
    printf("1 Ethereum: R$ %.2f ", ethereumPrice);
    if (oldEthereumPrice != 0) {
      if (ethereumPrice > oldEthereumPrice) {
        printf("(+%.2f%%)\n", ((ethereumPrice - oldEthereumPrice) / oldEthereumPrice) * 100);
        } else if (ethereumPrice < oldEthereumPrice) {
            printf("(-%.2f%%)\n", ((oldEthereumPrice - ethereumPrice) / oldEthereumPrice) * 100);
        } else {
            printf("(=)\n");
        }
      } else{
        printf("\n");
      }

    // Ripple
    printf("1 Ripple: R$ %.2f ", ripplePrice);
    if (oldRipplePrice != 0) {
      if (ripplePrice > oldRipplePrice) {
          printf("(+%.2f%%)\n", ((ripplePrice - oldRipplePrice) / oldRipplePrice) * 100);
      } else if (ripplePrice < oldRipplePrice) {
          printf("(-%.2f%%)\n", ((oldRipplePrice - ripplePrice) / oldRipplePrice) * 100);
       } else {
            printf("(=)\n");
        }
      } else{
        printf("\n");
      }

    diviser();
}

void buyCrypto(int userId){
  updateCryptoPrices();
  User user;
  int found = 0, optionCripto = 0, confirmBuy = 0;
  float amount = 0;
  float fee = 0;

  FILE *file = fopen("users.dat", "r+b");
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
  printf("\nComprar Criptosmoedas\n");
  diviser();

  printf("Saldo Atual\n");
  printf("R$ %.2f (Reais)\n", user.balanceReal);
  printf("\nSaldo Atual de Criptos\n");
  diviser();
  printf("BTC %.7f (Bitcoin)\n", user.balanceBitcoin);
  printf("ETC %.7f (Ethereum)\n", user.balanceEthereum);
  printf("XRP %.7f (Ripple)\n", user.balanceRipple);
  diviser();

  
  printf("\nFaca sua compra\n");
  printf("1 - Bitcoin (BTC)\n");
  printf("2 - Ethereum (ETC)\n");
  printf("3 - Ripple (XRP)\n");

  printf("Digite sua escolha: ");
  scanf("%i", &optionCripto);

  printf("Digite o valor que deseja comprar em R$ ");
  scanf("%f", &amount);
  switch (optionCripto) {
      case 1:
        fee = amount * BITCOIN_BUY_FEE;
      break;
      case 2:
        fee = amount * ETHEREUM_BUY_FEE;
      break;
      case 3:
        fee = amount * RIPPLE_BUY_FEE;
      break;
      default:
        diviser();
        printf("\nOpcao invalida\n");
        diviser();
        buyCrypto(user.id); 
      break;
  }
  float totalCost = amount + fee;


  if (totalCost > user.balanceReal) {
      printf("\nSaldo insuficiente para realizar a compra somado a taxa.\n");
      fclose(file);
      return;
  }
  printf("\nVoce deseja comprar R$ %.2f em ", amount);

  switch (optionCripto) {
      case 1:
        printf("Bitcoin (BTC) + taxa R$%2.f?\n", + fee);
        diviser();
      break;
      case 2:
        printf("Ethereum (ETC)+ taxa R$%2.f?\n", + fee);
        diviser();
      break;
      case 3:
        printf("Ripple (XRP)+ taxa R$%2.f?\n", + fee);
        diviser();
      break;
      default:
        diviser();
        printf("\nOpcao invalida\n");
        diviser();
        buyCrypto(user.id); 
      break;
  }

  printf("\nConfirmacao\n");
  diviser();
  printf("1 - Sim\n");
  printf("2 - Nao\n");
  diviser();
  scanf("%i", &confirmBuy); 
  printf("\nCompra realizada!\n");
  if (confirmBuy == 1) {
    switch (optionCripto) {
        case 1:
          user.balanceReal -= totalCost;
          user.balanceBitcoin += amount / bitcoinPrice;
          printf("Saldo BTC: %.7f\n", user.balanceBitcoin);
          diviser();
        break;
        case 2:
          user.balanceReal -= totalCost;
          user.balanceEthereum += amount / ethereumPrice;
          printf("Saldo Atual ETC: %.7f\n", user.balanceEthereum);
          diviser();
        break;
        case 3:
          user.balanceReal -= totalCost;
          user.balanceRipple += amount / ripplePrice;
          printf("Saldo Atual XRP: %.7f\n", user.balanceRipple);
          diviser();
        break;
    }

    //REESCREVER O ARQUIVO
    fseek(file, -sizeof(User), SEEK_CUR);
    fwrite(&user, sizeof(User), 1, file);
    //FECHAR O ARQUIVO PARA SALVAR OS DADOS
    fclose(file);

  }else{
    printf("\nCompra Cancelada!\n");
    return;
  }
}

void sellCrypto(int userId){
  updateCryptoPrices();
  User user;
  int found = 0, optionCripto = 0, confirmSell = 0;
  float amount = 0, fee = 0, totalCost = 0;

  FILE *file = fopen("users.dat", "r+b");
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
  printf("\nVender Criptosmoedas\n");
  diviser();

  printf("Saldo Atual\n");
  printf("R$ %.2f (Reais)\n", user.balanceReal);
  printf("\nSaldo Atual de Criptos\n");
  diviser();
  printf("BTC %.7f (Bitcoin)\n", user.balanceBitcoin);
  printf("ETC %.7f (Ethereum)\n", user.balanceEthereum);
  printf("XRP %.7f (Ripple)\n", user.balanceRipple);
  diviser();

  printf("\nFaca sua venda\n");
  printf("1 - Bitcoin (BTC)\n");
  printf("2 - Ethereum (ETC)\n");
  printf("3 - Ripple (XRP)\n");

  printf("Digite sua escolha: ");
  scanf("%i", &optionCripto);

  printf("Digite o valor que deseja vender em ");
  
  switch (optionCripto) {
      case 1:
        printf("Bitcoin (BTC): ");
      break;
      case 2:
        printf("Ethereum (ETC): " );
      break;
      case 3:
        printf("Ripple (XRP): ");
      break;
      default:
        diviser();
        printf("\nOpcao invalida\n");
        diviser();
        sellCrypto(user.id); 
      break;
  }
  scanf("%f", &amount);
  diviser();
  switch (optionCripto) {
      case 1:

        fee = (amount * bitcoinPrice) * BITCOIN_SELL_FEE;
        totalCost = (amount * bitcoinPrice) - fee;

        if (totalCost > user.balanceBitcoin * bitcoinPrice) {
            printf("\nSaldo insuficiente!\nCusto Total + Taxa (R$%.2f): R$%.2f em Bitcoin\n", fee, totalCost);
            fclose(file);
            return;
          }

      break;
      case 2:
        fee = (amount * ethereumPrice) * ETHEREUM_SELL_FEE;
        totalCost = (amount * ethereumPrice) - fee;

        if (totalCost > user.balanceEthereum * ethereumPrice) {
          printf("\nSaldo insuficiente:\nCusto Total + Taxa (R$%.2f): R$%.2f em Ethereum\n", fee, totalCost);
          fclose(file);
          return;
        }

      break;
      case 3:
        fee = (amount * ripplePrice) *  RIPPLE_SELL_FEE;
        totalCost = (amount * ripplePrice) - fee;

      if (totalCost > user.balanceRipple * ripplePrice) {
        printf("\nSaldo insuficiente:\nCusto Total + Taxa (R$%.2f): R$%.2f em Ripple\n", fee, totalCost);
        fclose(file);
        return;
      }

      break;
      default:
        diviser();
        printf("\nOpcao invalida\n");
        diviser();
        sellCrypto(user.id); 
      break;
  }
 
  printf("\nVoce deseja vender %.7f em ", amount);

  switch (optionCripto) {
      case 1:
        printf("Bitcoin (BTC) + taxa R$%2.f?\n", + fee);
        diviser();
      break;
      case 2:
        printf("Ethereum (ETC)+ taxa R$%2.f?\n", + fee);
        diviser();
      break;
      case 3:
        printf("Ripple (XRP)+ taxa R$%2.f?\n", + fee);
        diviser();
      break;
      default:
        diviser();
        printf("\nOpcao invalida\n");
        diviser();
        sellCrypto(user.id); 
      break;
  }

  printf("\nConfirmacao\n");
  diviser();
  printf("1 - Sim\n");
  printf("2 - Nao\n");
  diviser();
  scanf("%i", &confirmSell); 

  printf("\nVenda realizada!\n");
  diviser();
  if (confirmSell == 1) {
    switch (optionCripto) {
        case 1:
          user.balanceReal += totalCost;
          user.balanceBitcoin -= amount;
          printf("\nSaldo Atual BTC: %.7f\n", user.balanceBitcoin);
          diviser();
        break;
        case 2:
          user.balanceReal += totalCost;
          user.balanceEthereum -= amount;
          printf("\nSaldo Atual ETC: %.7f\n", user.balanceEthereum);
          diviser();
        break;
        case 3:
          user.balanceReal += totalCost;
          user.balanceRipple -= amount;
          printf("\nSaldo Atual XRP: %.7f\n", user.balanceRipple);
          diviser();
        break;
    }
    printf("\nSaldo Atual R$: %.2f\n", user.balanceReal);

    fseek(file, -sizeof(User), SEEK_CUR);
    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

  }else{
    printf("\nVenda Cancelada!\n");
    return;
  }
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


