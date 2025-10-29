#include <stdio.h>
#include <string.h>
#include <locale.h>

/*
Atributos:
1 - População (int)           -> maior vence
2 - Área (float, km²)         -> maior vence
3 - PIB (float, bilhões R$)   -> maior vence
4 - Pontos turísticos (int)   -> maior vence
5 - Densidade demográfica     -> MENOR vence
*/

typedef struct {
    char  pais[64];    // Nome do país (apenas para exibição)
    int   populacao;   // habitantes
    float area;        // km²
    float pib;         // bilhões de R$
    int   pontos;      // número de pontos turísticos
    float densidade;   // hab/km² (derivado: populacao / area)
} Carta;

static void limparEntrada(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static const char* nomeAtributo(int opc) {
    switch (opc) {
        case 1: return "População";
        case 2: return "Área (km²)";
        case 3: return "PIB (bilhões de R$)";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica (hab/km²)";
        default: return "Desconhecido";
    }
}

static float valorAtributo(const Carta* c, int opc) {
    switch (opc) {
        case 1: return (float)c->populacao;
        case 2: return c->area;
        case 3: return c->pib;
        case 4: return (float)c->pontos;
        case 5: return c->densidade;
        default: return 0.0f;
    }
}

static void exibirCarta(const Carta* c) {
    printf("País: %s | População: %d | Área: %.2f km² | PIB: %.2f bi R$ | Pontos: %d | Densidade: %.2f hab/km²\n",
           c->pais, c->populacao, c->area, c->pib, c->pontos, c->densidade);
}

static void calcularDerivados(Carta* c) {
    // Densidade: tratar área inválida para evitar divisão por zero
    c->densidade = (c->area > 0.0f) ? (c->populacao / c->area) : 0.0f;
}

static void mostrarMenuPrimeiro(void) {
    printf("\n==== Escolha o 1º atributo ====\n");
    printf("1 - População \n");
    printf("2 - Área\n");
    printf("3 - PIB (bilhões de R$)\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica\n");
    printf("Opção: ");
}

static void mostrarMenuSegundo(int exclui) {
    printf("\n==== Escolha o 2º atributo (diferente do 1º) ====\n");
    // Menu dinâmico: não exibe a opção já escolhida
    for (int i = 1; i <= 5; ++i) {
        if (i == exclui) continue;
        switch (i) {
            case 1: printf("1 - População \n"); break;
            case 2: printf("2 - Área \n"); break;
            case 3: printf("3 - PIB (bilhões de R$)\n"); break;
            case 4: printf("4 - Pontos Turísticos \n"); break;
            case 5: printf("5 - Densidade Demográfica \n"); break;
        }
    }
    printf("Opção: ");
}

static int lerOpcaoMenuPrimeiro(void) {
    int opc;
    while (1) {
        mostrarMenuPrimeiro();
        if (scanf("%d", &opc) != 1) {
            printf("Entrada inválida! Digite um número de 1 a 5.\n");
            limparEntrada();
            continue;
        }
        if (opc < 1 || opc > 5) {
            printf("Opção inexistente! Tente novamente.\n");
            continue;
        }
        limparEntrada();
        return opc;
    }
}

static int lerOpcaoMenuSegundo(int exclui) {
    int opc;
    while (1) {
        mostrarMenuSegundo(exclui);
        if (scanf("%d", &opc) != 1) {
            printf("Entrada inválida! Digite um número de 1 a 5 (diferente de %d).\n", exclui);
            limparEntrada();
            continue;
        }
        if (opc < 1 || opc > 5 || opc == exclui) {
            printf("Opção inválida! Não é permitido repetir o atributo escolhido (%d).\n", exclui);
            continue;
        }
        limparEntrada();
        return opc;
    }
}

int main(void) {
    setlocale(LC_ALL, "");

    // Cartas pré-cadastradas (substitua pelos seus dados ou pelo cadastro anterior, se quiser)
    Carta c1 = {"Brasil", 12325000, 1521.11f, 699.28f, 50, 0.0f};
    Carta c2 = {"Argentina",  6748000, 1200.25f, 300.50f, 30, 0.0f};

    calcularDerivados(&c1);
    calcularDerivados(&c2);

    printf("=== Super Trunfo – Nível Mestre ===\n");
    printf("Cartas carregadas:\n");
    exibirCarta(&c1);
    exibirCarta(&c2);

    // 1) Escolha do primeiro atributo
    int attr1 = lerOpcaoMenuPrimeiro();

    // 2) Escolha do segundo atributo (menu dinâmico: sem repetir o primeiro)
    int attr2 = lerOpcaoMenuSegundo(attr1);

    // 3) Comparações individuais
    float c1_v1 = valorAtributo(&c1, attr1);
    float c2_v1 = valorAtributo(&c2, attr1);
    float c1_v2 = valorAtributo(&c1, attr2);
    float c2_v2 = valorAtributo(&c2, attr2);

    // Para densidade (5), menor vence; demais, maior vence
    int menorVence1 = (attr1 == 5);
    int menorVence2 = (attr2 == 5);

    // Resultados individuais (1 se Carta 1 vence, 0 se Carta 2 vence, -1 empate)
    int r1 = (c1_v1 == c2_v1) ? -1 : (menorVence1 ? (c1_v1 < c2_v1) : (c1_v1 > c2_v1));
    int r2 = (c1_v2 == c2_v2) ? -1 : (menorVence2 ? (c1_v2 < c2_v2) : (c1_v2 > c2_v2));

    // 4) Soma dos atributos escolhidos
    float soma1 = c1_v1 + c1_v2;
    float soma2 = c2_v1 + c2_v2;

    // 5) Exibição clara do resultado
    printf("\n===== Resultado da Rodada =====\n");
    printf("Cartas: %s  VS  %s\n", c1.pais, c2.pais);

    // Atributo 1
    printf("\nAtributo 1: %s\n", nomeAtributo(attr1));
    switch (attr1) {
        case 1: printf("%s: %d | %s: %d\n", c1.pais, c1.populacao, c2.pais, c2.populacao); break;
        case 2: printf("%s: %.2f km² | %s: %.2f km²\n", c1.pais, c1.area, c2.pais, c2.area); break;
        case 3: printf("%s: %.2f bi R$ | %s: %.2f bi R$\n", c1.pais, c1.pib, c2.pais, c2.pib); break;
        case 4: printf("%s: %d | %s: %d\n", c1.pais, c1.pontos, c2.pais, c2.pontos); break;
        case 5: printf("%s: %.2f hab/km² | %s: %.2f hab/km²\n", c1.pais, c1.densidade, c2.pais, c2.densidade); break;
        default: break;
    }
    if (r1 == -1) {
        printf("Resultado do Atributo 1: Empate!\n");
    } else if (r1 == 1) {
        printf("Resultado do Atributo 1: %s venceu!\n", c1.pais);
    } else {
        printf("Resultado do Atributo 1: %s venceu!\n", c2.pais);
    }

    // Atributo 2
    printf("\nAtributo 2: %s\n", nomeAtributo(attr2));
    switch (attr2) {
        case 1: printf("%s: %d | %s: %d\n", c1.pais, c1.populacao, c2.pais, c2.populacao); break;
        case 2: printf("%s: %.2f km² | %s: %.2f km²\n", c1.pais, c1.area, c2.pais, c2.area); break;
        case 3: printf("%s: %.2f bi R$ | %s: %.2f bi R$\n", c1.pais, c1.pib, c2.pais, c2.pib); break;
        case 4: printf("%s: %d | %s: %d\n", c1.pais, c1.pontos, c2.pais, c2.pontos); break;
        case 5: printf("%s: %.2f hab/km² | %s: %.2f hab/km²\n", c1.pais, c1.densidade, c2.pais, c2.densidade); break;
        default: break;
    }
    if (r2 == -1) {
        printf("Resultado do Atributo 2: Empate!\n");
    } else if (r2 == 1) {
        printf("Resultado do Atributo 2: %s venceu!\n", c1.pais);
    } else {
        printf("Resultado do Atributo 2: %s venceu!\n", c2.pais);
    }

    // Somas
    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f\n", c1.pais, soma1);
    printf("%s: %.2f\n", c2.pais, soma2);

    if (soma1 == soma2) {
        printf("Resultado final: Empate!\n");
    } else {
        // if-else aninhado: decide vencedor final
        if (soma1 > soma2) {
            printf("Resultado final: %s venceu a rodada!\n", c1.pais);
        } else {
            printf("Resultado final: %s venceu a rodada!\n", c2.pais);
        }
    }

    // Observações (robustez mínima para dados inválidos das cartas)
    if (c1.area <= 0.0f || c2.area <= 0.0f) {
        printf("\n[Aviso] Área não positiva detectada em alguma carta; densidade foi considerada 0 para evitar divisão por zero.\n");
    }

    return 0;
}