#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MST.h"

int main(int argc,char **argv)
{
//Bloco de variaveis auxiliares
int cidades,npontes,aux=0,resposta;
char *nome;
if(argc<2)
{
    printf("Nome do arquivo nao fornecido\n");
    return -1;
}
nome=(char*)malloc(strlen(argv[1])+1);
strcpy(nome,argv[1]);
telesc *mapa;
caminhos *ponte;

//Bloco de leitura e alocacao das variaveis
mapa=leitura(nome,&cidades);
if (mapa==NULL)
{
	printf("Arquivo nao encontrado\n");
	return -1;
}
npontes=(cidades*(cidades-1))/2;
ponte=montaarestas(cidades,&*mapa);

//Bloco de execucao do algoritmo
radixsort(npontes,&*ponte,&*mapa,cidades);
resposta=aPRIMorado(cidades,&*mapa);

//Bloco de liberacao de memoria alocada
while(aux<cidades){
    libera(&mapa[aux]);
    aux++;
}
free(mapa);
free(ponte);
free(nome);


printf("%d\n",resposta);
    return 0;
}
