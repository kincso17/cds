//Djikstra módszer egy tetszőleges csomópontból az összes többibe
//való minimális távolság kiszámításához
#include <iostream>
using namespace std;
#include <limits.h>

// csomópontok száma
#define V 9


// függvény a legrövidebb út kiszámítására
// egy még meg nem látogatott csúcsba
int minDistance(int dist[], bool sptSet[])
{

    // inicializálás végtelen értékre
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
            }

    return min_index;
}

// megoldás kiírása
void printSolution(int dist[])
{
    cout <<"Tavolsag a kezdoponttol" << endl;
    for (int i = 0; i < V; i++)
        cout  << i << " : " << dist[i] << endl;
}

// legrovidebb utak kiszamitasa
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // a legrovidebb tavolsagokat fogja tarolni,
    //a forrastol az i. csomópontig

    bool sptSet[V]; // bejárt csomópontok mátrixa
    //sptSet[i] igaz lesz, ha i csp. ra ki lett számítva a legrövidebb út

    // kezdetben minden távolság végtelen és
    //egyik csomópontra sincs még kiszámítva az út
    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // src - src távolság mindig 0 lesz
    dist[src] = 0;

    // minden csomópontra a legrövidebb út kiszámítása
    for (int count = 0; count < V - 1; count++) {
        // legközelebbi, még be nem járt csúcs megkeresése
        //kezdetben ez mindig a src lesz, mivel annak a távolsága 0
        int u = minDistance(dist, sptSet);

        // meglátogatott csúcs jelölése
        sptSet[u] = true;

        // meglátogatott csúcs szomszédaihoz vezető legrövidebb út frissítése,
        // ha szükséges
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            // u= 1, v = 2 dist[u] = 0, dist
            // dist[0, 2, 5]
            // sptSET [I, I, H]
            if (!sptSet[v] && graph[u][v] > 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // megoldás kiírása
    printSolution(dist);
}

// driver program to test above function
int main()
{

    /* Let us create the example graph discussed above */
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstra(graph, 0);
    return 0;
}
