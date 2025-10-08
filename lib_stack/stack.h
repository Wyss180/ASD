#ifndef STACK
#define STACK

template <class T>
class Stack {
	T* _data;
	int _size;
	int _top;

public:
	Stack(int size = 20) :_size(size), _top(-1) {
		_data = new T[size];
	}
	~Stack() {
		delete[] _data;
	}
};

#endif