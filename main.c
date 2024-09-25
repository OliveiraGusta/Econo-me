#include "function.h"
#include <stdio.h>
#include <string.h>

int main() {
    User user;
    welcome();
    diviser();
    loginOrRegister(&user);

    int option;
    do {
        menu(user.id);  
        scanf("%i", &option);
        switch (option) {
            case 1:
                listUsers();
                break;
            case 2:
                checkUserInfos();
                break;
            case 3:
                deposit(user.id); 
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
