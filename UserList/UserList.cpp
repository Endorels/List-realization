// UserList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <list>

using namespace std;

template <typename T>
class UList
{

	public:
		UList();
		virtual ~UList();

		void push_back(T data);	// добавление в конец списка
		void pop_front();	// удаление из начала списка
		void push_front(T data); // добавление в начало списка
		void insert(T data, int index);	// вставка в позицию
		void removeAt(int index);		// удаление элемента в позиции
		void clear();		// Функция очистки списка


		T& operator[](const int index);		// оператор доступа к элементу

		int getSize() { return Size; };	//	вывод размера списка


	private:

		template <typename T>
		class Node
		{
			public:
				Node * pNext;
				T data;

				Node(T in_data = T(), Node * in_pNext = nullptr)
				{
					this->data = in_data;
					this->pNext = in_pNext;
				}
		};

		Node<T> * Head;
		int Size;
};

int main()
{
	setlocale(LC_ALL, "ru");

	UList<int> my_list;

	cout << "Size == " << my_list.getSize() << endl;
	cout << ">> Push_back" << endl;
	my_list.push_back(2);
	cout << ">> Push_back" << endl;
	my_list.push_back(3);
	cout << ">> Push_back" << endl;
	my_list.push_back(15);
	for (int i = 0; i < my_list.getSize(); ++i)
		cout << my_list[i] << endl;

	cout<< "Size == " << my_list.getSize() << endl;

	cout << ">> Push_front" << endl;
	my_list.push_front(111);
	for (int i = 0; i < my_list.getSize(); ++i)
		cout << my_list[i] << endl;

	cout << ">> insert" << endl;
	my_list.insert(222, 33);
	for (int i = 0; i < my_list.getSize(); ++i)
		cout << my_list[i] << endl;

	cout << ">> removeAt" << endl;
	my_list.removeAt(3);

	for(int i = 0; i < my_list.getSize(); ++i)
	cout << my_list[i] << endl;

}


template<typename T>
UList<T>::UList()
{
	Size = 0;
	Head = nullptr;
}

template<typename T>
UList<T>::~UList()
{
	this->clear();
}

template<typename T>
void UList<T>::push_back(T data)
{
	if (Head == nullptr)
		Head = new Node<T>(data);
	else
	{
		Node<T> * current = this->Head;

		while (current->pNext != nullptr)
			current = current->pNext;

		current->pNext = new Node<T>(data);
	}
	Size++;
}

template<typename T>
void UList<T>::pop_front()
{
	Node<T> * current = Head;

	Head = Head->pNext;
	delete current;
	Size--;
}

template<typename T>
void UList<T>::push_front(T data)
{
	Head  = new Node<T>(data, Head);
	Size++;
}

template<typename T>
void UList<T>::insert(T data, int index)
{

	if (index == 0)
	{
		push_front(data);
		Size++;
	}
	else if (index > this->getSize())
		cout << "Невозможно добавить элемент за пределами списка." << endl;
	else 
	{
		Node<T> * previous = this->Head;
		for (int i = 0; i < index - 1; ++i)
			previous = previous->pNext;
	
		Node<T> * newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}

}

template<typename T>
void UList<T>::removeAt(int index)
{
	if (index == 0)
		pop_front();

	else if(index > 0 && index < this->getSize())
	{
		Node<T> * current = this->Head;

		for (int i = 0; i < index - 1; ++i)
			current = current->pNext;

		Node<T> * onDelete = current->pNext;
		current->pNext = onDelete->pNext;
		delete onDelete;
		Size--;
	}
	else
	{
		cout << " Index out of range! " << endl;
	}

}

template<typename T>
void UList<T>::clear()
{
	while (Size)
		pop_front();
}

template<typename T>
T & UList<T>::operator[](const int index)
{
	int counter = 0;
	Node<T> * current = this->Head;

	while (current != nullptr)
	{
		if (counter == index)
			return current->data;

		current = current->pNext;
		counter++;
	}
}

