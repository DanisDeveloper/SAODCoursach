#ifndef _TREE_
#define _TREE_
#include<string>
#include<iostream>

#include"Room.h"

class Tree {

	class Node {
	public:
		Room data;
		int heightNode;
		Node* right;
		Node* left;
		Node* previous;
		Node(Room& data, Node* right = nullptr, Node* left = nullptr, Node* previous = nullptr, int heightNode = 1) {
			this->data = data;
			this->right = right;
			this->left = left;
			this->heightNode = heightNode;
			this->previous = previous;
		}
	};
	Node* root = nullptr;

	void getMaxLines(Node* node, int& maxLengthNumber, int& maxLengthPlaces, int& maxLengthRooms, int& maxLengthBathroom, int& maxLengthEquipment) {
		if (node == nullptr) return;
		if (std::to_string(node->data.getPlaces()).length() > maxLengthPlaces) maxLengthPlaces = std::to_string(node->data.getPlaces()).length();
		if (std::to_string(node->data.getRooms()).length() > maxLengthRooms) maxLengthRooms = std::to_string(node->data.getRooms()).length();
		if ((node->data.getBathroom() ? 4 : 5) > maxLengthBathroom) maxLengthBathroom = (node->data.getBathroom() ? 4 : 5);
		if (node->data.getEquipment().length() > maxLengthEquipment) maxLengthEquipment = node->data.getEquipment().length();
		getMaxLines(node->left, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom,  maxLengthEquipment);
		getMaxLines(node->right, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment);
	}

	void recursivePrint(Node* node, int maxLengthNumber, int maxLengthPlaces, int maxLengthRooms, int maxLengthBathroom, int maxLengthEquipment, std::function<bool(Room)>predicat) {
		if (node == nullptr) return;
		if(predicat(node->data))
			printLine(node->data, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment);
		recursivePrint(node->left, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment, predicat);
		recursivePrint(node->right, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment, predicat);
	}
	//void max_length_number(Node* node, int& length_number) {
	//	if (node == nullptr) return;
	//	if (std::to_string(node->room).length() > length_number)length_number = std::to_string(node->room).length();
	//	max_length_number(node->left, length_number);
	//	max_length_number(node->right, length_number);
	//}

