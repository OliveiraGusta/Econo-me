#include "function.h"
#include <stdio.h>
#include <string.h>

void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}

void diviser() { printf("-----------------------\n"); }

void loginOrRegister() {
  User user;
  int choice = 0;
  printf("PAINEL DO ADMINISTRADOR\n");
  diviser();
  printf("Faça seu Login ou Cadastro:\n");
  printf("1 - Cadastro\n");
  printf("2 - Login\n");
  diviser();
  scanf("%i", &choice);
  if (choice == 1)
    registerUser(&user);
  else if (choice == 2)
    loginUser();
  else {
    diviser();
    printf("Opcao invalida\n");
    diviser();
    loginOrRegister();
  }
}

void loginUser() {
  User user;
  char cpf[11];
  char password[5];

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
    printf("Seja Bem Vindo!\n");
    diviser();

  } else {
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
    printf("Limite de 10 usuarios atingido\n");
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

  printf("Digite o CPF (apenas números): ");
  scanf("%s", user->cpf);

  printf("Digite a senha: ");
  scanf("%s", user->password);

  file = openFile("users.dat", "ab");
  if (file == NULL) {
    return;
  }

  fwrite(user, sizeof(User), 1, file);
  fclose(file);
  printf("Usario Registrado e Logado com Sucesso!\n");
  diviser();
}

void listUsers() {
  FILE *file = openFile("users.dat", "rb");
  if (file == NULL) {
    return;
  }
  
  User user;
  int count = 0;
  printf("\nLista de Usuários:\n");
  diviser();

  while (fread(&user, sizeof(User), 1, file) == 1) {
    printf("ID: %d\n", user.id);
    printf("CPF: %s\n", user.cpf);
    printf("Senha: %s\n", user.password);
    diviser();
  }

  if (count == 0) {
    printf("Nenhum usuário cadastrado.\n");
  }

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