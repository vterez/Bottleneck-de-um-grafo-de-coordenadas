typedef struct {double lat;     //latitude da cidade
                double longi;   //longitude da cidade
                int *ordemdistancia;    //vetor com as distancias em ordem em relacao as outras cidades
                int *ordemcidade;       //vetor com as cidades na mesma ordem do vetor de distancias
                int *posicao;           //vetor com a posicao de cada cidade no vetor de distancias/cidades
                int contador;           //auxiliar para contabilizar cidades que ja estao ligadas
                    } telesc;    //struct para armazenar dados das cidades

typedef struct {int dist;       //distancia entre as cidades *a* e *b*
                int a;          //codigo cidade a
                int b;          //codigo cidade b
                    } caminhos;     //vetor com as 'pontes' entre as cidades

double deg2rad(double deg);
void radixsort(int n,caminhos *v,telesc *mapa,int cidades);
int distanceEarthKm(double lat1d, double lon1d, double lat2d, double lon2d);
telesc *leitura (char *nomearq,int *cidades);
caminhos *montaarestas(int cidades,telesc *mapa);
void libera(telesc *mapa);
int aPRIMorado(int cidades,telesc *mapa);
