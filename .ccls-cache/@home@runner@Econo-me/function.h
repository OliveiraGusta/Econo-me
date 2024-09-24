#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct {
  int  id; 
  char cpf[12];
  char password[6];
} User;

// Tools
void welcome();
void diviser();

// User Login
void loginUser();
void registerUser(User *user);
void loginOrRegister();

// Files
void listUsers();

#endif