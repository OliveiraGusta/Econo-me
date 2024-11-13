#ifndef ADMIN_H
#define ADMIN_H
#include <stdio.h>

//STRUCT DOS DADOS DO USUÁRIO
typedef struct {
    int id;
    char cpf[12];
    char password[6];
    char name[15];
    float balanceReal;
    float balanceBitcoin;
    float balanceEthereum;
    float balanceRipple;
} User;

typedef struct {
    int id;
    char cpf[12];
    char password[6];
} Admin;


//FERRAMENTAS
void welcome();            
void diviser();       
void menu(int adminId); 
      
//LOGIN E CADASTRASTO
void loginOrRegister(Admin *admin);
void loginAdmin(Admin *admin);            
void registerAdmin(Admin *admin);

//FUNOCES DE USUARIO
void registerUser();


#endif