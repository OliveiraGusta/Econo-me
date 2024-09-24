#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>

typedef struct {
  int id;
  char cpf[12];
  char password[6];
  float balanceReal;
  float balanceBitcoin;
  float balanceEthereum;
  float balanceRipple;

} User;

// Tools
void welcome();
void diviser();
void menu();

// User Login
void loginUser();
void registerUser(User *user);
void loginOrRegister();

// Files
void listUsers();
void checkUserInfos();
FILE *openFile(const char *filename, const char *mode);

#endif