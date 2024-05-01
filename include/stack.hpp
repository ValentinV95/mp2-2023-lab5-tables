// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#pragma once
#include <stdexcept>
#include <algorithm>

const size_t BASIC_SIZE = 10;

template<typename T>
class TStack {
public:
	TStack() {
		size = 0;
		pMem = new T[BASIC_SIZE];
		capacity = BASIC_SIZE;
	}
	~TStack() {
		delete[] pMem;
		size = 0;
		capacity = 0;
	}
	TStack(const TStack &copy) {
		size = copy.size;
		capacity = copy.capacity;
		pMem = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			pMem[i] = copy.pMem[i];
		}
	}
	TStack& operator=(const TStack &sec) {
		if (this == &sec) {
			return *this;
		}
		size = sec.size;
		if (capacity != sec.capacity) {
			T *temp = pMem;
			capacity = sec.capacity;
			pMem = new T[capacity];
			delete[] temp;
		}
		for (size_t i = 0; i < size; i++) {
			pMem[i] = sec.pMem[i];
		}
		return *this;
	}
	void push(T elem) {
		if (isFull()) {
			rearrange();
		}
		pMem[size++] = elem;
	}
	T top() {
		if (isEmpty()) {
			throw std::out_of_range("Stack: Stack is empty");
		}
		return pMem[size - 1];
	}
	T pop() {
		if (isEmpty()) {
			throw std::out_of_range("Stack: Stack is empty");
		}
		const T &ret = pMem[size - 1];
		size--;
		return ret;
	} 
	void clear() {
		size = 0;
	}
	size_t get_size() { return size; }
	bool isFull() { return size == capacity; }
	bool isEmpty() { return size == 0; }
private:
	void rearrange() {
		T *tmp = pMem;
		capacity *= 2;
		pMem = new T[capacity];
		std::copy(tmp, tmp + size, pMem);
		delete[] tmp;
	}
	T *pMem;
	size_t size;
	size_t capacity;
};
