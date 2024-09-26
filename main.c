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
                listUsers();
                break;
            case 2:
                checkUserInfos(user.id);
                break;
            case 3:
                printf("\nConsultar Extrato\n");
                printf("\nEm Breve...\n");
                diviser();
                break;
            case 4:
                deposit(user.id);
                break;
            case 5:
                printf("\nSacar da Carteira(R$)\n");
                printf("\nEm Breve...\n");
                diviser();
                break;
            case 6:
                buyCrypto(user.id); 
                break;
            case 7:
                printf("\nVender Criptomoedas\n");
                printf("\nEm Breve...\n");
                diviser();
                break;
            case 8:
                printf("\nAtualizar Cotação da Cripto\n");
                printf("\nEm Breve...\n");
                diviser(); 
                break;
            case 9:
                printf("Encerrando Sessão...\n");
                break;
            default:
                diviser();
                printf("Opção inválida. Tente novamente.\n");
                diviser();
                break;
        }
    } while (option != 9);

    return 0;
}
