#include <iostream>
#include <vector>
#include <algorithm>
#include<set>

#define ENDPOINTS_NUM 1000

using namespace std;

long long V, E, R, C, X;
vector<int> vsize;
vector<int> e_latency;// czas dostepu z data center do danego endpointu

// first = id of the endpoint, second = id of cache server
vector<vector<pair<int, int>>> cache_latency; // czas dostepu z endpointu do
// cache

vector<set<int>> cache_videos;
vector<long long> cache_space_left;

vector<vector<pair<int, int>>> endpoint_request;

vector<pair<int, int>> sorted_endpoints; //first - priorytet wg. algorytmu,
// second - numer endpointu

void read_endpoint(int i) {
    int num;
    scanf("%d", &e_latency[i]);
    scanf("%d", &num);

    int cache_nr, lat;
    for (int j = 0; j < num; j++) {
        scanf("%d%d", &cache_nr, &lat);
        cache_latency[i].push_back(make_pair(lat, cache_nr));
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
    cache_latency.resize(ENDPOINTS_NUM);
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
    cache_videos.resize(C);
    cache_space_left.resize(C);

    for (int i = 0; i < C; i++) {
        cache_space_left[i] = X;
    }
}

void sort_endpoints() {

    long priority = 0;

    for (int e = 0; e < E; ++e) {
        for (int i = 0; i < endpoint_request[e].size(); ++i) {
            priority += endpoint_request[e][i].first;

        }
        for (int i = 0; i < cache_latency[e].size(); ++i) {
            priority -= X * 1 / cache_latency[e][i].first;
        }
        sorted_endpoints.push_back(make_pair(priority, e));
        priority = 0;
    }
    sort(sorted_endpoints.begin(), sorted_endpoints.end());
    reverse(sorted_endpoints.begin(), sorted_endpoints.end());

}

void sort_videos() {
    for (int i = 0; i < E; i++) {
        sort(endpoint_request[i].begin(), endpoint_request[i].end());
        reverse(endpoint_request[i].begin(), endpoint_request[i].end());
    }
}

void sort_caches() {
    for (int i = 0; i < E; i++) {
        sort(cache_latency[i].begin(), cache_latency[i].end());
    }
}

void insert_things() {
    int vid, cl;
    for (int i = 0; i < E; i++) {
       //cout << "sorted od " << i << " " << sorted_endpoints[i].first << ", "
         //    << sorted_endpoints[i].second << endl;

        for (int j = 0; j < endpoint_request[i].size(); j++) {
            vid = endpoint_request[i][j].second;
            for (int k = 0; k < cache_latency[i].size(); k++) {
                cl = cache_latency[i][k].second;
                //cout << "cl = " << cl << endl;
                if (cache_space_left[cl] >= vsize[vid]) {
                    cache_videos[cl].insert(vid);
                    cache_space_left[cl] -= vsize[vid];
                    break;
                }
            }
        }
    }
}

void print_output() {
    int used_caches = 0;

    for (int i = 0; i < cache_space_left.size(); ++i) {
        if (cache_space_left[i] != X) used_caches += 1;
    }

    cout << used_caches << endl;

    for (int i = 0; i < cache_space_left.size(); ++i) {
        if (cache_space_left[i] != X) {
            cout << i;
            for (auto k = cache_videos[i].begin();
                 k != cache_videos[i].end(); ++k) {
                cout << " " << *k;
            }
            cout << endl;
        }
    }
}

int main() {
    read_input();
    sort_endpoints();
    sort_videos();
    sort_caches();
    insert_things();

    print_output();
    return 0;
}