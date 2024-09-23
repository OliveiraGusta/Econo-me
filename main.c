#include "function.h"
#include <stdio.h>
#include <string.h>


typedef struct {
    char cpf[12];
    char password[20];
} User;

void displayUserInfo(const User *user) {
    printf("CPF: %s\n", user->cpf);
    printf("Senha: %s\n", user->password);
}

int main(){
  User user;
  
  welcome();
  diviser();
  loginOrRegister();
  scanf("%i", user.cpf);


  
  return 0;
}