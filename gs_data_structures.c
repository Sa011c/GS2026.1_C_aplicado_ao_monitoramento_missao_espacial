#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep() - animações

#define MAX_LEITURAS 100

// Definição de cores ANSI para o terminal
#define RESET   "\x1b[0m"
#define VERMELHO "\x1b[31m"
#define AMARELO  "\x1b[33m"
#define LARANJA  "\x1b[38;5;208m" // Código de 256 cores para Laranja
#define VERDE    "\x1b[32m"
#define CIANO    "\x1b[36m"

// Estrutura para armazenar o histórico
typedef struct {
    float temperatura;
    float energia;
    int comunicacao;
} Leitura;

// Protótipos das funções
void exibirMenu();
void animacaoCarregando(char *mensagem);
void analisarDados(float temp, float energ, int com);

int main() {
    Leitura historico[MAX_LEITURAS];
    int totalLeituras = 0;
    int opcao;

    // Dados iniciais simulados (para o caso de o usuário querer analisar sem cadastrar)
    float tempAtual = 25.0, energiaAtual = 100.0;
    int comAtual = 1; // 1 = OK, 0 = Falha

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Inserir dados
                if (totalLeituras < MAX_LEITURAS) {
                    printf("\n--- CADASTRO DE DADOS DOS SENSORES ---\n");
                    printf("Digite a temperatura da nave (C): ");
                    scanf("%f", &tempAtual);
                    printf("Digite a porcentagem de energia (0-100): ");
                    scanf("%f", &energiaAtual);
                    printf("Digite o status da comunicacao (1 para OK / 0 para Falha): ");
                    scanf("%d", &comAtual);

                    // Salva no histórico
                    historico[totalLeituras].temperatura = tempAtual;
                    historico[totalLeituras].energia = energiaAtual;
                    historico[totalLeituras].comunicacao = comAtual;
                    totalLeituras++;

                    animacaoCarregando("Salvando dados nos sistemas de bordo");
                    printf(VERDE "Dados cadastrados com sucesso!\n" RESET);
                } else {
                    printf(VERMELHO "Memoria do historico cheia!\n" RESET);
                }
                break;

            case 2: // Visualizar status atual
                animacaoCarregando("Acessando telemetria atual");
                printf("\n===================================\n");
                printf("       STATUS ATUAL DA MISSAO      \n");
                printf("===================================\n");
                printf("Temperatura: %.2f C\n", tempAtual);
                printf("Energia: %.2f%%\n", energiaAtual);
                printf("Comunicacao: %s\n", comAtual == 1 ? "OPERACIONAL" : "FALHA");
                printf("===================================\n");
                break;

            case 3: // Executar análise (Simulação contínua dos alertas)
                animacaoCarregando("Rodando diagnostico dos sistemas");
                analisarDados(tempAtual, energiaAtual, comAtual);
                break;

            case 4: // Histórico das Leituras
                printf("\n--- HISTORICO DE LEITURAS ---\n");
                if (totalLeituras == 0) {
                    printf("Nenhum dado registrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLeituras; i++) {
                        printf("[%d] Temp: %.1f C | Energia: %.1f%% | Com: %s\n", 
                                i + 1, 
                                historico[i].temperatura, 
                                historico[i].energia, 
                                historico[i].comunicacao == 1 ? "OK" : "FALHA");
                    }
                }
                break;

            case 5: // Encerrar sistema
                printf(CIANO "\nDesconectando dos sistemas da nave... Missao encerrada.\n" RESET);
                break;

            default:
                printf(VERMELHO "Opcao invalida! Tente novamente.\n" RESET);
        }
        
        printf("\nPressione ENTER para continuar...");
        getchar(); // Limpa o buffer
        getchar(); // Aguarda o enter
        system("clear || cls"); // Limpa a tela para a próxima repetição

    } while (opcao != 5);

    return 0;
}

// Função para exibir o menu visual
void exibirMenu() {
    printf(CIANO "=======================================\n");
    printf("     SISTEMA DE MONITORAMENTO ESPACIAL \n");
    printf("=======================================\n" RESET);
    printf("1. Inserir Dados (Sensores)\n");
    printf("2. Visualizar Status Atual\n");
    printf("3. Executar Analise de Alertas\n");
    printf("4. Visualizar Historico de Leituras\n");
    printf("5. Encerrar Sistema\n");
    printf("---------------------------------------\n");
}

// Função para simular uma animação simples de carregamento
void animacaoCarregando(char *mensagem) {
    printf("%s", mensagem);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout); // Força o terminal a exibir o ponto imediatamente
        sleep(1);       // Aguarda 1 segundo
    }
    printf("\n");
}

// Função que analisa os dados e aplica as regras de negócio com as cores solicitadas
void analisarDados(float temp, float energ, int com) {
    int tudoOk = 1;

    printf("\n--- RELATORIO DE ANALISE CRITICA ---\n");

    if (temp > 80) {
        printf(VERMELHO "[ALERTA] Superaquecimento detectado! Temp: %.2f C\n" RESET, temp);
        tudoOk = 0;
    }
    if (energ < 20) {
        printf(AMARELO "[ALERTA] Economia de energia ativada! Nivel: %.2f%%\n" RESET, energ);
        tudoOk = 0;
    }
    if (com == 0) {
        printf(LARANJA "[ALERTA] Falha de comunicacao com a base!\n" RESET);
        tudoOk = 0;
    }

    if (tudoOk) {
        printf(VERDE "[STATUS] Todos os sistemas operando dentro dos limites normais.\n" RESET);
    }
}