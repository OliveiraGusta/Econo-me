#ifndef USER_H
#define USER_H
#include <stdio.h>

typedef struct {
    int cryptoId;        
    float balance;       
} UserCryptoBalance;

//STRUCT DOS DADOS DO USUÁRIO
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
void menu(int userId); 
void loginOrRegister(User *user);
      
//USUÁRIO
void loginUser(User *user);            
void registerUser(User *user);
void checkUserInfos(int userId);              
void deposit(int userId);     
void withdraw(int userId);         

//CRIPTOS
void updateCryptoPrices();
void buyCrypto(int userId);
void sellCrypto(int userId);     

//TRANSAÇÕES
void addTransaction(int userId, const char *transactionType, float amount, float cryptoAmount, const char *cryptoType);
void showTransactionHistory(int userId);

//ARQUIVOS
FILE *openFile(const char *filename, const char *mode); 

#endif
