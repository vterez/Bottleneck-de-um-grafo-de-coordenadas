# Bottleneck-de-um-grafo-de-coordenadas
Dadas coordenadas de pontos na Terra, o programa retorna a maior aresta da árvore geradora mínima do grafo associado, com complexidade O(n), sendo n o número de arestas.

O programa abre um arquivo cujo nome é passado por linha de comando e utiliza o algorimo de Prim para o cálculo de uma Minimum Spanning Tree (MST), mas, ao invés de utilizar heapsort, utiliza o radixsort, pois, para uma entrada cujos dados são limitados superiormente, é possível ordenar em tempo linear. Por fim, o programa retorna a maior aresta da MST.

O arquivo deve ser formado da seguinte forma:
Número de pontos (x)
Para cada uma das x linhas a seguir, devem ser inseridas a latitude e a longitude de um ponto, separadas por espaço.

