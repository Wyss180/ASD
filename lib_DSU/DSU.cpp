#include "DSU.h"
#include <stdexcept>

DSU::DSU(int size):_size(size) {
    _parent = new int[_size];
    _rank = new int[_size];
    for (int i = 0; i < _size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

int DSU::find(int x) {
    if (_parent[x] != x) {
        _parent[x] = find(_parent[x]);
    }
    return _parent[x];
}

void DSU::unionSets(int x, int y) {
    if (x == y) {
        return;
    }
    int rank_x = find(x);
    int rank_y = find(y);
    if (rank_x == rank_y) {
        return;
    }
    if (_rank[rank_x] < _rank[rank_y]) {
        _parent[rank_x] = rank_y;
    }
    else if (_rank[rank_x] > _rank[rank_y]) {
        _parent[rank_y] = rank_x;
    }
    else {
        _parent[rank_y] = rank_x;
        _rank[rank_x]++;
    }
}

int DSU::rank(int x) const {
    return _rank[x];
}