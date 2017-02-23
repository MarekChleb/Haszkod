#include <iostream>
#include <vector>

#define ENDPOINTS_NUM 1000

using namespace std;

long long V, E, R, C, X;
vector<int> vsize;
vector<int> e_latency;// czas dostepu z data center do danego endpointu

// first = id of the endpoint, second = id of cache server
vector<vector<int>> cache_latency; // czas dostepu z endpointu do
    // cache

vector<vector<pair<int, int>>> endpoint_request;

void read_endpoint(int i) {
    int num;
    scanf("%d", &e_latency[i]);
    scanf("%d", &num);

    cache_latency[i].resize(1000);
    int cache_nr, lat;
    for (int j = 0; j < num; j++) {
        scanf("%d%d", &cache_nr, &lat);
        cache_latency[i][cache_nr] = lat;
    }
}

void read_input() {
    scanf("%lld", &V);
    scanf("%lld", &E);
    scanf("%lld", &R);
    scanf("%lld", &C);
    scanf("%lld", &X);

    vsize.reserve(V);

    for (int i = 0; i < V; i++) {
        scanf("%d", &vsize[i]);
    }

    e_latency.resize(ENDPOINTS_NUM);
    for (int i = 0; i < E; i++) {
        read_endpoint(i);
    }

    endpoint_request.resize(1003);
    int idv, ide, reqnum;
    for (int i = 0; i < R; i++) {
        scanf("%d%d%d", &idv, &ide, &reqnum);
        endpoint_request[ide].push_back(make_pair(reqnum, idv));
    }
}

void sort_endpoints() {
    
}

int main() {
    read_input();
    sort_endpoints();
    for (diosa) {
        sort_video(i);
        sort_cache(i);
        insert_things(i);
    }
    print_output();
    return 0;
}