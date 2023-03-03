#ifndef _CYCLIC_LIST_
#define _CYCLIC_LIST_

#include<initializer_list>
#include<functional>
#include<string>

template<class T>
class CyclicList
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

	CyclicList();
	CyclicList(const int& size);

	CyclicList(const CyclicList& list);
	CyclicList& operator=(const CyclicList& list);

	CyclicList(const std::initializer_list<T>& list);
	CyclicList& operator=(const std::initializer_list<T>& list);

	CyclicList(const CyclicList&& list);
	CyclicList& operator=(const CyclicList&& list);

	~CyclicList();

	void resize(const int& size);
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
	int countBy(std::function<bool(T)>predicat);

};

template<class T>
CyclicList<T>::CyclicList()
{
	size = 0;
	head = nullptr;
}

template<class T>
CyclicList<T>::CyclicList(const int& size)
{
	for (int i = 0; i < size; i++)
	{
		pushBack(T());
	}
}

template<class T>
CyclicList<T>::CyclicList(const CyclicList& list)
{
	Node<T>* current = list.head;
	for (int i = 0; i < list.size; i++)
	{
		this->pushBack(current->data);
		current = current->next;
	}
}

template<class T>
CyclicList<T>& CyclicList<T>::operator=(const CyclicList<T>& list)
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
CyclicList<T>::CyclicList(const std::initializer_list<T>& list)
{
	for (auto& val : list)
	{
		pushBack(val);
	}
}

template<class T>
CyclicList<T>& CyclicList<T>::operator=(const std::initializer_list<T>& list)
{
	clear();
	for (auto& val : list)
	{
		pushBack(val);
	}
	return *this;
}

template<class T>
CyclicList<T>::CyclicList(const CyclicList&& list)
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
CyclicList<T>& CyclicList<T>::operator=(const CyclicList<T>&& list)
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
CyclicList<T>::~CyclicList()
{
	clear();
}


template<class T>
void CyclicList<T>::resize(const int& size)
{
	clear();
	for (int i = 0; i < size; i++)
	{
		pushBack(T());
	}
}

template<class T>
void CyclicList<T>::clear()
{
	while (size != 0)
	{
		popBack();
	}
}

template<class T>
void CyclicList<T>::pushBack(const T& data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
		head->next = head;
	}
	else
	{
		Node<T>* current = head;
		while (current->next != head)
		{
			current = current->next;
		}
		current->next = new Node<T>(data, head);
	}
	++size;
}

template<class T>
void CyclicList<T>::pushFront(const T& data)
{
	if (head == nullptr) {
		head = new Node<T>(data);
		head->next = head;
		++size;
	}
	else {
		Node<T>* current = head;
		while (current->next != head) {
			current = current->next;
		}
		head = new Node<T>(data, head);
		current->next = head;
		++size;
	}

}


template<class T>
void CyclicList<T>::popBack()
{

	if (head == nullptr) return;

	if (head->next == head) {
		delete head;
		head = nullptr;
	}
	else {
		Node<T>* current = head;
		while (current->next->next != head) {
			current = current->next;
		}
		delete current->next;
		current->next = head;
	}
	--size;
}

template<class T>
void CyclicList<T>::popFront()
{
	Node<T>* current = head;
	while (current->next != head) {
		current = current->next;
	}

	head = head->next;
	delete current->next;
	current->next = head;
	--size;
}

template<class T>
T& CyclicList<T>::operator[](const int& index)
{
	Node<T>* current = head;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->data;
}

template<class T>
T& CyclicList<T>::getBy(std::function<bool(T)> predicat)
{
	if(head == nullptr) throw std::string("Element is not found");
	Node<T>* current = head;
	while (!predicat(current->data))
	{
		current = current->next;
		if (current == head) throw std::string("Element is not found");
	}
	return current->data;
}

template<class T>
void CyclicList<T>::insert(const int& index, const T& data)
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
void CyclicList<T>::removeBy(std::function<bool(T)> predicat)
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
			if (current->next == head) throw std::string("Element is not found");
		}
		Node<T>* temp = current->next;
		current->next = temp->next;
		delete temp;
		--size;
	}
}

template<class T>
bool CyclicList<T>::isEmpty() { return (size == 0); }

template<class T>
bool CyclicList<T>::findBy(std::function<bool(T)>predicat)
{

	if (head != nullptr) {
		if (predicat(head->data)) {
			return true;
		}
		Node<T>* current = head->next;
		while (current != head) {
			if (predicat(current->data)) {
				return true;
			}
			current = current->next;
		}
	}
	return false;
}

template<class T>
int CyclicList<T>::countBy(std::function<bool(T)>predicat)
{
	int count = 0;
	if (head != nullptr) {
		if (predicat(head->data)) {
			count++;
		}
		Node<T>* current = head->next;
		while (current != head) {
			if (predicat(current->data)) {
				count++;
			}
			current = current->next;
		}
	}
	return count;
}


#endif 
