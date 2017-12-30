#include "blimit.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <stack>
#include <mutex>
#include <thread>
#include <sstream>

#define NULL_NODE -1

std::vector<std::vector<std::pair<int, int>>> graph;

std::vector<std::set<std::pair<int, int>>> S; // adorators of given vertex
std::vector<std::vector<int>> T;

unsigned int _bvalue(unsigned int method, int node_id) {
    return bvalue(method, static_cast<unsigned long>(node_id));
}

std::pair<int, int> get_S_last(int v, unsigned int bv) {
    if (S[v].size() == bv)
        return *S[v].begin();
    return std::make_pair(0, NULL_NODE);
}

int get_weight(int u, int v) {
    for (auto p : graph[u]) {
        if (p.first == v)
            return p.second;
    }
    return 0;
}

// returns true if W(u,v) :<: W(v, w)
int compare_weights(int u, int v, int w, int weight) {
    // v - shared vertex
    if(weight == get_weight(v, w))
        return u < w;
    return weight < get_weight(v, w);
}

void bsuitor(unsigned int method, int n) {
    std::vector<int> Q, R;
    for (int v=0; v<n; v++)
        Q.push_back(v);

    while (!Q.empty()) {
        while (!Q.empty()) {
            int u = Q.back();
            Q.pop_back();
            unsigned int bu = _bvalue(method, u);
            //std::cout << "u = " << u << std::endl;
            while (T[u].size() < bu) {
                int x = NULL_NODE, x_weight = 0;
                for (auto p : graph[u]) {
                    int v = p.first, w = p.second;
                    int sv_last = get_S_last(v, _bvalue(method, v)).second; // S[v].last
                    if (std::find(T[u].begin(), T[u].end(), v) == T[u].end()
                        && compare_weights(sv_last, v, u, w)) {
                            if(w > x_weight || (w == x_weight && v > x)) {
                                //std::cout << "znalazlem: " << v << "\n";
                                x = v;
                                x_weight = w;
                            }
                    }
                }
                std::cout << u << " ma adorowac " << x << std::endl;
                
                if (x == NULL_NODE)
                    break;
                else {
                    std::pair<int, int> py = get_S_last(x, _bvalue(method, x));
                    int y = py.second; // S[x].last
                    if (y != NULL_NODE)
                        S[x].erase(py);
                    std::cout << "pW(" << u << ", " << x << ") = " << get_weight(u, x) << "\n";
                    std::pair<int, int> p = std::make_pair(x_weight, u);
                    S[x].insert(p); // delete y if y != null
                    T[u].push_back(x);
                    if (y != NULL_NODE) {
                        T[y].erase(std::remove(T[y].begin(), T[y].end(), x), T[y].end()); // erase-remove idiom
                        R.push_back(y);
                    }
                }
            }

        }

        Q.clear();
        std::cout << "Q = ";
        for (auto x : R) {
            Q.push_back(x);
            std::cout << x << ", ";
        }
        std::cout << std::endl;
        R.clear();
    }
}

int read_input(std::string filename) {
    std::ifstream input(filename);
    std::stringstream ss;
    while (!input.eof()) {
        std::string line;
        std::getline(input, line);
        if(line[0] != '#')
            ss << line << std::endl;
    }
    int u, v, w;
    int freeIndex = 0;
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    std::map<int, int> normalization_map;
    while (ss >> u >> v >> w) {
        normalization_map.insert(std::make_pair(u, 0));
        normalization_map.insert(std::make_pair(v, 0));
        edges.push_back(std::make_pair(u, std::make_pair(v, w)));
    }
    input.close();

    for (auto &m : normalization_map)
        m.second = freeIndex++;
    graph.resize(freeIndex+1);
    S.resize(freeIndex+1);
    T.resize(freeIndex+1);
    for (const auto &p : edges) {
        int u = p.first, v = p.second.first, w = p.second.second;
        int n_u = normalization_map[u], n_v = normalization_map[v];
        graph[n_u].push_back(std::make_pair(n_v, w));
        graph[n_v].push_back(std::make_pair(n_u, w));
    }
    return freeIndex;
}

int sum_of_matched_weights(int n) {
    int sum = 0;
    for (int v=0; v<n; v++) {
        for (auto u : T[v])
            sum += get_weight(v, u);
    }
    return sum / 2;
}

void clear_stuff(int n) {
    for (int i=0; i<n; i++) {
        S[i].clear();
        T[i].clear();
    }
}

int check_argv(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " thread-count inputfile b-limit" << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    if (!check_argv(argc, argv))
        return 1;

    int thread_count = std::stoi(argv[1]);
    int b_limit = std::stoi(argv[3]);
    std::string input_filename(argv[2]);

    int n = read_input(input_filename);

    for (int b_method = 0; b_method<b_limit+1; b_method++) {
        bsuitor(static_cast<unsigned>(b_method), n);
        std::cout << sum_of_matched_weights(n) << std::endl;
        clear_stuff(n);
    }
}
