#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*Implementação do "OxeIfood" utilizando dijkstra em ambientes simulados
mini-documentação:
- Assim que o menu carregar voce ira selecionar o que deseja que o programa faça dentro das opções que ele da, cujo essas opções são:
1- Ao digitar o 1 irá adicionar o mapa de restaurantes, onde voce ira adicionar cada restaurante por nome e bairro e respeitando a quantidade minima de restaurantes que é de 2(DOIS)
2 - Ao digitar o 2 irá imprimir o seu mapa completo com todos os menores caminhos partindo de todos restaurantes para todos.
3 - Ao digitar o 3 remove um caminho caso esteja interditado
4- Ao digitar o 4 diz o melhor caminho da sua atual localização para o seu destino
0 - Ao digitar o 0 , ele encerra o programa.
*/

//pontos a serem implementados
//1 -  melhor visualização de todos os caminhos(tentar gerar um arquivo)
//2 - imprimir somente a rota que o usuario quer
//3- interface mais simples com o usuario
///Declaração de variaveis globais para facilitar
typedef struct
{
    int idprime;
    char nome[50];
    char bairro[50];
}nodes;
nodes vetor_restaurante[20]; //se alocar dinamicamente , qual tipo volta?
int destino, origem, vertices = 0;
int custo, *custos = NULL;
///IMPLEMENTANDO ATRAVES DE UMA MATRIZ DE ADJACENCIA
void dijkstra(int vertices,int origem,int destino,int *custos)
{
	int i,v, cont = 0;
	int *ant, *tmp;
	int *conhece;     /* vertices para os quais se conhece o caminho minimo */
	double min;
	double dist[vertices]; /* vetor com os custos dos caminhos */


	/* aloca as linhas da matriz */

	ant = calloc (vertices, sizeof(int *));
	tmp = calloc (vertices, sizeof(int *));
	if (ant == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	}

	conhece = calloc (vertices, sizeof(int *));
	if (conhece == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	}

	for (i = 0; i < vertices; i++) {
		if (custos[(origem - 1) * vertices + i] !=- 1) {
			ant[i] = origem - 1;
			dist[i] = custos[(origem-1)*vertices+i];
		}
		else {
			ant[i]= -1;
			dist[i] = HUGE_VAL;
		}
		conhece[i]=0;
	}
	conhece[origem-1] = 1;
	dist[origem-1] = 0;

	/* Laco principal */
	do {

		/* Encontrando o vertice que deve entrar em conhece */
		min = HUGE_VAL; //SE dist i for menor que o HUGO_VAL/INFINITE entao o v recebe i
		for (i=0;i<vertices;i++)
			if (!conhece[i])
				if (dist[i]>=0 && dist[i]<min) {
					min=dist[i];
          v=i;
				}

		/* Calculando as distancias dos novos vizinhos de conhece */
		if (min != HUGE_VAL && v != destino - 1) {
			conhece[v] = 1;
			for (i = 0; i < vertices; i++)
				if (!conhece[i]) {
					if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
					   	dist[i] = dist[v] + custos[v*vertices+i];
						ant[i] =v;
				   	}
        		}
		}
	} while (v != destino - 1 && min != HUGE_VAL);

	/* Mostra o Resultado da busca */
	printf("\tDo restaurante %d para o restaurante %d: \t", origem, destino);
	if (min == HUGE_VAL) {
		printf("Nao Existe\n");
		printf("\tDistancia: \t- \n");
	}
	else {
		i = destino;
		i = ant[i-1];
		while (i != -1) {
			tmp[cont] = i+1;
			cont++;
			i = ant[i];
		}

		for (i = cont; i > 0 ; i--) {
			printf("%d -> ", tmp[i-1]);
		}
		printf("%d", destino);

		printf("\n\tCusto:  %d\n",(int) dist[destino-1]);
	}
}

