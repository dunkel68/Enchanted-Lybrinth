#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

class AVLNode {
public:
	Texture texture1;
	Sprite sprite1;
	int data;		// points to be added
	int height;
	string category;
	AVLNode* left, * right;
	AVLNode(int data = 0, string cat = "") {
		this->data = data;
		category = cat;
		left = right = NULL;
		height = 0;
	}
	~AVLNode() {
		left = right = NULL;
		delete left, right;
	}
};

class AVL {
public:
	AVLNode* root;
	AVL() {
		root = NULL;
	}
	AVLNode* insert(AVLNode* node, int data, string cat) {
		if (!root) {
			root = new AVLNode(data, cat);
			return root;
		}
		if (!node) {
			AVLNode* newNode = new AVLNode(data, cat);
			return newNode;
		}
		if (data < node->data)
			node->left = insert(node->left, data, cat);
		else if (data > node->data)
			node->right = insert(node->right, data, cat);
		else
			return node;
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = balancingFactor(node);
		
		if (balance > 1 && data < node->left->data)
			return rightRotate(node);
		if (balance < -1 && data > node->right->data)
			return leftRotate(node);
		if (balance < -1 && data < node->right->data) {		// Right Left Rotation
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		if (balance > 1 && data > node->left->data) {		// Left Right Rotation
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		return node;
	}
	AVLNode* remove(AVLNode* node, int data) {
		if (!root)
			return NULL;
		if (data < node->data)
			node->left = remove(node->left, data);
		else if (data > node->data)
			node->right = remove(node->right, data);
		else {
			if (node->left == NULL && node->right == NULL) {
				AVLNode* temp = node;
				delete temp;
				temp = node = NULL;
				return node;
			}
			else if (node->left == NULL && node->right != NULL)
				return node->right;
			else if (node->left != NULL && node->right == NULL)
				return node->left;
			else {
				AVLNode* temp = largest(node->left);
				node->data = temp->data;
				node->left = remove(node->left, temp->data);
				temp = NULL;
				delete temp;
				return node;
			}
		}
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = balancingFactor(node);

		if (balance > 1 && node->left->left != NULL)
			return rightRotate(node);
		if (balance < -1 && node->right->right != NULL)
			return leftRotate(node);
		if (balance < -1 && node->right->right == NULL) {		// Right Left Rotation
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		if (balance > 1 && node->left->left == NULL) {		// Left Right Rotation
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		return node;
	}
	AVLNode* rightRotate(AVLNode* node) {
		AVLNode* temp1 = node->left;
		AVLNode* temp2 = temp1->right;

		temp1->right = node;
		node->left = temp2;

		node->height = 1 + max(height(node->left), height(node->right));
		temp1->height = 1 + max(height(temp1->left), height(temp1->right));

		return temp1;
	}
	AVLNode* leftRotate(AVLNode* node) {
		AVLNode* temp1 = node->right;
		AVLNode* temp2 = temp1->left;

		temp1->left = node;
		node->right = temp2;

		node->height = 1 + max(height(node->left), height(node->right));
		temp1->height = 1 + max(height(temp1->left), height(temp1->right));

		return temp1;
	}
	bool isEmpty() {
		if (!root)
			return true;
		else
			return false;
	}
	bool search(AVLNode* node, int data) {
		if (!node)
			return false;
		else if (data < node->data)
			search(node->left, data);
		else if (data > node->data)
			search(node->right, data);
		else
			return true;
	}
	int peek(AVLNode* node, int data) {
		AVLNode* current = root;
		while(current) {
			if (data > node->data) {
				current = current->right;
			}
			else if (data < current->data) {
				current = current->left;
			}
			else
				return data;
		}
		return 0;
	}
	AVLNode* largest(AVLNode* r) {
		if (!r)
			return NULL;
		else if (!r->right)
			return r;
		else
			largest(r->right);
	}
	AVLNode* smallest(AVLNode* r) {
		if (!r)
			return NULL;
		else if (!r->left)
			return r;
		else
			smallest(r->left);
	}
	int balancingFactor(AVLNode* node) {
		if (!node)
			return 0;
		else
			return (height(node->left) - height(node->right));
	}
	int height(AVLNode* node) {
		if (!node)
			return -1;
		else
			return node->height;
	}
	void inorderTraversal(AVLNode* node) {
		if (!node)
			return;
		inorderTraversal(node->left);
		cout << node->data << " ";
		inorderTraversal(node->right);
	}
	void insertNode(AVLNode* node, int data, string cat) {
		root = insert(node, data, cat);
	}
	void deleteNode(AVLNode* node, int data) {
		if (search(node, data))
			root = remove(node, data);
		else
			return;
	}
	void displayInventoryOnScreen(AVLNode* node, RenderWindow& window) {
		if (!node)
			return;
		displayInventoryOnScreen(node->left, window);
		if (node->category == "key") {
			node->texture1.loadFromFile("images/key.png");
			node->sprite1.setTexture(node->texture1);
			node->sprite1.setScale(0.2f, 0.2f);
			node->sprite1.setPosition(900, 200);
			window.draw(node->sprite1);
		}
		else if (node->category == "sword-1") {
			node->texture1.loadFromFile("images/sword1.png");
			node->sprite1.setTexture(node->texture1);
			node->sprite1.setScale(0.2f, 0.2f);
			node->sprite1.setPosition(950, 200);
			window.draw(node->sprite1);
		}
		else if (node->category == "sword-2") {
			node->texture1.loadFromFile("images/sword2.png");
			node->sprite1.setTexture(node->texture1);
			node->sprite1.setScale(0.2f, 0.2f);
			node->sprite1.setPosition(1000, 200);
			window.draw(node->sprite1);
		}
		else if (node->category == "portion-1") {
			node->texture1.loadFromFile("images/orange.png");
			node->sprite1.setTexture(node->texture1);
			node->sprite1.setScale(0.2f, 0.2f);
			node->sprite1.setPosition(1050, 200);
			window.draw(node->sprite1);
		}
		else if (node->category == "portion-2") {
			node->texture1.loadFromFile("images/green.png");
			node->sprite1.setTexture(node->texture1);
			node->sprite1.setScale(0.1f, 0.1f);
			node->sprite1.setPosition(1100, 200);
			window.draw(node->sprite1);
		}
		else if (node->category == "portion-3") {
			node->texture1.loadFromFile("images/blue.png");
			node->sprite1.setTexture(node->texture1);
			node->sprite1.setScale(0.1f, 0.1f);
			node->sprite1.setPosition(1150, 200);
			window.draw(node->sprite1);
		}
		displayInventoryOnScreen(node->right, window);

	}
};

//bool collectInventory(const Player& player, Inventory& inventory) {
//
//}