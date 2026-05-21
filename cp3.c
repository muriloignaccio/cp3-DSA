#include <stdio.h>
#include <stdlib.h>

void exibirMenu() {
  printf("\n========================\n");
  printf(" CAIXA ELETRONICO \n");
  printf("========================\n");
  printf("1 - Consultar Saldo\n");
  printf("2 - Realizar Saque\n");
  printf("3 - Realizar Deposito\n");
  printf("4 - Consultar Extrato\n");
  printf("0 - Sair\n");
  printf("========================\n");
  printf("Escolha uma opcao: ");
}

void pausar(int limparBuffer) {
  if (limparBuffer) {
      while (getchar() != '\n');
  }

  printf("\nPressione ENTER para continuar...");
  getchar();
}

void consultarSaldo(float saldo) {
  printf("\n--- SALDO ATUAL ---\n");
  printf("R$ %.2f\n", saldo);
  printf("-------------------\n");
  
  pausar(0);
}

float realizarDeposito(float saldo) {
  float valor;

  printf("Digite o valor do deposito: ");
  scanf("%f", &valor);

  if (valor > 0) {
    saldo += valor;
    printf("Deposito realizado!\n");
  } else {
    printf("Valor invalido!\n");
  }

  pausar(1);

  return saldo;
}

float realizarSaque(float saldo) {
  float valor;
  const float LIMITE_DIARIO = 1000.00;

  printf("Valor do saque: ");
  scanf("%f", &valor);

  if (valor > LIMITE_DIARIO) {
    printf("Limite diario excedido!\n");
  } else if(valor > saldo || valor <= 0) {
    printf("Saldo insuficiente ou valor invalido!\n");
  } else {
    saldo -= valor;
    printf("Saque realizado!\n");
  }

  pausar(1);

  return saldo;
}

void exibirExtrato(float saldo, char extrato[][100], int quantidadeTransacoes) {
  printf("\n========================\n");
  printf(" EXTRATO \n");
  printf("========================\n");

  if (quantidadeTransacoes == 0) {
    printf("Nenhuma transação realizada!\n");
    printf("========================\n");

    pausar(0);

    return;
  }

  for (int i = 0; i < quantidadeTransacoes; i++) {
    printf("%s\n", extrato[i]);  
  }

  printf("\n========================\n");
  printf("Saldo atual: R$ %.2f\n", saldo);

  pausar(0);
  
}

int main() {
  int opcao;
  float saldo = 500.00;
  char extrato[10][100];
  int quantidadeTransacoes = 0;

  do {
    system("clear");
    exibirMenu();
    scanf("%d", &opcao);

    while (getchar() != '\n');

    switch(opcao) {
      case 1:
        consultarSaldo(saldo);
        break;
      case 2: {
        float saldoAnterior = saldo;
        saldo = realizarSaque(saldo);

        if (saldo != saldoAnterior && quantidadeTransacoes < 10) {
          sprintf(extrato[quantidadeTransacoes],
            "Saque: -R$ %.2f",
            saldoAnterior - saldo
          );

          quantidadeTransacoes++;
        }

        break;
      }
      case 3: {
        float saldoAnterior = saldo;
        saldo = realizarDeposito(saldo);

        if (saldo != saldoAnterior && quantidadeTransacoes < 10) {
          sprintf(extrato[quantidadeTransacoes],
            "Depósito: +R$ %.2f",
            saldo - saldoAnterior 
          );

          quantidadeTransacoes++;
        }
        break;
      }
      case 4: 
        exibirExtrato(saldo, extrato, quantidadeTransacoes);
        break;
      case 0:
        printf("Saindo...\n");
        break;
      default:
        printf("Opcao Invalida!\n");
        pausar(0);
      }

  } while (opcao != 0);

  printf("Obrigado por usar nosso ATM!");
}

