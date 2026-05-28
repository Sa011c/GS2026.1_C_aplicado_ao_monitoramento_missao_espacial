# GS2026.1_C_aplicado_ao_monitoramento_missao_espacial
O sistema monitorar temperatura da nave; nível de energia; comunicação; status operacional da missão.


```
floxograma 

    A[Início] --> B[Inicializar Variáveis e Vetor de Histórico]

    B --> C[Exibir Menu Interativo]
    C --> D[Ler Opção do Usuário]

    D --> E{Escolha da Opção}

    # Opção 1
    E -->|Opção 1| F[Inserir Dados]
    F --> G[Salvar no Vetor]
    G --> H[Limpar Tela]
    H --> C

    # Opção 2
    E -->|Opção 2| I[Exibir Status Atual]
    I --> J[Limpar Tela]
    J --> C

    # Opção 3
    E -->|Opção 3| K[Executar Análise<br/>If / Else + Aplicação de Cores]
    K --> L[Limpar Tela]
    L --> C

    # Opção 4
    E -->|Opção 4| M[Percorrer Histórico<br/>Loop For]
    M --> N[Limpar Tela]
    N --> C

    # Opção 5
    E -->|Opção 5| O[Encerrar Sistema]

    O --> P[Fim do Programa]

```
