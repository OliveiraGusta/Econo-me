#include "function.h"
#include <stdio.h>
#include <string.h>



int main() {
  welcome();
  diviser();
  int option = 0;
  loginOrRegister();

  do {
    menu();
    scanf("%i", &option);
    switch (option) {
    case 1:
      listUsers();
      break;
    case 2:
    checkUserInfos();
      break;
    case 4:
    deposit();
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
