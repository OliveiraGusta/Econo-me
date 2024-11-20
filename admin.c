#include "admin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void welcome() {
  printf("ECONO-ME CRIPTO\n");
  diviser();
  printf("O Super App da suas cripto moedas\n");
}
void menu(int adminId){
  printf("\nEscolha uma opcao:\n");
  diviser();
  printf("1 - Cadastro de novo investidor\n");
  printf("2 - Listar Usuarios\n");
  printf("3 - Excluir investidor\n");
  printf("4 - Cadastro de criptomoeda\n");
  printf("5 - Excluir criptomoeda\n");
  printf("6 - Consultar saldo de um investidor\n");
  printf("7 - Consultar extrado de um investidor\n");
  printf("8 - Ver e Atualizar cotacao de criptomoedas\n");
  printf("9 - Sair\n");
  diviser();
}
void diviser() { printf("-----------------------\n"); }
void loginOrRegister(Admin *admin) {
  int option = 0;
  printf("Faca seu Login ou Cadastro:\n");
  printf("1 - Cadastro\n");
  printf("2 - Login\n");
  diviser();
  printf("Digite sua escolha: ");
  scanf("%i", &option);
  if (option == 1)
    registerAdmin(admin);
  else if (option == 2)
    loginAdmin(admin);
  else {
    diviser();
    printf("\nOpcao invalida\n");
    diviser();
    loginOrRegister(admin);
  }
}
void loginAdmin(Admin *admin) {
  char cpf[12];
  char password[6];
  int isAdmin = 0;
  Admin tempAdmin;

  printf("\nFaca seu Login\n");
  diviser();
  printf("Digite o CPF (apenas numeros): ");
  scanf("%11s", cpf);

  printf("Digite a senha: ");
  scanf("%5s", password);

  FILE *file = fopen("admins_account.dat", "rb");
  if (!file) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
// PROCURA UM Usuario COM O CPF E SENHA, CASO ENCONTRAR É UM Usuario
  while (fread(&tempAdmin, sizeof(Admin), 1, file) == 1) {
          if (strcmp(tempAdmin.cpf, cpf) == 0 && strcmp(tempAdmin.password, password) == 0)  {
              *admin = tempAdmin; 
              isAdmin = 1;
              break;
          }
      }

      fclose(file);

      if (isAdmin) {
          diviser();
          printf("Seja Bem Vindo!\n");
          diviser();
      } else {
          diviser();
          printf("Usuario nao encontrado.\nCPF ou Senha incorretos.\n");
          diviser();
          loginOrRegister(admin);
      }
  }