	int getHeight(Node* node) {
		return node ? node->heightNode : 0;
	}
	int difference(Node* node) {
		return getHeight(node->right) - getHeight(node->left);
	}
	void fixHeight(Node* node) {
		int height_left = getHeight(node->left);
		int height_right = getHeight(node->right);
		node->heightNode = (height_left > height_right ? height_left : height_right) + 1;
	}
	void rightRotate(Node* high) {
		Node* low = high->left;
		high->left = low->right;
		if (low->right != nullptr)
			low->right->previous = high;
		low->right = high;
		low->previous = high->previous;
		high->previous = low;
		if (low->previous != nullptr) {
			if (low->previous->data < low->data) {
				low->previous->right = low;
			}
			if (low->previous->data > low->data) {
				low->previous->left = low;
			}
		}

		fixHeight(high);
		fixHeight(low);
	}
	void leftRotate(Node* high) {
		Node* low = high->right;
		high->right = low->left;
		if (low->left != nullptr)
			low->left->previous = high;
		low->left = high;
		low->previous = high->previous;
		high->previous = low;
		if (low->previous != nullptr) {
			if (low->previous->data < low->data) {
				low->previous->right = low;
			}
			if (low->previous->data > low->data) {
				low->previous->left = low;
			}
		}
		fixHeight(high);
		fixHeight(low);
	}
	void balance(Node* node) {
		while (true) {
			fixHeight(node);
			if (difference(node) >= 2) {
				if (difference(node->right) == 1 || difference(node->right) == 0) {
					leftRotate(node);
				}
				else
				{
					//BigLeftRotate
					rightRotate(node->right);
					leftRotate(node);
				}
			}
			else if (difference(node) <= -2) {
				if (difference(node->left) == -1 || difference(node->left) == 0) {
					rightRotate(node);
				}
				else
				{
					//BigRightRotate
					leftRotate(node->left);
					rightRotate(node);
				}
			}
			if (node->previous)
				node = node->previous;
			else {
				root = node;
				break;
			}
			root = node;
		}
	}
	void clearRecursive(Node* node) {
		if (node == nullptr) return;
		clearRecursive(node->left);
		clearRecursive(node->right);
		delete node;
	}
public:
	bool add(Room data) {
		if (!(this->find(data))) {
			if (root == nullptr) {
				root = new Node(data);
			}
			else {

				Node* temp = root;
				while (true) {
					if (data > temp->data) {
						if (temp->right == nullptr) {
							temp->right = new Node(data);
							temp->right->previous = temp;

							break;
						}
						else {
							temp = temp->right;

						}

					}
					else {
						if (temp->left == nullptr) {
							temp->left = new Node(data);
							temp->left->previous = temp;
							break;
						}
						else {
							temp = temp->left;
						}
					}
				}
				balance(temp);
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	void remove(Room data) {
		if (this->find(data)) {
			Node* temp = root;
			while (true) {
				if (data == temp->data) {
					if (getHeight(temp) == 1) {
						if (temp->previous == nullptr) {
							delete temp;
							temp = nullptr;
							root = nullptr;
						}
						else {
							if (data < temp->previous->data) {
								temp->previous->left = nullptr;
							}
							else {
								temp->previous->right = nullptr;
							}
							Node* another_temp = temp->previous;
							delete temp;
							temp = nullptr;
							this->balance(another_temp);
						}
						break;
					}

					if (temp->right == nullptr || temp->left == nullptr) {
						if (temp->previous == nullptr) {
							if (temp->right != nullptr) {
								root = temp->right;
								temp->right->previous = nullptr;
							}
							else if (temp->left != nullptr) {
								root = temp->left;
								temp->left->previous = nullptr;
							}
							delete temp;
							temp = nullptr;
							this->balance(root);
						}
						else {
							if (data < temp->previous->data) {
								if (temp->right != nullptr) {
									temp->right->previous = temp->previous;
									temp->previous->left = temp->right;
								}
								else if (temp->left != nullptr) {
									temp->left->previous = temp->previous;
									temp->previous->left = temp->left;
								}
							}
							else {
								if (temp->right != nullptr) {
									temp->right->previous = temp->previous;
									temp->previous->right = temp->right;
								}
								else if (temp->left != nullptr) {
									temp->left->previous = temp->previous;
									temp->previous->right = temp->left;
								}
							}
							Node* another_temp = temp->previous;
							delete temp;
							temp = nullptr;
							this->balance(another_temp);
						}

						break;
					}
					if (temp->right != nullptr && temp->left != nullptr) {
						Node* most_right = temp->left;
						while (most_right->right != nullptr) {
							most_right = most_right->right;
						}
						if (most_right == temp->left) {
							most_right->previous = temp->previous;
							if (temp->previous != nullptr) {
								if (data < temp->previous->data)
									temp->previous->left = most_right;
								else
									temp->previous->right = most_right;
							}
							most_right->right = temp->right;
							temp->right->previous = most_right;
							delete temp;
							temp = nullptr;
							this->balance(most_right);
							break;
						}
						else {
							Node* prev = most_right->previous;
							prev->right = most_right->left;
							if (most_right->left != nullptr) {
								most_right->left->previous = prev;
							}
							most_right->right = temp->right;
							most_right->left = temp->left;
							temp->right->previous = most_right;
							temp->left->previous = most_right;
							most_right->previous = temp->previous;
							if (temp->previous != nullptr) {
								if (data < temp->previous->data) {
									temp->previous->left = most_right;
								}
								else {
									temp->previous->right = most_right;
								}
							}
							delete temp;
							temp = nullptr;
							this->balance(prev);
							break;
						}
					}
				}
				else if (data < temp->data) {
					temp = temp->left;
				}
				else if (data > temp->data) {
					temp = temp->right;
				}
			}
		}
		else
		{
			throw std::string("Room with number \"") + data.getNumber() + std::string("\" is not found!");
		}
	}
	bool find(Room room) {
		if (root != nullptr) {
			Node* temp = root;
			while (temp->data != room) {
				if (room > temp->data) {
					if (temp->right == nullptr) {
						return false;
					}
					else {
						temp = temp->right;
					}
				}
				else {
					if (temp->left == nullptr) {
						return false;
					}
					else {
						temp = temp->left;
					}
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	Room& get(std::string number) {
			if (root != nullptr) {
				Node* temp = root;
				while (!(numberToInt(temp->data.getNumber()) == numberToInt(number) && temp->data.getNumber()[0] == number[0])) {
					if (numberToInt(number) > numberToInt(temp->data.getNumber())) {
						if (temp->right == nullptr) {
							throw std::string("Element is not found");
						}
						else {
							temp = temp->right;
						}
					}
					else {
						if (temp->left == nullptr) {
							throw std::string("Element is not found");
						}
						else {
							temp = temp->left;
						}
					}
				}
				return temp->data;
			}
			else {
				throw std::string("Element is not found");
			}
	}

	void printEdgeLine(int maxLengthNumber, int maxLengthPlaces, int maxLengthRooms, int maxLengthBathroom, int maxLengthEquipment) {
		std::cout << "+-";
		for (int i = 0; i < maxLengthNumber; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthPlaces; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthRooms; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthBathroom; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthEquipment; i++)
			std::cout << "-";
		std::cout << "-+" << std::endl;
	}

	void printElementByMaxWidth(std::string str, int maxLength) {
		int diff = maxLength - str.length();
		std::cout << str;
		for (int i = 0; i < diff; i++)
			std::cout << " ";
	}

	void printLine(Room room, int maxLengthNumber, int maxLengthPlaces, int maxLengthRooms, int maxLengthBathroom, int maxLengthEquipment) {
		std::cout << "| ";
		printElementByMaxWidth(room.getNumber(), maxLengthNumber);
		std::cout << " | ";
		printElementByMaxWidth(std::to_string(room.getPlaces()), maxLengthPlaces);
		std::cout << " | ";
		printElementByMaxWidth(std::to_string(room.getRooms()), maxLengthRooms);
		std::cout << " | ";
		printElementByMaxWidth(room.getBathroom() ? "true" : "false", maxLengthBathroom);
		std::cout << " | ";
		printElementByMaxWidth(room.getEquipment(), maxLengthEquipment);
		std::cout << " |" << std::endl;
	}

	void print(std::function<bool(Room)>predicat) {
		if (!isEmpty()) {
			int maxLengthNumber = 6;
			int maxLengthPlaces = 6;
			int maxLengthRooms = 5;
			int maxLengthBathroom = 8;
			int maxLengthEquipment = 9;
			getMaxLines(root, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment);

			printEdgeLine(maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment);
			std::cout << "| ";
			printElementByMaxWidth("Number", maxLengthNumber);
			std::cout << " | ";
			printElementByMaxWidth("Places", maxLengthPlaces);
			std::cout << " | ";
			printElementByMaxWidth("Rooms", maxLengthRooms);
			std::cout << " | ";
			printElementByMaxWidth("Bathroom", maxLengthBathroom);
			std::cout << " | ";
			printElementByMaxWidth("Equipment", maxLengthEquipment);
			std::cout << " |" << std::endl;
			printEdgeLine(maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment);
			recursivePrint(root, maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment, predicat);
			printEdgeLine(maxLengthNumber, maxLengthPlaces, maxLengthRooms, maxLengthBathroom, maxLengthEquipment);
		}
		else {
			std::cout << "Empty" << std::endl;
		}
	}

	bool isEmpty() {
		return root == nullptr;
	}

	void clear() {
		clearRecursive(root);
		root = nullptr;
	}
	~Tree() {
		this->clear();
	}
};


#endif
