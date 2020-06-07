#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "MST.h"
#define earthRadiusKm 6371.0


double deg2rad(double deg) {
    return (deg * M_PI / 180);
}

int distanceEarthKm(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lat2r, lon1r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r-lat1r)/2);
    v = sin((lon2r-lon1r)/2);
    return (int) 2.0 * earthRadiusKm * asin(sqrt(u*u+cos(lat1r)*cos(lat2r)*v*v));
}

void radixsort(int n,caminhos *v,telesc *mapa,int cidades){
    int digitos=5,divisor=1,aux=0,aux2=0,aux3=0,contador[10],base=10;
    caminhos *vetor;
    vetor=(caminhos*)malloc(n*sizeof(*vetor));  //Vetor auxiliar
    while(aux<digitos){
        aux2=0;
        if(aux==4)base=3;   //Controle para evitar loops desnecessarios ja que os termos sao limitados a 20000.
        while(aux2<base){
            contador[aux2]=0;
            aux2++;}
        aux2=0;
        while(aux2<n){      //Conta quantos x%10^n tem
            aux3=(v[aux2].dist/divisor)%10;
            if(aux3==0){        //Ja aloca os que tem %10=0 pra poupar loop
                    vetor[contador[aux3]].dist=v[aux2].dist;
                    vetor[contador[aux3]].a=v[aux2].a;
                    vetor[contador[aux3]].b=v[aux2].b;
            }
            contador[aux3]++;
            aux2++;
        }
        aux2=1;
        while(aux2<base){           //Incrementa os contadores para alocar depois nos locais certos
            contador[aux2]+=contador[aux2-1];
            aux2++;
        }
        aux2=0;
        while(aux2<n){
            aux3=(v[aux2].dist/divisor)%10;     //Aloca cada item num local com base no seu %10^n
            if(aux3!=0){vetor[contador[aux3-1]].dist=v[aux2].dist;
                    vetor[contador[aux3-1]].a=v[aux2].a;
                    vetor[contador[aux3-1]].b=v[aux2].b;
                    contador[aux3-1]++;
            }
            aux2++;
        }
        aux2=0;
        while(aux2<n){
            if(aux!=4)v[aux2]=vetor[aux2];        //Altera o vetor original para o vetor auxiliar
            else{                 //Se for o ultimo digito a ser analisado, aloca cada distancia a sua respectiva
                aux3=vetor[aux2].a;             //cidade, em ordem, deixando todas os vetores de distancias das cidades
                mapa[aux3-1].ordemdistancia[mapa[aux3-1].contador]=vetor[aux2].dist;    //em ordem
                mapa[aux3-1].ordemcidade[mapa[aux3-1].contador]=vetor[aux2].b-1;
                mapa[aux3-1].posicao[vetor[aux2].b-1]=mapa[aux3-1].contador;
                mapa[aux3-1].contador++;
                aux3=vetor[aux2].b;
                mapa[aux3-1].ordemdistancia[mapa[aux3-1].contador]=vetor[aux2].dist;
                mapa[aux3-1].ordemcidade[mapa[aux3-1].contador]=vetor[aux2].a-1;
                mapa[aux3-1].posicao[vetor[aux2].a-1]=mapa[aux3-1].contador;
                mapa[aux3-1].contador++;}
            aux2++;
        }
            if(aux==4){
                aux2=0;
                while(aux2<cidades){
                    mapa[aux2].contador=1;
                    aux2++;
                }
            }
            aux++;divisor*=10;
    }free(vetor);
}


