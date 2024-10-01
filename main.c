#include "function.h"
#include <stdio.h>
#include <string.h>

int main() {
    User user;
    welcome();
    diviser();
    loginOrRegister(&user);
    updateCryptoPrices();

    int option;
    do {
        menu(user.id);  
        scanf("%i", &option);
        
        switch (option) {
            case 1:
                checkUserInfos(user.id);
                break;
            case 2:
               showTransactionHistory(user.id);
                break;
            case 3:
                deposit(user.id);
                break;
            case 4:
                withdraw(user.id);
                break;
            case 5:
                buyCrypto(user.id); 
                break;
            case 6:
                sellCrypto(user.id); 
                break;
            case 7:
                updateCryptoPrices();
                break;
            case 8:
                printf("Encerrando Sessao...\n");
                break;
            default:
                diviser();
                printf("Opcao inválida. Tente novamente.\n");
                diviser();
                break;
        }
    } while (option != 8);

    return 0;
}