void registerAdmin(Admin *admin) {
    FILE *file = fopen("admins_account.dat", "rb"); 
    if (!file) {
        file = fopen("admins_account.dat", "wb");  
        if (!file) {
            printf("Erro ao abrir o arquivo de Usuarios.\n");
            return;
        }
    }

    int adminCount = 0;
    Admin tempAdmin;

    while (fread(&tempAdmin, sizeof(Admin), 1, file) == 1) {
        adminCount++;
    }
    fclose(file);

    if (adminCount >= 10) {
        diviser();
        printf("\nLimite de 10 Usuarios atingido\n");
        diviser();
        loginOrRegister(admin);  
        return;
    }

   
    admin->id = 1; 
    file = fopen("admins_account.dat", "rb");  
    if (file != NULL) {
        while (fread(&tempAdmin, sizeof(Admin), 1, file) == 1) {
            if (tempAdmin.id >= admin->id) {
                admin->id = tempAdmin.id + 1; 
            }
        }
        fclose(file);
    }

  
    printf("\nFaca seu Cadastro\n");
    diviser();
    printf("Digite o CPF (apenas numeros): ");
    scanf("%11s", admin->cpf);  

    printf("Digite a senha (ate 5 digitos): ");
    scanf("%5s", admin->password);  

    file = fopen("admins_account.dat", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo de Usuarios.\n");
        return;
    }

    fwrite(admin, sizeof(Admin), 1, file);
    fclose(file);

    printf("\nAdministrador Registrado e Logado com Sucesso!\n");
    diviser();
}
void registerUser() {
    FILE *file = fopen("users_account.dat", "rb"); 
    if (!file) {
        file = fopen("users_account.dat", "wb");  
        if (!file) {
            printf("Erro ao abrir o arquivo de Usuarios.\n");
            return;
        }
    }
    User user;
    int userCount = 0;
    User tempUser;
  
    while (fread(&tempUser, sizeof(User), 1, file) == 1) {
        userCount++;
    }
    fclose(file);
    if (userCount >= 10) {
        diviser();
        printf("\nLimite de 10 Usuarios atingido\n");
        diviser(); 
        return;
    }

    user.id = 1; 
    file = fopen("users_account.dat", "rb");  
   
    if (file != NULL) {
        while (fread(&tempUser, sizeof(User), 1, file) == 1) {
            if (tempUser.id >= user.id) {
                user.id = tempUser.id + 1; 
            }
        }
        fclose(file);
    }

    printf("\nFaca o Cadastro do novo usuario\n");
    diviser();
    printf("Digite o nome: ");
    scanf("%14s", user.name);
    diviser();
    printf("Digite o CPF (apenas numeros): ");
    scanf("%11s", user.cpf);  

    printf("Digite a senha (ate 5 digitos): ");
    scanf("%5s", user.password);  

    
    // Inicializa saldo em reais e saldos de criptomoedas
    user.balanceReal = 0.0;
    user.cryptoCount = 0; // Nenhuma criptomoeda no momento do cadastro
    // Inicializa a lista de saldos de criptomoedas (caso precise inicializar com algum valor)
    for (int i = 0; i < 100; i++) {
        user.balances[i].cryptoId = -1; // ID inválido para criptos não atribuídas
        user.balances[i].balance = 0.0;
    }

    // Salva o usuário no arquivo
    file = fopen("users_account.dat", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("\nUsuário Registrado e Logado com Sucesso!\n");
    diviser();
}
void listUsers(){
    FILE *file = fopen("users_account.dat", "rb"); 
    if (!file) {
        printf("Erro ao abrir o arquivo de Usuarios.\n");
        return;
    }

    User user;
    int foundUser = 0; 
    printf("\nListando Usuarios\n");
    diviser();
    while (fread(&user, sizeof(User), 1, file) == 1) {
        foundUser = 1;
        printf("ID: %d\n", user.id);
        printf("Nome: %s\n", user.name);
        printf("CPF: %s\n", user.cpf);
        diviser();
    }

    if (!foundUser) {
        printf("Nenhum usuario encontrado.\n");
    }

    fclose(file);
}
void deleteUser() {
    FILE *file = fopen("users_account.dat", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de Usuarios.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Erro na funcao de apagar.\n");
        fclose(file);
        return;
    }

    char userCPFtoDelete[12];
    printf("\nDigite o CPF do Usuario que deseja excluir: ");
    scanf("%11s", userCPFtoDelete);

    if (userExists(userCPFtoDelete)) {
        checkUserInfos(userCPFtoDelete);
        int option = 0;
        printf("Deseja realmente excluir o usuario com o CPF %s:\n", userCPFtoDelete);
        printf("1 - Excluir\n");
        printf("2 - Cancelar\n");
        diviser();

        printf("Digite sua escolha: ");
        scanf("%i", &option);

        int userDeleted = 0;  // Marcação para exclusão
        if (option == 1) {
            User userToDelete;

            while (fread(&userToDelete, sizeof(User), 1, file) == 1) {
                if (strcmp(userToDelete.cpf, userCPFtoDelete) != 0) {
                    fwrite(&userToDelete, sizeof(User), 1, tempFile);
                } else {
                    userDeleted = 1;
                }
            }
        } else if (option == 2) {
            printf("Exclusão cancelada.\n");
        } else {
            printf("\nOpcao invalida\n");
        }

        // Fechar ambos os arquivos antes de qualquer operação de sistema
        fclose(file);
        fclose(tempFile);

        if (userDeleted) {
            if (remove("users_account.dat") != 0) {
                printf("Erro ao remover o arquivo original.\n");
            } else if (rename("temp.dat", "users_account.dat") != 0) {
                printf("Erro ao renomear o arquivo temporário.\n");
            } else {
                printf("Usuario excluido com sucesso.\n");
            }
        } else {
            remove("temp.dat"); // Limpeza do temporário se o usuário não foi encontrado
        }
    } else {
        printf("\nUsuario nao encontrado\n");
        fclose(file);
        fclose(tempFile);
        remove("temp.dat");
    }
}

int userExists(const char userCPF[]){
    User user;
    int foundUser = 0;
    
    FILE *file = fopen("users_account.dat", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        fclose(file);
        return 0;
    }

    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (strcmp(user.cpf, userCPF) == 0) {
            foundUser = 1;
            fclose(file);
            break;
        }
    }

    if (!foundUser) {
        return 0;
    } 

      return foundUser;
}


