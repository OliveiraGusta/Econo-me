#include "function.h"
#include <stdio.h>
#include <string.h>

void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}

void menu(){
  printf("\nEscolha uma opção:\n");
  diviser();
  printf("1 - Listar Usuários\n");
  printf("2 - Consultar Informações e Saldo do Usuário\n");
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

void loginOrRegister() {
  User user;
  int choice = 0;
  printf("Faça seu Login ou Cadastro:\n");
  printf("1 - Cadastro\n");
  printf("2 - Login\n");
  diviser();
  printf("Digite sua escolha: ");
  scanf("%i", &choice);
  if (choice == 1)
    registerUser(&user);
  else if (choice == 2)
    loginUser();
  else {
    diviser();
    printf("\nOpcao invalida\n");
    diviser();
    loginOrRegister();
  }
}

void loginUser() {
  User user;
  char cpf[11];
  char password[5];
  
  printf("\nFaca seu Login\n");
  diviser();
  printf("Digite o CPF (apenas números): ");
  scanf("%s", cpf);

  printf("Digite a senha: ");
  scanf("%s", password);

  FILE *file = fopen("users.dat", "rb");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  int isUser = 0;
  while (fread(&user, sizeof(User), 1, file) == 1) {
    if (strcmp(user.cpf, cpf) == 0 && strcmp(user.password, password) == 0) {
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
    printf("Usuario não encontrado.\nCPF ou Senha Incorretos.\n");
    diviser();
    loginOrRegister();
  }
}

void registerUser(User *user) {
  FILE *file = openFile("users.dat", "rb");
  if (file == NULL) {
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
    loginOrRegister();
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
  printf("Digite o CPF (apenas números): ");
  scanf("%s", user->cpf);

  printf("Digite a senha: ");
  scanf("%s", user->password);

  user->balanceReal = 0;
  user->balanceBitcoin = 0;
  user->balanceEthereum = 0;
  user->balanceRipple = 0;
  
  
  file = openFile("users.dat", "ab");
  if (file == NULL) {
    return;
  }

  fwrite(user, sizeof(User), 1, file);
  fclose(file);
  printf("\nUsario Registrado e Logado com Sucesso!\n");
  diviser();
}

void listUsers() {
  FILE *file = openFile("users.dat", "rb");
  if (file == NULL) {
    return;
  }
  
  User user;
  printf("\nLista de Usuários:\n");
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

void checkUserInfos(){
  
   FILE *file = openFile("users.dat", "rb");
    if (file == NULL) {
      return;
    }
    
    printf("\nSua Carteira\n");
    diviser();
    User user;
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

FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    printf("Erro ao abrir o arquivo %s.\n", filename);
    return NULL;
  }
  return file;
}