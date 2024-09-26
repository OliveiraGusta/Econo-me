#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

float bitcoinPrice = 0, ethereumPrice = 0, ripplePrice = 0;;


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
  printf("8 - Atualizar C\n");
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
    printf("Saldo em Bitcoin: %.5f\n", user.balanceBitcoin);
    printf("Saldo em Ethereum: %.5f\n", user.balanceEthereum);
    printf("Saldo em Ripple: %.5f\n", user.balanceRipple);
    diviser();
  }

  fclose(file);
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
    printf("Bitcoin: %.5f\n", user.balanceBitcoin);
    printf("Ethereum: %.5f\n", user.balanceEthereum);
    printf("Ripple: %.5f\n", user.balanceRipple);
    diviser();
    
    
    fclose(file);
}


void updateCryptoPrices() {
    srand(time(0));

    bitcoinPrice = (rand() % 11 - 5) / 100.0 * BITCOIN_INITIAL + BITCOIN_INITIAL;
    ethereumPrice = (rand() % 11 - 5) / 100.0 * ETHEREUM_INITIAL + ETHEREUM_INITIAL;
    ripplePrice = (rand() % 11 - 5) / 100.0 * RIPPLE_INITIAL + RIPPLE_INITIAL;

    printf("\nCotacao Atual de Criptos moedas\n");
    diviser();
    printf("1 Bitcoin: R$ %.2f\n", bitcoinPrice);
    printf("1 Ethereum: R$ %.2f\n", ethereumPrice);
    printf("1 Ripple: R$ %.2f\n", ripplePrice);
    diviser();
}

void deposit(int userId) {
  User user;
  int found = 0, amount = 0;
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
  
  
  printf("\nQual valor do deposito?\n");
  diviser();
  printf("R$ ");
  scanf("%i", &amount);
  diviser();
  
  if (amount <= 0) {
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

void buyCrypto(int userId){

  updateCryptoPrices();
  User user;
  int found = 0, optionCripto = 0, confirmBuy = 0;
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
  printf("\nComprar Criptosmoedas\n");
  diviser();

  printf("Saldo Atual\n");
  printf("R$ %.2f (Reais)\n", user.balanceReal);
  printf("\nSaldo Atual de Criptos\n");
  diviser();
  printf("BTC %.5f (Bitcoin)\n", user.balanceBitcoin);
  printf("ETC %.5f (Ethereum)\n", user.balanceEthereum);
  printf("XRP %.5f (Ripple)\n", user.balanceRipple);
  diviser();

  

  printf("\nFaca sua compra\n");
  printf("1 - Bitcoin (BTC)\n");
  printf("2 - Ethereum (ETC)\n");
  printf("3 - Ripple (XRP)\n");

  printf("Digite sua escolha: ");
  scanf("%i", &optionCripto);

  printf("Digite o valor que deseja investir em R$ ");
  scanf("%.2f", &amount);

  if (amount > user.balanceReal) {
      printf("\nSaldo insuficiente para realizar a compra.\n");
      fclose(file);
      return;
  }
  printf("Voce deseja comprar R$ %.2f em ", amount);

  switch (optionCripto) {
      case 1:
        printf("Bitcoin (BTC)?\n");
        diviser();
      break;
      case 2:
        printf("Ethereum (ETC)?\n");
        diviser();
      break;
      case 3:
        printf("Ripple (XRP)?\n");
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
  printf("1 - Sim\n");
  printf("2 - Nao\n");
  scanf("%i", &confirmBuy); 

  if (confirmBuy == 1) {
    switch (optionCripto) {
        case 1:
        
          diviser();
          amount -= amount * BITCOIN_BUY_FEE;
          user.balanceReal -= amount;
          user.balanceBitcoin += amount / bitcoinPrice;
          printf("Compra realizada!\nSaldo BTC: %.5f\n", user.balanceBitcoin);
          diviser();
        break;
        case 2:
          printf("\nComprando Ethereum (ETC)\n");
          diviser();
          amount -= amount * ETHEREUM_BUY_FEE;
          user.balanceReal -= amount;
          user.balanceEthereum += amount / bitcoinPrice;
          printf("Compra realizada!\nSaldo ETC: %.5f\n", user.balanceEthereum);
          diviser();
        break;
        case 3:
          printf("\nComprando Ripple (XRP)\n");
          amount -= amount * RIPPLE_BUY_FEE;
          user.balanceReal -= amount;
          user.balanceRipple += amount / bitcoinPrice;
          printf("Compra realizada!\nSaldo XRP: %.5f\n", user.balanceRipple);
          diviser();
        break;
        default:
          diviser();
          printf("\nOpcao invalida\n");
          diviser();
          buyCrypto(user.id); 
        break;
    }

  }else{
    
    return;
  }
}



FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (!file) {
    printf("Erro ao abrir o arquivo %s.\n", filename);
    return NULL;
  }
  return file;
}