void checkUser(){
    char userCPF[12];
    printf("\nDigite o CPF do usuario que você deseja ver as informacoes: ");
    scanf("%12s", userCPF);
    checkUserInfos(userCPF);
}

void checkUserInfos(char userCPF[]){
    User user;
    int foundUser = 0;
    FILE *file = fopen("users_account.dat", "r+b"); 
    if (file == NULL) {
        printf("Erro ao verificar seu saldo\n");
        return;
    }

     while (fread(&user, sizeof(User), 1, file) == 1) {
        if (strcmp(user.cpf, userCPF) == 0) {
            foundUser = 1;
            fclose(file);
            break;
        }
    }

    if (!foundUser) {
        printf("Usuário não encontrado.\n");
        fclose(file);
        return;
    }
    
    printf("\nNome: %s\n", user.name);
    printf("CPF: %s\n", user.cpf);
    diviser();

    // Exibe a carteira do usuário
    printf("\nCarteira do investidor\n");
    diviser();
    printf("\nSaldo\n");
    diviser();
    printf("R$%.2f\n", user.balanceReal);

    for (int i = 0; i < user.cryptoCount; i++) {
        int cryptoId = user.balances[i].cryptoId;
        float balance = user.balances[i].balance;

        FILE *cryptoFile = fopen("criptos.dat", "rb");
        if (cryptoFile == NULL) {
            printf("Erro ao carregar a lista de criptomoedas.\n");
            fclose(file);
            return;
        }

        Cripto cripto;
        char cryptoName[15] = "---";  
        char cryptoAbrev[6] = "---"; 

        // Busca pelo nome e sigla da criptomoeda pelo ID
        while (fread(&cripto, sizeof(Cripto), 1, cryptoFile) == 1) {
            if (cripto.id == cryptoId) {
                strncpy(cryptoName, cripto.name, sizeof(cryptoName) - 1);
                strncpy(cryptoAbrev, cripto.abrev, sizeof(cryptoAbrev) - 1);
                break;
            }
        }
        fclose(cryptoFile);

        // Exibe o saldo da criptomoeda
        printf("%s (%s): %.7f\n", cryptoName, cryptoAbrev, balance);
    }
    diviser();
    
    fclose(file);
}

void registerCripto() {
    FILE *file = fopen("criptos.dat", "ab+"); // Abre em modo append e leitura
    if (!file) {
        printf("Erro ao abrir o arquivo de Criptos.\n");
        return;
    }

    Cripto cripto;
    Cripto temp;
    int lastId = 0;

    // Encontra o maior ID já registrado
    while (fread(&temp, sizeof(Cripto), 1, file) == 1) {
        if (temp.id > lastId) {
            lastId = temp.id;
        }
    }

    // Define o próximo ID
    cripto.id = lastId + 1;

    printf("\nCadastro de Nova Criptomoeda\n");
    diviser();

    printf("Digite o nome: ");
    scanf("%14s", cripto.name);

    printf("Digite a Sigla: ");
    scanf("%5s", cripto.abrev);

    diviser();
    printf("Digite a cotação inicial: ");
    scanf("%f", &cripto.price);

    diviser();
    printf("Digite a taxa de compra (ex: 1%% = 0.01): ");
    scanf("%f", &cripto.buyFee);

    diviser();
    printf("Digite a taxa de venda (ex: 1%% = 0.01): ");
    scanf("%f", &cripto.sellFee);

    // Escreve o registro no arquivo
    fwrite(&cripto, sizeof(Cripto), 1, file);
    fclose(file);

    printf("\nCriptomoeda cadastrada com sucesso:\n");
    diviser();
    printf("ID: %d\n", cripto.id);
    printf("Nome: %s\n", cripto.name);
    printf("Sigla: %s\n", cripto.abrev);
    printf("Cotação Inicial: %.2f\n", cripto.price);
    printf("Taxa de Compra: %.2f%%\n", cripto.buyFee * 100);
    printf("Taxa de Venda: %.2f%%\n", cripto.sellFee * 100);
}


