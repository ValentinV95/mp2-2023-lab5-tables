// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть
#include <cstdlib>
#include <iostream>
#include <exception>


template <class T>
class TStack {
private:
	T* data;
	size_t size;
	size_t cap;
	void resize()
	{
		T* tmp = new T[2*cap];
		std::copy(data+0, data+cap,tmp);
		delete[]data;
		data = tmp;
		cap *= 2;
	}
public:
	TStack()
	{
		data = new T[10];
		cap = 10;
		size = 0;
	}
	size_t quantElems() {
		return size;
	}
	bool isEmpty()
	{
		return (size == 0);
	}
	void push(T el) {
		if (size == cap)
			resize();
		data[size++] = el;
	}
	T pop()
	{
		if (isEmpty()) throw std::underflow_error("The stack is empty");
		else return data[--size];
	}
	T& top()
	{
		if (isEmpty()) throw std::underflow_error("The stack is empty");
		else return data[size-1];
	}
	void clear() //очистка стека. ƒва вопроса: зачем и правильно ли?
	{
		size = 0;
		cap = 10;
		T* tmp = new T[cap];
		delete[]data;
		data = tmp;
	}
	~TStack ()
	{
		delete[]data;
		size = cap = 0;
	}
};