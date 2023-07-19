#include <stdio.h>

int main()
{
    int op, direcao, qtdV, maxA, origem, destino, maisAresta, ponderado, pesoAresta = 1;
    
    printf("-----Matriz de Adjacencia-----\n");
    printf("0 - Nao Direcional \n");
    printf("1 - Direcional \n");
    printf("Escolha qual tipo do seu grafo: \n");
    scanf("%d", &direcao);

    printf("------------------------------\n");
    printf("0 - Nao ponderado \n");
    printf("1 - Ponderado \n");
    printf("Escolha qual tipo do seu grafo: \n");
    scanf("%d", &ponderado);

    printf("------------------------------\n");
    printf("Digite a quantidade de Vertices: ");    
    scanf("%d", &qtdV);

    int matriz[qtdV][qtdV], matrizComplementar[qtdV][qtdV], matrizSubjacente[qtdV][qtdV], graus[qtdV], grausDirecional[qtdV][2];

    if(!direcao)
        maxA = qtdV * (qtdV-1)/2;
    else
        maxA = qtdV * (qtdV-1); 

    //atribuindo valores iniciais a todas as posições das matrizes
    for(int i = 0; i < qtdV; i++){
        for(int j = 0; j < qtdV; j++){
            matriz[i][j] = 0;
            matrizSubjacente[i][j] = 0;
            if(i == j){
                matrizComplementar[i][j] = 0;
            } else {
                matrizComplementar[i][j] = 1;
            }
        }
    }
     //atribuindo 0 a todas as posições da matriz e vetor de graus
    for(int i = 0; i < qtdV; i++){
        for(int j = 0; j < 2; j++){
            grausDirecional[i][j] = 0;
        }
        graus[i] = 0;
    }

    //entrada das arestas de acordo com origem e destino
    int i = 0, tamanho = 0;
    do{        
        printf("Digite a origem e destino da aresta %d (exemplo: 1 2): ", i);
        scanf("%d %d", &origem, &destino);
        if(ponderado){
            printf("Digite o peso da aresta: ");
            scanf("%d", &pesoAresta);
        }
        printf("Deseja inserir outra aresta? (1-Sim | 0-Nao)\n");
        scanf("%d", &maisAresta);

        if (origem > qtdV || destino > qtdV || origem < 0 || destino < 0 || i > maxA){
            printf("Aresta inválida!\n");
            i--;
        }else{            
            matriz[origem][destino] = pesoAresta;
            matrizComplementar[origem][destino] = 0;
            matrizSubjacente[origem][destino] = pesoAresta;
            matrizSubjacente[destino][origem] = pesoAresta;
                
            if (!direcao){
                matriz[destino][origem] = pesoAresta;
                matrizComplementar[destino][origem] = 0;
                graus[origem]++;
                graus[destino]++;
            }else{
                grausDirecional[origem][0]++;
                grausDirecional[destino][1]++;
            }
        } 
        i++;
        tamanho++;
    }while(maisAresta == 1);
    


    do{
        printf("------------------------------\n");
        printf("Informe a opcao desejada:\n");
        printf("1- Apresentar a matriz resultada do grafo\n");
        printf("2- Apresentar a ordem e o tamanho do grafo\n");
        printf("3- Apresentar a vizinhanca e grau de todos os vertices\n");
        printf("4- Apresentar a matriz de adjacencia do grafo complementar\n");
        printf("5- Apresentar a matriz de adjacencia do grafo subjacente (apenas para grafos direcionados)\n");
        printf("0- Sair\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                //Exibindo a matriz resultada do grafo
                printf("-----Matriz de Adjacencia-----\n");
                for(int i = 0; i < qtdV; i++){
                    printf("   ");
                    for(int j = 0; j < qtdV; j++){
                    printf("%4d ", matriz[i][j]);
                    }
                printf("\n");
                }
                break;

            case 2:
                //Exibindo o tamanho e ordem do grafo
                printf("------------------------------\n");
                printf("O seu grafo tem ordem %d e tamanho %d. \n", qtdV, tamanho);
                break;

            case 3:
                //Exibindo os graus e vizinhaca dos vertices
                printf("------------------------------\n");
                printf("Vizinhos dos vertices: \n");
                for(int i = 0; i < qtdV; i++){
                    printf("Vertice %d:", i);
                    for(int j = 0; j < qtdV; j++){
                        if(i != j && matriz[i][j] == 1){
                            printf(" %d",j);
                        }
                        if(direcao && matriz[j][i] == 1){
                            printf(" %d",j);
                        }
                    }
                printf("\n");
                }

                printf("Graus dos vertices: \n");
                for (int i = 0; i < qtdV; i++){
                    if (direcao){
                        printf("Vertice %d: Entrada: %d; Saida: %d", i, grausDirecional[i][1], grausDirecional[i][0]);
                    }else{
                        printf("Vertice %d: %d", i, graus[i]);
                    }
                    printf("\n");
                }
                break;

            case 4:
                //Exibindo a matriz resultada do grafo complementar
                printf("-----Matriz de Adjacencia Complementar-----\n");
                for(int i = 0; i < qtdV; i++){
                    printf("   ");
                    for(int j = 0; j < qtdV; j++){
                    printf("%4d ", matrizComplementar[i][j]);
                    }
                printf("\n");
                }
                break;

            case 5:
                //Exibindo a matriz de adjacencia do grafo subjacente (apenas para grafos direcionados)
                if (direcao){
                    printf("-----Matriz de Adjacencia do grafo subjacente-----\n");
                    for(int i = 0; i < qtdV; i++){
                        printf("   ");
                        for(int j = 0; j < qtdV; j++){
                            printf("%4d ", matrizSubjacente[i][j]);
                        }
                        printf("\n");
                    }
                    }else{
                        printf("APENAS PARA GRAFOS DIRECIONADOS!!!\n");
                    }
                break;

            case 0:
                
                break;
        }
    }while(op != 0);

    return 0;
}