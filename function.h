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
void menu(int userId); 
void loginOrRegister(User *user);
void listUsers();     
      
// User
void loginUser(User *user);            
void registerUser(User *user);

// Cryptos
void deposit(int userId);              
void checkUserInfos();  
void buyCrypto(int userId);   

// Files
FILE *openFile(const char *filename, const char *mode); 

#endif
