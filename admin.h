#ifndef ADMIN_H
#define ADMIN_H
#include <stdio.h>


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


#endif