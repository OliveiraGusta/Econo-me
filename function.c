#include "function.h"
#include <stdio.h>
#include <string.h>

void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}
void menu(int userId){
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

void loginOrRegister(User *user) {
  int option = 0;
  printf("Faça seu Login ou Cadastro:\n");
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
  printf("Digite o CPF (apenas números): ");
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
    printf("Usuario não encontrado.\nCPF ou Senha Incorretos.\n");
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
  printf("Digite o CPF (apenas números): ");
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
    if (!file) {
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

void deposit(int userId) {
  User user;
  int found = 0;
  FILE *file = fopen("users.dat", "r+b");  // Usando fopen
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
  diviser();
  printf("Saldo Atual: R$%.2f\n", user.balanceReal);
  
  int choice = 0;
  printf("\nQual valor do depósito?\n");
  diviser();
  printf("R$ ");
  scanf("%i", &choice);
  diviser();
  
  if (choice <= 0) {
      printf("Seu depósito não pode ser negativo ou zero.\n");
      fclose(file);
      deposit(userId); 
  } else {
      user.balanceReal += choice;

      fseek(file, -sizeof(User), SEEK_CUR);
      fwrite(&user, sizeof(User), 1, file);

      printf("Saldo Atualizado: %.2f\n", user.balanceReal);
      diviser();
      
      fclose(file);
  }
}

void buyCrypto(int userId){
  User user;
  int found = 0, option = 0;
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
      printf("Usuário não encontrado.\n");
      fclose(file);
      return;
  }
  printf("\nComprar Criptosmoedas");
  diviser();
  printf("Saldo Atual");
  printf("R$ %.5f\n (Reais)", user.balanceBitcoin);
  printf("Saldo Atual de Criptos");
  diviser();
  printf("BTC %.5f\n (Bitcoin)", user.balanceBitcoin);
  printf("ETC %.5f\n (Ethereum)", user.balanceEthereum);
  printf("XRP %.5f\n (Ripple)", user.balanceRipple);
  diviser();
  printf("\nFaça sua compra\n");
  printf("1 - Bitcoin (BTC)\n");
  printf("2 - Ethereum (ETC)\n");
  printf("3 - Ripple (XRP)\n");
  printf("Digite sua escolha: ");
  scanf("%i", &option);
  switch (option) {
      case 1:
        printf("Bitcoin (BTC)\n");
        diviser();
        
      break;
      case 2:
        printf("Ethereum (ETC)\n");
        diviser();

      break;
      case 3:
        printf("Ripple (XRP)\n");
        diviser();
      break;
      default:
        diviser();
        printf("\nOpcao invalida\n");
        diviser();
      break;


}

FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (!file) {
    printf("Erro ao abrir o arquivo %s.\n", filename);
    return NULL;
  }
  return file;
}


