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
                diviser();
                registerUser();
                break;
            case 2:
                diviser();
                listUsers();
                break;
            case 3:
                diviser();
                deleteUser();
                break;
            case 4:
                diviser();            
                printf("\nCadastro de criptomoeda");
                diviser();
                printf("Em breve..");  
                break;
            case 5:
                diviser();
                printf("Excluir criptomoeda");
                diviser();
                printf("Em breve..");
                break;
            case 6:
                diviser();
                printf("Consultar saldo de um investidor");
                diviser();
                printf("Em breve..");          
                break;
            case 7:
                diviser();
                printf("Consultar extrado de um investidor");
                diviser();
                printf("Em breve..");
                break;
            case 8:
                diviser();
                printf("Ver e Atualizar cotacao de criptomoedas");
                diviser();
                printf("Em breve..");
                break;
            case 9:
                diviser();
                printf("Encerrando Sessao...\n");
                break;
                break;
            default:
                diviser();
                printf("Opcao invalida. Tente novamente.\n");
                diviser();
                break;
        }
    } while (option != 9);

    return 0;
}
