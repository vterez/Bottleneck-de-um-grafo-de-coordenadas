using System;

namespace T2
{
    class Telescopio
    {
        public double Longitude
            { get; set;}
        public double Latitude
            { get; set; }
        public int[] ordemdistancia
            { get; set; }
        public int[] ordemcidade
            { get; set; }
        public int[] posicao
            { get; set; }
        public int contador
            { get; set; }
        public Telescopio(double lati,double longi,int ncidades,int numposi)
        {
            Latitude=lati;
            Longitude = longi;
            posicao = new int[ncidades];
            ordemcidade = new int[ncidades];
            ordemdistancia = new int[ncidades];
            contador = 1;
            ordemcidade[0] = numposi;
            ordemdistancia[0] = 0;
            posicao[numposi] = 0;
        }
    }
    class Caminhos
    {
        public int a { get; set; }
        public int b { get; set; }
        public int dist { get; set; }
        public Caminhos(int ca,int cb)
        {
            a = ca;
            b = cb;
            dist = 0;
        }
        public Caminhos(Caminhos x)
        {
            a = x.a;
            b = x.b;
            dist = x.dist;
        }

    }
    static class Funcoes
    {
        static public void leentrada(string arq,out Telescopio[] telesc, out int ncidades)
        {
            System.IO.StreamReader file = new System.IO.StreamReader(arq);
            string line;
            int contador = 0;
            line = file.ReadLine();
            ncidades = Int32.Parse(line);
            telesc = new Telescopio[ncidades];
            while((line=file.ReadLine()) != null)
            {
                string[] split = line.Split(' ');
                telesc[contador] = new Telescopio(double.Parse(split[0], System.Globalization.CultureInfo.InvariantCulture),double.Parse(split[1],System.Globalization.CultureInfo.InvariantCulture),ncidades,contador);
                contador++;
            }
        }

        static public double deg2rad(double deg)
        {
            return 3.1416 * deg / 180;
        }
        static public int Distance(double lat1d,double lon1d,double lat2d,double lon2d)
        {
            double lat1r, lat2r, lon1r, lon2r, u, v;
            lat1r = deg2rad(lat1d);
            lon1r = deg2rad(lon1d);
            lat2r = deg2rad(lat2d);
            lon2r = deg2rad(lon2d);
            u = Math.Sin((lat2r - lat1r) / 2);
            v = Math.Sin((lon2r - lon1r) / 2);
            return (int)(2.0 * 6371.2 * Math.Asin(Math.Sqrt(u * u + Math.Cos(lat1r) * Math.Cos(lat2r) * v * v)));
        }
        static public Caminhos[] montaarestas(int ncidades,Telescopio[] telesc)
        {
            int aux = 0, aux2, aux3 = 0;
            int npontes = (ncidades * (ncidades - 1)) / 2;
            var pontes = new Caminhos[npontes];
            while(aux<ncidades)
            {
                aux2 = aux + 1;
                while(aux2<ncidades)
                {
                    pontes[aux3] = new Caminhos(aux, aux2);
                    pontes[aux3].dist = Distance(telesc[aux].Latitude, telesc[aux].Longitude, telesc[aux2].Latitude, telesc[aux2].Longitude);
                    aux3++;aux2++;
                }
                aux++;
            }
            return pontes;
        }
        static public void radixsort(int ncidades, Caminhos[] v, Telescopio[] mapa)
        {
            int npontes = (ncidades * (ncidades - 1)) / 2;
            int digitos = 5, divisor = 1, aux = 0, aux2 = 0, aux3 = 0, basenum = 10, aux4;
            int[] contador = new int[basenum];
            while(aux<digitos)
            {
                Caminhos[] vetor = new Caminhos[npontes];
                aux2 = 0;
                if (aux == 4) basenum = 3;
                while(aux2<basenum)
                {
                    contador[aux2] = 0;
                    aux2++;
                }
                aux2 = 0;
                while(aux2<npontes)
                {
                    aux3 = (v[aux2].dist / divisor) % 10;
                    if(aux3==0)
                    {
                        vetor[contador[0]] = new Caminhos(v[aux2]);
                    }
                    contador[aux3]++;
                    aux2++;
                }
                aux2 = 1;
                while(aux2<basenum)
                {
                    contador[aux2] += contador[aux2 - 1];
                    aux2++;
                }
                aux2 = 0;
                while(aux2<npontes)
                {
                    aux3 = (v[aux2].dist / divisor) % 10;
                    if(aux3!=0)
                    {
                        vetor[contador[aux3 - 1]] = new Caminhos(v[aux2]);
                        contador[aux3 - 1]++;
                    }
                    aux2++;
                }
                aux2 = 0;
                while(aux2<npontes)
                {
                    if (aux != 4)
                        v[aux2] = vetor[aux2];
                    else
                    {
                        aux3 = vetor[aux2].a;
                        aux4 = mapa[aux3].contador;
                        mapa[aux3].ordemdistancia[aux4] = vetor[aux2].dist;
                        mapa[aux3].ordemcidade[aux4] = vetor[aux2].b;
                        mapa[aux3].posicao[vetor[aux2].b] = aux4;
                        mapa[aux3].contador++;
                        aux3 = vetor[aux2].b;
                        aux4 = mapa[aux3].contador;
                        mapa[aux3].ordemdistancia[aux4] = vetor[aux2].dist;
                        mapa[aux3].ordemcidade[aux4] = vetor[aux2].a;
                        mapa[aux3].posicao[vetor[aux2].a] = aux4;
                        mapa[aux3].contador++;
                    }
                    aux2++;
                }
                if(aux==4)
                {
                    aux2 = 0;
                    while(aux2<ncidades)
                    {
                        mapa[aux2].contador = 1;
                        aux2++;
                    }
                }
                aux++;
                divisor *= 10;
            }
        }
        static public int aPRIMorado(int ncidades,Telescopio[] mapa)
        {
            int[] reserva = new int[ncidades];
            reserva[0] = 0;
            int aux = 0, aux2, aux3, aux4, aux5, aux6, resposta = 0;
            while(aux<ncidades-1)
            {
                while(mapa[0].ordemdistancia[mapa[0].contador]==0)
                {
                    mapa[0].contador++;
                }
                aux3 = 0;
                aux4 = 1;
                aux2 = mapa[0].ordemdistancia[mapa[0].contador];
                aux5 = mapa[0].ordemcidade[mapa[0].contador];
                while(aux4<=aux)
                {
                    aux6 = reserva[aux4];
                    while(mapa[aux6].ordemdistancia[mapa[aux6].contador]==0)
                    {
                        mapa[aux6].contador++;
                    }
                    if(mapa[aux6].ordemdistancia[mapa[aux6].contador]<aux2)
                    {
                        aux2 = mapa[aux6].ordemdistancia[mapa[aux6].contador];
                        aux5 = mapa[aux6].ordemcidade[mapa[aux6].contador];
                        aux3 = reserva[aux4];
                    }
                    aux4++;
                }
                if (aux2 > resposta)
                    resposta = aux2;
                aux2 = 0;
                while(aux2<=aux)
                {
                    aux6 = reserva[aux2];
                    mapa[aux6].ordemdistancia[mapa[aux6].posicao[aux5]] = 0;
                    mapa[aux5].ordemdistancia[mapa[aux5].posicao[reserva[aux2]]] = 0;
                    aux2++;
                }
                reserva[aux + 1] = aux5;
                aux++;
                mapa[aux3].contador++;
            }
            return resposta;
        }
    }
}