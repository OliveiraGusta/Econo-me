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
    printf("2 - Sair\n");
    diviser();
    scanf("%i", &option);

    switch (option) {
    case 1:
      listUsers();
      break;
    case 2:
      printf("Encerrando Sessao...\n");
      break;
    default:
      diviser();
      printf("Opção invalida. Tente novamente.\n");
      diviser();
      break;
    }
  } while (option != 2);

  return 0;
}