void listCripto(){
    FILE *file = fopen("criptos.dat", "rb"); 
    if (!file) {
        printf("Erro ao abrir o arquivo de Criptos.\n");
        return;
    }

    Cripto cripto;
    int foundCripto = 0; 
    printf("\nListando Criptos\n");
    diviser();
    while (fread(&cripto, sizeof(Cripto), 1, file) == 1) {
        foundCripto = 1;
    printf("ID: %d\n", cripto.id);
    printf("Nome: %s\n", cripto.name);
    printf("Sigla: %s\n", cripto.abrev);
    printf("Cotacao Inicial: %.2f\n", cripto.price);
    printf("Taxa de Compra: %.2f%%\n", cripto.buyFee);
    printf("Taxa de Venda: %.2f%%\n", cripto.sellFee);        
    diviser();
    }

    if (!foundCripto) {
        printf("Nenhuma cripto encontrada.\n");
    }

    fclose(file);
}

void deleteCripto() {
    FILE *file = fopen("criptos.dat", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de Criptos.\n");
        return;
    }

    FILE *tempFile = fopen("tempcripto.dat", "wb");
    if (!tempFile) {
        printf("Erro na funcao de apagar.\n");
        fclose(file);
        return;
    }

    char criptoABREVtoDelete[6];
    printf("\nDigite a Sigla da Cripto que deseja excluir: ");
    scanf("%11s", criptoABREVtoDelete);

    if (criptoExists(criptoABREVtoDelete)) {
        checkCriptosInfos(criptoABREVtoDelete);
        int option = 0;
        printf("Deseja realmente excluir a Cripto com a Sigla %s:\n", criptoABREVtoDelete);
        printf("1 - Excluir\n");
        printf("2 - Cancelar\n");
        diviser();

        printf("Digite sua escolha: ");
        scanf("%i", &option);

        int criptoDeleted = 0;  
        if (option == 1) {
            Cripto criptoToDelete;

            while (fread(&criptoToDelete, sizeof(Cripto), 1, file) == 1) {
                if (strcmp(criptoToDelete.abrev, criptoABREVtoDelete) != 0) {
                    fwrite(&criptoToDelete, sizeof(Cripto), 1, tempFile);
                } else {
                    criptoDeleted = 1;
                }
            }
        } else if (option == 2) {
            printf("Exclusão cancelada.\n");
        } else {
            printf("\nOpcao invalida\n");
        }

        fclose(file);
        fclose(tempFile);

        if (criptoDeleted) {
            if (remove("criptos.dat") != 0) {
                printf("Erro ao remover o arquivo original.\n");
            } else if (rename("tempcripto.dat", "criptos.dat") != 0) {
                printf("Erro ao renomear o arquivo temporário.\n");
            } else {
                printf("Cripto excluida com sucesso.\n");
            }
        } else {
            remove("tempcripto.dat"); 
        }
    } else {
        printf("\nCripto nao encontrada\n");
        fclose(file);
        fclose(tempFile);
        remove("tempcripto.dat");
    }
}

void checkCriptosInfos(char criptoABREVtoDelete[]) {
    Cripto cripto;
    int foundCripto = 0;

    FILE *file = fopen("criptos.dat", "r+b");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de Criptos\n");
        return; 
    }

    while (fread(&cripto, sizeof(Cripto), 1, file) == 1) {
        if (strcmp(cripto.abrev, criptoABREVtoDelete) == 0) {
            foundCripto = 1;
            break; 
        }
    }

    if (!foundCripto) {
        printf("Cripto nao encontrada.\n");
        fclose(file);  
        return;
    }

    // LISTANDO CRIPTOS
    printf("\nListando Criptos\n");
    diviser();
    
    fseek(file, 0, SEEK_SET);
    
    while (fread(&cripto, sizeof(Cripto), 1, file) == 1) {
        printf("ID: %d\n", cripto.id);
        printf("Nome: %s\n", cripto.name);
        printf("Sigla: %s\n", cripto.abrev);
        printf("Cotacao Inicial: %.2f\n", cripto.price);
        printf("Taxa de Compra: %.2f%%\n", cripto.buyFee);
        printf("Taxa de Venda: %.2f%%\n", cripto.sellFee);
        diviser();
    }

    fclose(file); 
}

int criptoExists(const char criptoABREVtoDelete[]) {
    Cripto cripto;
    int foundCripto = 0;
    
    FILE *file = fopen("criptos.dat", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        fclose(file);
        return 0;
    }

    while (fread(&cripto, sizeof(Cripto), 1, file) == 1) {
        if (strcmp(cripto.abrev, criptoABREVtoDelete) == 0) {
            foundCripto = 1;
            fclose(file);
            break;
        }
    }

    if (!foundCripto) {
        return 0;
    } 

      return foundCripto;
}



