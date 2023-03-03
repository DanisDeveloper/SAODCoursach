#ifndef _MY_FORWARD_LIST_
#define _MY_FORWARD_LIST_

#include<initializer_list>
#include<functional>
#include<string>

template<class T>
class List
{
private:

	template<class T>
	class Node
	{
	public:
		T data;
		Node* next;
		Node(T data = T(), Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};
	Node<T>* head = nullptr;
	int size = 0;
public:

	int getSize() { return size; }

	List();
	List(const int& size);

	List(const List& list);
	List& operator=(const List& list);

	List(const std::initializer_list<T>& list);
	List& operator=(const std::initializer_list<T>& list);

	List(const List&& list);
	List& operator=(const List&& list);

	~List();

	void resize(const int& size);
	T back();
	T front();
	void clear();
	void pushBack(const T& data);
	void pushFront(const T& data);
	void popBack();
	void popFront();
	T& operator[](const int& index);
	T& getBy(std::function<bool(T)> predicat);
	void insert(const int& index, const T& data);
	void removeBy(std::function<bool(T)> predicat);
	bool isEmpty();
	bool findBy(std::function<bool(T)>predicat);
};

template<class T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template<class T>
List<T>::List(const int& size)
{
	for (int i = 0; i < size; i++)
	{
		pushBack(T());
	}
}

template<class T>
List<T>::List(const List& list)
{
	Node<T>* current = list.head;
	for (int i = 0; i < list.size; i++)
	{
		this->pushBack(current->data);
		current = current->next;
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (list.head == head) return *this;
	clear();

	Node<T>* current = list.head;
	for (int i = 0; i < list.size; i++)
	{
		this->pushBack(current->data);
		current = current->next;
	}
	return *this;
}

template<class T>
List<T>::List(const std::initializer_list<T>& list)
{
	for (auto& val : list)
	{
		pushBack(val);
	}
}

template<class T>
List<T>& List<T>::operator=(const std::initializer_list<T>& list)
{
	clear();
	for (auto& val : list)
	{
		pushBack(val);
	}
	return *this;
}

template<class T>
List<T>::List(const List&& list)
{
	Node<T>* current = list.head;
	for (int i = 0; i < list.size; i++)
	{
		this->pushBack(current->data);
		current = current->next;
	}
	list.clear();
}

template<class T>
List<T>& List<T>::operator=(const List<T>&& list)
{
	if (list.head == head) return *this;
	clear();

	Node<T>* current = list.head;
	for (int i = 0; i < list.size; i++)
	{
		this->pushBack(current->data);
		current = current->next;
	}
	list.clear();
	return *this;
}

template<class T>
List<T>::~List()
{
	clear();
}


template<class T>
void List<T>::resize(const int& size)
{
	clear();
	for (int i = 0; i < size; i++)
	{
		pushBack(T());
	}
}

template<class T>
T List<T>::back()
{
	Node<T>* current = head;
	while (current->next != nullptr)
	{
		current = current->next;
	}

	return current->data;
}

template<class T>
T List<T>::front()
{
	return head->data;
}

template<class T>
void List<T>::clear()
{
	while (size != 0)
	{
		popBack();
	}
}

template<class T>
void List<T>::pushBack(const T& data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new Node<T>(data);
	}
	++size;
}

template<class T>
void List<T>::pushFront(const T& data)
{
	head = new Node<T>(data, head);
	++size;
}


template<class T>
void List<T>::popBack()
{

	if (head == nullptr) return;

	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		--size;
		return;
	}
	Node<T>* current = head;
	while (current->next->next != nullptr) {
		current = current->next;
	}
	delete current->next;
	current->next = nullptr;
	--size;
}

template<class T>
void List<T>::popFront()
{
	Node<T>* current = head;

	head = head->next;
	delete current;
	--size;
}

template<class T>
T& List<T>::operator[](const int& index)
{
	Node<T>* current = head;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->data;
}

template<class T>
T& List<T>::getBy(std::function<bool(T)> predicat)
{
	if (head == nullptr) throw std::string("Element is not found");
	Node<T>* current = head;
	while (!predicat(current->data))
	{
		current = current->next;
		if (current == nullptr) throw std::string("Element is not found");
	}
	return current->data;
}

template<class T>
void List<T>::insert(const int& index, const T& data)
{
	if (index == 0)
	{
		pushFront(data);
	}
	else
	{
		Node<T>* current = head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		Node<T>* newNode = new Node<T>(data, current->next);
		current->next = newNode;
		++size;
	}
}

template<class T>
void List<T>::removeBy(std::function<bool(T)> predicat)
{
	if (size == 0) throw std::string("CyclicList is empty");
	if (predicat(head->data)) {
		popBack();
	}
	else {
		Node<T>* current = head;
		while (!predicat(current->next->data))
		{
			current = current->next;
			if (current->next == nullptr) throw std::string("Element is not found");
		}
		Node<T>* temp = current->next;
		current->next = temp->next;
		delete temp;
		--size;
	}
}

template<class T>
bool List<T>::isEmpty() { return (size == 0); }

template<class T>
bool List<T>::findBy(std::function<bool(T)>predicat)
{
	Node<T>* current = head;
	while (current != nullptr) {
		if (predicat(current->data)) {
			return true;
		}
		current = current->next;
	}
	return false;
}


#endif 
