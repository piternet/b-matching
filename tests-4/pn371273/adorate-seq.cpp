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

std::map<std::pair<int, int>, int> weights;
std::map<int, std::vector<int>> graph;
std::set<int> vertices;

std::map<int, std::priority_queue<std::pair<int, int>>> S; // adorators of given vertex
std::map<int, std::vector<int>> T;

unsigned int _bvalue(unsigned int method, int node_id) {
    return bvalue(method, static_cast<unsigned long>(node_id));
}

int get_S_last(int v, int bv) {
    if (S[v].size() == bv)
        return S[v].top().second;
    return NULL_NODE;
}

int get_weight(int u, int v) {
    if (u == NULL_NODE || v == NULL_NODE)
        return 0;
    return weights[std::make_pair(u, v)];
}

// returns true if W(u,v) :<: W(v, w)
int compare_weights(int u, int v, int w) {
    // v - shared vertex
    if(get_weight(u, v) == get_weight(v, w))
        return u < w;
    return get_weight(u, v) < get_weight(v, w);
}

void bsuitor(unsigned int method) {
    std::vector<int> Q, R;
    for (auto v : vertices)
        Q.push_back(v);

    while (!Q.empty()) {
        while (!Q.empty()) {
            int u = Q.back();
            Q.pop_back();
            unsigned int bu = _bvalue(method, u);
            std::cout << "u = " << u << std::endl;
            while (T[u].size() < bu) {
                int x = NULL_NODE, x_weight = 0;
                for (auto v : graph[u]) {
                    int sv_last = get_S_last(v, _bvalue(method, v)); // S[v].last
                    if (std::find(T[u].begin(), T[u].end(), v) == T[u].end()
                        && compare_weights(sv_last, v, u)) {
                            if(get_weight(u, v) > x_weight) {
                                std::cout << "znalazlem: " << v << "\n";
                                x = v;
                                x_weight = get_weight(u, v);
                            }
                    }
                }
                std::cout << u << " ma adorowac " << x << std::endl;
                
                if (x == NULL_NODE)
                    break;
                else {
                    int y = get_S_last(x, _bvalue(method, x)); // S[x].last
                    if (y != NULL_NODE)
                        S[x].pop();
                    std::cout << "pW(" << u << ", " << x << ") = " << get_weight(u, x) << "\n";
                    S[x].push(std::make_pair(-get_weight(u, x), u)); // delete y if y != null
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

void read_input(std::string filename) {
    std::ifstream input(filename);
    std::stringstream ss;
    while (!input.eof()) {
        std::string line;
        std::getline(input, line);
        if(line[0] != '#')
            ss << line << std::endl;
    }
    int u, v, w;
    while (ss >> u >> v >> w) {
        weights[std::make_pair(u, v)] = w;
        //std::cout << "W(" << u << ", " << v << ") = " << get_weight(u, v) << "\n";
        weights[std::make_pair(v, u)] = w;
        //std::cout << "W(" << v << ", " << u << ") = " << get_weight(v, u) << "\n";
        graph[u].push_back(v);
        graph[v].push_back(u);
        vertices.insert(v);
        vertices.insert(u);    
        //std::cerr << u << " " << v << " " << std::endl;
    }
    input.close();
}

int sum_of_matched_weights() {
    int sum = 0;
    for (auto v : vertices) {
        for (auto u : T[v])
            sum += get_weight(v, u);
    }
    return sum;
}

void clear_stuff() {

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

    read_input(input_filename);

    for (unsigned int b_method = 0; b_method<b_limit+1; b_method++) {
        bsuitor(b_method);
        std::cout << sum_of_matched_weights() << std::endl;
        clear_stuff();
    }
}
