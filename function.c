#include "function.h"
#include <stdio.h>

void welcome(){
    printf("ECONO-ME CRIPTO\n");
    diviser();
    printf("O Super App da suas cripto moedas\n");


}

void diviser(){
    printf("-----------------------\n");

}

void loginOrRegister(){
    int choice = 0;
    printf("Escolha uma opcao:\n");
    printf("1 - Cadastro\n");
    printf("2 - Login\n");
    diviser();
    scanf("%i", &choice);
    if (choice == 1){
        //cadastro
        printf("Funcao Cadastro\n");
    }
    else if (choice == 2){
        //login
        printf("Funcao Login\n");
    }
    else {
        diviser();
        printf("Opcao invalida\n");
        diviser();
        loginOrRegister();
    }

}

void loginUser(){

}

void registerUser(){

}