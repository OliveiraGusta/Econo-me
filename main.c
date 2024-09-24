#include "function.h"
#include <stdio.h>
#include <string.h>

int main() {
  welcome();
  diviser();
  int option = 0;
  loginOrRegister();

  do {
    printf("Escolha uma opção:\n");
    printf("1 - Listar Usuários\n");
    printf("2 - Consultar Informações e Saldo do Usuário\n");
    printf("3 - Consultar Extrato\n");
    printf("4 - Depositar na Carteira(R$)\n");
    printf("5 - Sacar da Carteira(R$)\n");
    printf("6 - Comprar Criptomoedas\n");
    printf("7 - Vender Criptomoedas\n");
    printf("8 - Atualizar Cotações\n");
    printf("9 - Sair\n");
    diviser();
    scanf("%i", &option);

    switch (option) {
    case 1:
      listUsers();
      break;
    case 9:
      printf("Encerrando Sessao...\n");
      break;
    default:
      diviser();
      printf("Opção invalida. Tente novamente.\n");
      diviser();
      break;
    }
  } while (option != 9);

  return 0;
}