telesc *leitura (char *nomearq,int *cidades){
        FILE *Entrada;
        Entrada=fopen(nomearq,"r");
        if(Entrada==NULL)
			return NULL;
		int aux,aux2;
        fscanf(Entrada,"%d",&aux2);     //Le o numero de cidades
        *cidades=aux2;
        aux=0;
        telesc *mapa;
        mapa=(telesc*)malloc(aux2*sizeof(*mapa));    //Aloca o vetor dinamicamente
        while(aux<aux2){                            //Escaneia todas as distanciass
            fscanf(Entrada,"%lf %lf",&(mapa[aux].lat),&(mapa[aux].longi));
            mapa[aux].ordemcidade=(int*)malloc((aux2)*sizeof(int));
            mapa[aux].ordemdistancia=(int*)malloc((aux2)*sizeof(int));
            mapa[aux].posicao=(int*)malloc((aux2)*sizeof(int));
            mapa[aux].contador=1;               //Inicializa variaveis de controle
            mapa[aux].ordemcidade[0]=aux;
            mapa[aux].ordemdistancia[0]=0;
            mapa[aux].posicao[aux]=0;
            aux++;
        }
        fclose(Entrada);
        return (mapa);      //Retorna o vetor mapa
}

caminhos *montaarestas(int cidades,telesc *mapa){
    int aux=0,aux2,aux3=0;
    int npontes=(cidades*(cidades-1))/2;
    caminhos *ponte;
    ponte=(caminhos*)malloc(npontes*sizeof(*ponte));
    while(aux<cidades){aux2=aux+1;      //Enquanto ha cidades sem pontes
    while(aux2<cidades){if(aux2==cidades)break;     //Faz as pontes com as outras cidades sem pontes
        ponte[aux3].dist=distanceEarthKm(mapa[aux].lat,mapa[aux].longi,mapa[aux2].lat,mapa[aux2].longi);
        ponte[aux3].a=aux+1;                //e coloca num vetor que contem todas as pontes
        ponte[aux3].b=aux2+1;
        aux3++;aux2++;
    }
        aux++;
}
return ponte;
}

int aPRIMorado(int cidades,telesc *mapa){
    int *reserva;
    reserva=(int*)calloc(cidades,sizeof(int));
    reserva[0]=0;                           //Comeca uma arvore com a cidade 0
    int aux=0,aux2,aux3,aux4,aux5,resposta=0;
    while(aux<cidades-1){               //Enquanto ha nos fora da arvore
    while(mapa[0].ordemdistancia[mapa[0].contador]==0)mapa[0].contador++;   //Seleciona o no com a menor distancia
    aux3=0;                                                                           //ate a arvore
    aux4=1;
    aux2=mapa[0].ordemdistancia[mapa[0].contador];
    aux5=mapa[0].ordemcidade[mapa[0].contador];
    while(aux4<=aux){
        while(mapa[reserva[aux4]].ordemdistancia[mapa[reserva[aux4]].contador]==0){
                mapa[reserva[aux4]].contador++;}
        if(mapa[reserva[aux4]].ordemdistancia[mapa[reserva[aux4]].contador]<aux2)
            {aux2=mapa[reserva[aux4]].ordemdistancia[mapa[reserva[aux4]].contador];
             aux5=mapa[reserva[aux4]].ordemcidade[mapa[reserva[aux4]].contador];
             aux3=reserva[aux4];}
        aux4++;
    }
    if(aux2>resposta)resposta=aux2;         //Analisa se essa distancia nova e' maior que as outras para a resposta
    aux2=0;
    while(aux2<=aux){                       //Zera as distancias de todos as cidades da arvore ate a nova cidade e
        mapa[reserva[aux2]].ordemdistancia[mapa[reserva[aux2]].posicao[aux5]]=0;
        mapa[aux5].ordemdistancia[mapa[aux5].posicao[reserva[aux2]]]=0; //da nova cidade a todas as outras da arvore
        aux2++;
    }
    reserva[aux+1]=aux5;        //Coloca a nova cidade na arvore
    aux++;
    mapa[aux3].contador++;

}
free(reserva);
return resposta;    //Retorna a maior distancia utilizada
}

void libera(telesc *mapa){
    free(mapa->ordemcidade);        //Libera a memoria alocada dos vetores de cada cidade
    free(mapa->ordemdistancia);
    free(mapa->posicao);

}
