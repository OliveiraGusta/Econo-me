#ifndef ADMIN_H
#define ADMIN_H
#include <stdio.h>


typedef struct {
    int id;
    char cpf[12];
    char password[6];
} Admin;
//STRUCT DOS DADOS DO USUÁRIO

typedef struct {
    int cryptoId;        
    float balance;       
} UserCryptoBalance;

typedef struct {
    int id;
    char cpf[12];
    char password[6];
    char name[15];
    float balanceReal;         
    UserCryptoBalance balances[100]; 
    int cryptoCount;                
} User;

//STRUCT CRIPTOS
typedef struct {
    int id;
    char name[15];
    char abrev[6];
    float price;
    float buyFee;
    float sellFee;
} Cripto;

//STRUCT DOS DADOS DO EXTRATO
typedef struct {
    int userId;      
    char transactionType[20];  
    float amount;     
    float cryptoAmount;
    char cryptoType[10];    
    char date[20]; 
} Transaction;

//FERRAMENTAS
void welcome();            
void diviser();       
void menu(int adminId); 
      
//LOGIN E CADASTRO
void loginOrRegister(Admin *admin);
void loginAdmin(Admin *admin);            
void registerAdmin(Admin *admin);

//FUNCOES DE USUARIO
void registerUser();
void deleteUser();
void listUsers();
void checkUserInfos(char userCPF[]);
void checkUser();
void checkUserTransactionHistory();
void showTransactionHistory(char userCPF[]);
int getUserIdByCPF(char cpf[]);

//FUNCOES CRIPTO
void registerCripto();
void listCripto();
void deleteCripto();
void checkCriptosInfos(const char criptoABREVtoDelete[]);
int criptoExists(const char criptoABREVtoDelete[]);
void updateCryptoPrices();

//ARQUIVOS
int userExists(const char userCPF[]);


#endif