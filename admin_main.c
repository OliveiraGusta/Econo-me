#include "admin.h"
#include <stdio.h>
#include <string.h>

int main() {
    Admin admin;
    welcome();
    diviser();

    //ESCOLHA DE CADASTRO OU LOGIN DO ADMINISTRADOR
    loginOrRegister(&admin);
    
    //LOPPING DO MENU
    int option;
    do {
        menu(admin.id);  
        scanf("%i", &option);
        
        switch (option) {
            case 1:
                registerUser();
                break;
            case 2:
                printf("Excluir investidor");
                printf("Em breve..");
                break;
            case 3:
                printf("Cadastro de criptomoeda");
                printf("Em breve..");  
                break;
            case 4:
                printf("Excluir criptomoeda");
                printf("Em breve..");
                break;
            case 5:
                printf("Consultar saldo de um investidor");
                printf("Em breve..");          
                break;
            case 6:
                printf("Consultar extrado de um investidor");
                printf("Em breve..");
                break;
            case 7:
                printf("Ver e Atualizar cotação de criptomoedas");
                printf("Em breve..");
                break;
            case 8:
                printf("Encerrando Sessao...\n");
                break;
            default:
                diviser();
                printf("Opcao invalida. Tente novamente.\n");
                diviser();
                break;
        }
    } while (option != 8);

    return 0;
}
