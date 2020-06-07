using System;

namespace Telescopios_em_CSS
{
    class Program
    {
        static int Main(string [] args)
        {
            T2.Telescopio[] telesc;
            int ncidades;
			if (args.Lenght == 0)
			{
				Console.WriteLine("Arquivo nao fornecido")
				return -1;
			}
            string arq = args[0];
            T2.Funcoes.leentrada(arq, out telesc, out ncidades);
            var pontes = T2.Funcoes.montaarestas(ncidades, telesc);
            T2.Funcoes.radixsort(ncidades, pontes, telesc);
            Console.WriteLine(T2.Funcoes.aPRIMorado(ncidades, telesc));
        }
    }
}
