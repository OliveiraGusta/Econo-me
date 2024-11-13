#include "admin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}
void menu(int adminId){
  printf("\nEscolha uma opcao:\n");
  diviser();
  printf("1 - Cadastro de novo investidor\n");
  printf("2 - Excluir investidor\n");
  printf("3 - Cadastro de criptomoeda\n");
  printf("4 - Excluir criptomoeda\n");
  printf("5 - Consultar saldo de um investidor\n");
  printf("6 - Consultar extrado de um investidor\n");
  printf("7 - Ver e Atualizar cotação de criptomoedas\n");
  printf("8 - Sair\n");
  diviser();
}
void diviser() { printf("-----------------------\n"); }


void loginOrRegister(Admin *admin) {
  int option = 0;
  printf("Faca seu Login ou Cadastro:\n");
  printf("1 - Cadastro\n");
  printf("2 - Login\n");
  diviser();
  printf("Digite sua escolha: ");
  scanf("%i", &option);
  if (option == 1)
    registerAdmin(admin);
  else if (option == 2)
    loginAdmin(admin);
  else {
    diviser();
    printf("\nOpcao invalida\n");
    diviser();
    loginOrRegister(admin);
  }
}


void loginAdmin(Admin *admin) {
  char cpf[12];
  char password[6];
  int isAdmin = 0;
  Admin tempAdmin;

  printf("\nFaca seu Login\n");
  diviser();
  printf("Digite o CPF (apenas numeros): ");
  scanf("%11s", cpf);

  printf("Digite a senha: ");
  scanf("%5s", password);

  FILE *file = fopen("admins_account.dat", "rb");
  if (!file) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
// PROCURA UM USUÁRIO COM O CPF E SENHA, CASO ENCONTRAR É UM USUÁRIO
  while (fread(&tempAdmin, sizeof(Admin), 1, file) == 1) {
          if (strcmp(tempAdmin.cpf, cpf) == 0 && strcmp(tempAdmin.password, password) == 0)  {
              *admin = tempAdmin; 
              isAdmin = 1;
              break;
          }
      }

      fclose(file);

      if (isAdmin) {
          diviser();
          printf("Seja Bem Vindo!\n");
          diviser();
      } else {
          diviser();
          printf("Usuário não encontrado.\nCPF ou Senha incorretos.\n");
          diviser();
          loginOrRegister(admin);
      }
  }

void registerAdmin(Admin *admin) {
    FILE *file = fopen("admins_account.dat", "rb"); 
    if (!file) {
        file = fopen("admins_account.dat", "wb");  
        if (!file) {
            printf("Erro ao abrir o arquivo de usuários.\n");
            return;
        }
    }

    int adminCount = 0;
    Admin tempAdmin;

    while (fread(&tempAdmin, sizeof(Admin), 1, file) == 1) {
        adminCount++;
    }
    fclose(file);

    if (adminCount >= 10) {
        diviser();
        printf("\nLimite de 10 usuários atingido\n");
        diviser();
        loginOrRegister(admin);  
        return;
    }

   
    admin->id = 1; 
    file = fopen("admins_account.dat", "rb");  
    if (file != NULL) {
        while (fread(&tempAdmin, sizeof(Admin), 1, file) == 1) {
            if (tempAdmin.id >= admin->id) {
                admin->id = tempAdmin.id + 1; 
            }
        }
        fclose(file);
    }

  
    printf("\nFaca seu Cadastro\n");
    diviser();
    printf("Digite o CPF (apenas numeros): ");
    scanf("%11s", admin->cpf);  

    printf("Digite a senha (ate 5 digitos): ");
    scanf("%5s", admin->password);  

    file = fopen("admins_account.dat", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(admin, sizeof(Admin), 1, file);
    fclose(file);

    printf("Administador Registrado e Logado com Sucesso!\n");
    diviser();
}

void registerUser() {

    FILE *file = fopen("users_account.dat", "rb"); 
    
    if (!file) {
        file = fopen("users_account.dat", "wb");  
        if (!file) {
            printf("Erro ao abrir o arquivo de usuários.\n");
            return;
        }
    }
    User user;
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
        return;
    }

    user.id = 1; 
    file = fopen("users_account.dat", "rb");  
   
    if (file != NULL) {
        while (fread(&tempUser, sizeof(User), 1, file) == 1) {
            if (tempUser.id >= user.id) {
                user.id = tempUser.id + 1; 
            }
        }
        fclose(file);
    }

    printf("187");
    printf("\nFaca o Cadastro do novo usuario\n");
    diviser();
    printf("Digite o nome: ");
    scanf("%14s", user.name);
    diviser();
    printf("Digite o CPF (apenas numeros): ");
    scanf("%11s", user.cpf);  

    printf("Digite a senha (até 5 dígitos): ");
    scanf("%5s", user.password);  

    user.balanceReal = 0.0;
    user.balanceBitcoin = 0.0;
    user.balanceEthereum = 0.0;
    user.balanceRipple = 0.0;

    file = fopen("users_account.dat", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("\nUsuario Registrado e Logado com Sucesso!\n");
    diviser();
}