void cabecalho()
{
	printf("Oche FOOD!\n");
	printf("Menu:\n");
	printf("\t 1 - Adicionar o seu mapa de restaurantes\n"
	  	   "\t 2 - Imprimir todos os restaurantes que voce adicionou\n"
         "\t 3 - Remover um caminho para um restaurante\n"
         "\t 4 - Melhor caminho da sua atual localizacao para o destino\n"
	  	   "\t 0 - Sair do programa\n");
	printf(">>> ");

}

void add()
{   
    /*nessa parte do adicionar eu precisava adicionar informações junto com o vertice entao criei um tipo complexo NODES 
    e depois criei uma variavel chamada vetor_restaurantes aonde guarda as seguintes informações
    
    o usuario vai me dar a quantidade de vertices, para cada vertice que for adicionado eu criei um contador para 
    atribuir um id para cada restaurante utizilizando a entrada dos vertices como variavel global
        
    */
	int i, j,aux;
  //do{
		printf("\nInforme a quantidade de restaurantes (no minimo 2 ): ");
		scanf("%d",&vertices);
    for(aux=1;aux<=vertices;aux++)
    {
      vetor_restaurante[aux].idprime = aux;
      printf("\nInforme o nome do restaurante: ");
      scanf("%s",vetor_restaurante[aux].nome);
      strcpy(vetor_restaurante->nome,vetor_restaurante[aux].nome);
      printf("\nInforme o bairro do restaurante: ");
      scanf("%s",vetor_restaurante[aux].bairro);
      strcpy(vetor_restaurante->bairro,vetor_restaurante[aux].bairro);

      printf("%d\t%s\t%s\n",vetor_restaurante[aux].idprime,vetor_restaurante->nome,vetor_restaurante->bairro);
      fflush(stdin);
    }
	//} while (vertices < 2 );
    ///CUSTOS EH UM PONTEIRO QUE RECEBE NULL
	if (!custos)//se custos esta preenchido entao libere custos
    {
        free(custos);
    }
	custos = (int *) malloc(sizeof(int)*vertices*vertices);
	for (i = 0; i <= vertices * vertices; i++)
		custos[i] = -1;

	printf("Entre com os custos entre eles:\n");
	do {
		do {
			printf("ID do restaurante de saida entre 1 e %d ou '0' para sair): ", vertices);
			scanf("%d",&origem);
		} while (origem < 0 || origem > vertices);

		if (origem) {
			do {
				printf("ID do restaurante de chegada entre 1 e %d, menos %d): ", vertices, origem);
				scanf("%d", &destino);
			} while (destino < 1 || destino > vertices || destino == origem);

			do {
				printf("Distancia do restaurante %d para o restaurante %d: ",
						origem, destino);
				scanf("%d",&custo);
			} while (custo < 0);

			custos[(origem-1) * vertices + destino - 1] = custo;
		}

	} while (origem);
}

void procurar()
{
	int i, j;

	printf("Mapa completo: \n");

	for (i = 1; i <= vertices; i++) {
		for (j = 1; j <= vertices; j++)
			dijkstra(vertices, i,j, custos);
		printf("\n");
	}
}

void remover()
{


}


int main(void) {    
	int i, j;
	char opcao, l[50],e;
  cabecalho();
  do {
    fflush(stdin);
    scanf("%c", &opcao);
    if (opcao == 49) {
			add();
      cabecalho();
		}
    if ((opcao == 50) && (vertices > 0) )
    {
      procurar();
      cabecalho();
		}
    if((opcao == 51) && (vertices > 0) )
    {
      remover();
      cabecalho();
    }
    if((opcao == 52) && (vertices > 0) )
    {
      ///////
      printf("\nDigite os IDS origem e destino do caminho\n");
      do {
        printf("ID saida (entre 1 e %d): ",vertices);
        scanf("%d",&origem);
      } while (origem<1 || origem>vertices);

      do {
        printf("ID destino (entre 1 e %d, menos %d): ",vertices,origem);
        scanf("%d",&destino);
      } while (destino<1 || destino>vertices || destino==origem);
      dijkstra(vertices,origem,destino,custos);
      cabecalho();
        //////
    }

  }while (opcao != 48);

	return 0;
}
