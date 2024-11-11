#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>

// VALORES INICIAIS E TAXAS DAS CRIPTOS
#define BITCOIN_INITIAL 354798.40
#define BITCOIN_BUY_FEE 0.02    // 2% 
#define BITCOIN_SELL_FEE 0.03   // 3% 

#define ETHEREUM_INITIAL 14461.70
#define ETHEREUM_BUY_FEE 0.01   // 1% 
#define ETHEREUM_SELL_FEE 0.02  // 2% 

#define RIPPLE_INITIAL 3.22
#define RIPPLE_BUY_FEE 0.01     // 1% 
#define RIPPLE_SELL_FEE 0.01    // 1% 


//STRUCT DOS DADOS DO USUÁRIO
typedef struct {
    int id;
    char cpf[12];
    char password[6];
    float balanceReal;
    float balanceBitcoin;
    float balanceEthereum;
    float balanceRipple;
} User;

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
