#ifndef dsuh
#define dsuh

class DSU {
private:
    int* _parent;
    int* _rank;
    int _size;

public:
    DSU(int size);

    ~DSU();

    int find(int x);

    void unionSets(int x, int y);

    int rank(int x) const;
};

#endif
