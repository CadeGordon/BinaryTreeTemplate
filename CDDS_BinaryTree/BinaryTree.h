#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
template<typename T>
class TreeNode;

template<typename T>
class BinaryTree
{
public:

	BinaryTree();
	~BinaryTree();

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>*, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	m_root = nullptr;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	if (m_root == nullptr)
		return true;
	return false;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	TreeNode<T>* newNode = new TreeNode<T>(value);
	TreeNode<T>* tempNode = m_root;
	bool nodeInserted = false;

	if (m_root == nullptr)
	{
		m_root = newNode;
		return;
	}

	while (!nodeInserted)
	{
		if (value < tempNode->getData())
		{
			if (tempNode->getLeft())
				tempNode = tempNode->getLeft();
			else
			{
				tempNode->setLeft(newNode);
				nodeInserted = true;
			}
		}

		else if (value > tempNode->getData())
		{
			if (tempNode->getRight())
				tempNode = tempNode->getRight();
			else
			{
				tempNode->setRight(newNode);
				nodeInserted = true;
			}
		}

		else if (value == tempNode->getData())
			return;
	}

	return;
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	
	TreeNode<T>* nodeToRemove = nullptr; 
	TreeNode<T>* currentParent = nullptr;
	TreeNode<T>* currentNode = nullptr;

	if (!findNode(value, nodeToRemove, currentParent))
		return; 

	if (nodeToRemove->hasRight()) 
	{
		currentNode = nodeToRemove->getRight();

		if (currentNode->hasLeft()) 
		{
			currentParent = currentNode;
			bool searching = true;

			while (searching) 
			{
				if (currentParent->getLeft()->hasLeft()) 
				{
					currentParent = currentParent->getLeft();
				}
				else 
				{
					currentNode = currentParent->getLeft();
					searching = false;
				}
			}

			nodeToRemove->setData(currentNode->getData());
			currentParent->setLeft(currentNode->getRight());
			delete currentNode;
		}
		else 
		{
			nodeToRemove->setData(currentNode->getData());

			if (currentNode->hasRight()) 
			{
				nodeToRemove->setRight(currentNode->getRight());
			}
			else nodeToRemove->setRight(nullptr);
			delete currentNode;
		}
	}
	else 
	{
		if (currentParent) 
		{
			if (nodeToRemove->hasLeft()) 
			{
				currentNode = nodeToRemove->getLeft();
				
				if (currentParent->getLeft() == nodeToRemove)
					currentParent->setLeft(currentNode);
				
				else if (currentParent->getRight() == nodeToRemove)
					currentParent->setRight(currentNode);

				delete nodeToRemove;
				return;
			}
			else 
			{
				if (currentParent->getLeft() == nodeToRemove)
					currentParent->setLeft(nullptr);
				else if (currentParent->getRight() == nodeToRemove)
					currentParent->setRight(nullptr);
				
				delete nodeToRemove;
			}
		}
		else 
		{
			if (nodeToRemove->hasLeft()) 
			{
				currentNode = nodeToRemove->getLeft();
				
				m_root = currentNode;
				
				delete nodeToRemove;
				return;
			}
			else 
			{
				delete nodeToRemove;
				m_root = nullptr;
			}
		}
		delete currentNode;
	}
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	bool nodeFound = false;
	TreeNode<T>* currentNode = m_root;

	while (!nodeFound)
	{
		if (value < currentNode->getData())
		{
			if (currentNode->getLeft())
				currentNode = currentNode->getLeft();
		}

		else if (value > currentNode->getData())
		{
			if (currentNode->getRight())
				currentNode = currentNode->getRight();
		}

		else if (value == currentNode->getData())
			return currentNode;
	}

	return currentNode;

		
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	TreeNode<T>* currentNode = m_root;
	bool found = false;

	while (currentNode)
	{
		if (searchValue < currentNode->getData())
		{
			if (currentNode->getLeft())
			{
				nodeParent = currentNode;
				currentNode = currentNode->getLeft();
			}
			else
				return false;
		}

		else if (searchValue > currentNode->getData())
		{
			if (currentNode->getRight())
			{
				nodeParent = currentNode;
				currentNode = currentNode->getRight();
			}
			else
				return false;
		}

		else if (searchValue == currentNode->getData())
		{
			nodeFound = currentNode;
			found = true;
			return found;
		}
	}
	return found;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	//sets the needed space in between 
	horizontalSpacing /= 2;

	//check if the ucurrent node in null
	if (currentNode)
	{
		//draws the left cilkd if this node has one
		if (currentNode->hasLeft())
		{
			//Darws a line betwen the left child and the ucrrent node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//dras the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//draws a line between this child and the curent code
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//draws the current node
		currentNode->draw(x, y, (selected == currentNode));

	}
}