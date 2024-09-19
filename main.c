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

int main(void){
  User user;
  
  printf("Econome Cripto\n");
  printf("=========================\n");
  printf("Faça seu Login:\n");
  printf("CPF: ");
  scanf("%s", user.cpf);
  printf("Senha: ");
  print("\n")
  scanf("%s", user.password);
  displayUserInfo(&user);

  
  return 0;
}