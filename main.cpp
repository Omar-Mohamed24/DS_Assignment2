#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <vector>
using namespace std;
//-------------------------------------------------------class-----------------------------------------------------------------------
class Item
{
private:
    string itemName;
    string category;
    int price;

public:
    // Regular constructor
    Item(string itemName, string category, int price);

    // Copy constructor
    Item(const Item &other);

    // Getter methods
    string get_itemName() const;
    string get_category() const;
    int get_price() const;

    // Display method
    void display(ostream &os) const;
    void display() const;

    // Overload comparison operators
    friend bool operator<(const Item &I1, const Item &I2);
    friend bool operator>(const Item &I1, const Item &I2);
    friend bool operator==(const Item &I1, const Item &I2);
};
//-----------------------------------------------class_implementation----------------------------------------------------------------
Item::Item(string itemName, string category, int price)
{
    this->itemName = itemName;
    this->category = category;
    this->price = price;
}

Item::Item(const Item &other) : itemName(other.itemName), category(other.category), price(other.price) {}

string Item::get_itemName() const
{
    return itemName;
}

string Item::get_category() const
{
    return category;
}

int Item::get_price() const
{
    return price;
}

void Item::display(ostream &os) const
{
    os << "Item Name: " << itemName << "\n";
    os << "Category: " << category << "\n";
    os << "Price: " << price << "\n";
    os << "\n";
}

void Item::display() const
{
    display(cout);
}

bool operator<(const Item &I1, const Item &I2)
{
    if (I1.itemName != I2.itemName)
        return I1.itemName < I2.itemName;
    if (I1.category != I2.category)
        return I1.category < I2.category;
    return I1.price < I2.price;
}

bool operator>(const Item &I1, const Item &I2)
{
    return I2 < I1; // Just swap the arguments and use the < operator
}

bool operator==(const Item &I1, const Item &I2)
{
    return I1.itemName == I2.itemName && I1.category == I2.category && I1.price == I2.price;
}

//---------------------------------------------------------BST_Implementation--------------------------------------------------------
template <typename T>
struct BSTNode
{
    T Key;
    BSTNode<T> *leftlink;
    BSTNode<T> *rightlink;

    BSTNode() : leftlink(nullptr), rightlink(nullptr) {}

    BSTNode(const T &key) : Key(key), leftlink(nullptr), rightlink(nullptr) {}
};
//*********************************************************************************
template <typename T>
class BST
{
private:
    BSTNode<T> *root;

public:
    BST() : root(NULL) {}
    BSTNode<T> *getroot() const { return root; }
/////////////////////helperfunc////////////////////////////
    void inOrder(BSTNode<T> *node, vector<T> &items) const
    {
        if (node == nullptr)
            return;
        inOrder(node->leftlink, items);
        items.push_back(node->Key);
        inOrder(node->rightlink, items);
    }

    void preOrder(BSTNode<T> *node, vector<T> &items) const
    {
        if (node == nullptr)
            return;
        items.push_back(node->Key);       // Visit the root node first
        preOrder(node->leftlink, items);  // Then traverse the left subtree
        preOrder(node->rightlink, items); // Finally traverse the right subtree
    }
////////////////////////// insert///////////////////////////
    void insert(const T &insertItem)
    {
        BSTNode<T> *current, *prev, *newNode;
        newNode = new BSTNode<T>(insertItem);
        if (root == NULL)
            root = newNode;
        else
        {
            current = root;
            while (current != NULL)
            {
                prev = current;
                if (current->Key == insertItem)
                {
                    cout << "The insert item is already in the list-";
                    cout << "duplicates are not allowed.";
                    insertItem.display();
                    return;
                }
                else if (insertItem < current->Key)
                    current = current->leftlink;
                else
                    current = current->rightlink;
            }
            if (insertItem < prev->Key)
                prev->leftlink = newNode;
            else
                prev->rightlink = newNode;
        }
    }
/////////////////////////remove////////////////////////////////////////
    void deleteNode(BSTNode<T> *&node, const T &deleteItem)
    {
        BSTNode<T> *temp, *current, *prev;
        if (node == NULL)
            cerr << "Error: The node to be deleted is NULL." << endl;

        if (deleteItem < node->Key)
        {
            deleteNode(node->leftlink, deleteItem);
        }
        else if (deleteItem > node->Key)
        {
            deleteNode(node->rightlink, deleteItem);
        }
        else
        {
            if (node->leftlink == NULL && node->rightlink == NULL)
            {
                node = nullptr;
                delete node;
            }
            else if (node->leftlink == NULL)
            {
                temp = node;
                node = node->rightlink;
                delete temp;
            }
            else if (node->rightlink == NULL)
            {
                temp = node;
                node = node->leftlink;
                delete temp;
            }
            else
            {
                current = node->leftlink;
                prev = NULL;
                while (current->rightlink != NULL)
                {
                    prev = current;
                    current = current->rightlink;
                }
                node->Key = current->Key;
                if (prev == NULL)
                    node->leftlink = current->leftlink;
                else
                    prev->rightlink = current->leftlink;
                delete current;
            }
        }
    }

    void deleteitem(const T &deleteItem)
    {
        deleteNode(root, deleteItem);
    }
/////////////////////////Display//////////////////////////
    void Display() const
    {
        vector<T> items;
        preOrder(root, items);
        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their name ascending////////////////////////
    void displaySortedByNameascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end());
        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their name descending////////////////////////
    void displaySortedByNamedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.rbegin(), items.rend());
        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their prices ascending//////////////////////
    void displaySortedByPriceascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const T &a, const T &b)
             { return a.get_price() < b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their prices descending//////////////////////
    void displaySortedByPricedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const T &a, const T &b)
             { return a.get_price() > b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
};
//---------------------------------------------------------AVL_Implementation--------------------------------------------------------
template <class elemType>
struct AVLNode
{
    elemType info;
    int bfactor; // balance factor
    AVLNode<elemType> *llink;
    AVLNode<elemType> *rlink;
    AVLNode() : info(elemType()), bfactor(0), llink(nullptr), rlink(nullptr) {}
    AVLNode(const elemType &info) : info(info), bfactor(0), llink(nullptr), rlink(nullptr) {}
};
//**********************************************************************************
template <typename elemType>
class AVL
{
private:
    AVLNode<elemType> *root;

public:
    AVL() : root(NULL) {}

    AVLNode<elemType> *getroot() const { return root; }
/////////////////////helperfunc//////////////////////////////////////////////////
    void inOrder(AVLNode<elemType> *node, vector<elemType> &items) const
    {
        if (node == nullptr)
            return;
        inOrder(node->llink, items);
        items.push_back(node->info);
        inOrder(node->rlink, items);
    }

    void preOrder(AVLNode<elemType> *node, vector<elemType> &items) const
    {
        if (node == nullptr)
            return;
        items.push_back(node->info);
        preOrder(node->llink, items);
        preOrder(node->rlink, items);
    }

    void rotateToLeft(AVLNode<elemType>* &root)
    {
        AVLNode<elemType> *p; 
        if (root == NULL)
            cerr << "Error in the tree" << endl;
        else if (root->rlink == NULL)
            cerr << "Error in the tree:"
                <<" No right subtree to rotate." << endl;
        else
        {
            p = root->rlink;
            root->rlink = p->llink; 
            p->llink = root;
            root = p; 
        }
    }

    void rotateToRight(AVLNode<elemType>* &root)
    {
        AVLNode<elemType> *p;
        if (root == NULL)
            cerr << "Error in the tree" << endl;
        else if (root->llink == NULL)
            cerr << "Error in the tree:"
            << " No left subtree to rotate." << endl;
        else
        {
            p = root->llink;
            root->llink = p->rlink;
            p->rlink = root;
            root = p; 
        }
    }

    void balanceFromLeft(AVLNode<elemType>* &root)
    {
        AVLNode<elemType> *p;
        AVLNode<elemType> *w;
        p = root->llink; //p points to the left subtree of root
        switch (p->bfactor)
        {
            case -1:
                root->bfactor = 0;
                p->bfactor = 0;
                rotateToRight(root);
                break;
            case 0:
                cerr << "Error: Cannot balance from the left." << endl;
                break;
            case 1:
                w = p->rlink;
                switch (w->bfactor) 
                {
                    case -1:
                        root->bfactor = 1;
                        p->bfactor = 0;
                        break;
                    case 0:
                        root->bfactor = 0;
                        p->bfactor = 0;
                        break;
                    case 1:
                        root->bfactor = 0;
                        p->bfactor = -1;
                }
                w->bfactor = 0;
                rotateToLeft(p);
                root->llink = p;
                rotateToRight(root);
        }
    }

    void balanceFromRight(AVLNode<elemType>* &root)
    {
        AVLNode<elemType> *p;
        AVLNode<elemType> *w;
        p = root->rlink; 
        switch (p->bfactor)
        {
            case -1:
                w = p->llink;
                switch (w->bfactor)
                {
                case -1:
                    root->bfactor = 0;
                    p->bfactor = 1;
                    break;
                case 0:
                    root->bfactor = 0;
                    p->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = -1;
                    p->bfactor = 0;
                }
                w->bfactor = 0;
                rotateToRight(p);
                root->rlink = p;
                rotateToLeft(root);
                break;
            case 0:
                cerr << "Error: Cannot balance from the left." << endl;
                break;
            case 1:
                root->bfactor = 0;
                p->bfactor = 0;
                rotateToLeft(root);
        }
    }
////////////////////////// insert/////////////////////////////////////////////////
    void insertIntoAVL(AVLNode<elemType>* &root,AVLNode<elemType> *newNode, bool& isTaller)
    {
        if (root == NULL)
        {
            root = newNode;
            isTaller = true;
        }
        else if (root->info == newNode->info)
            cerr << "No duplicates are allowed." << endl;
        else if (root->info > newNode->info)
        {
            insertIntoAVL(root->llink, newNode, isTaller);
            if (isTaller)
                switch (root->bfactor)
                {
                    case -1:
                        balanceFromLeft(root);
                        isTaller = false;
                        break;
                    case 0:
                        root->bfactor = -1;
                        isTaller = true;
                        break;
                    case 1:
                        root->bfactor = 0;
                        isTaller = false;
                }
        }
        else
        {
            insertIntoAVL(root->rlink, newNode, isTaller);
            if (isTaller)
                switch (root->bfactor)
                {
                    case -1:
                        root->bfactor = 0;
                        isTaller = false;
                        break;
                    case 0:
                        root->bfactor = 1;
                        isTaller = true;
                        break;
                    case 1:
                        balanceFromRight(root);
                        isTaller = false;
                }
        }
    }

    void insert(const elemType &newItem)
    {
        bool isTaller = false;
        AVLNode<elemType> *newNode;
        newNode = new AVLNode<elemType>(newItem);
        
        insertIntoAVL(root, newNode, isTaller);
    }
/////////////////////////remove///////////////////////////////////////////////////
    void deleteNode(AVLNode<elemType> *&root, const elemType &key, bool &isShorter)
    {
        if (root == nullptr)
        {
            isShorter = false;
            return;
        }

        if (key < root->info)
        {
            deleteNode(root->llink, key, isShorter);
            if (isShorter)
            {
                switch (root->bfactor)
                {
                    case -1:
                        root->bfactor = 0;
                        isShorter = true;
                        break;
                    case 0:
                        root->bfactor = 1;
                        isShorter = false;
                        break;
                    case 1:
                        balanceFromRight(root);
                        isShorter = (root->bfactor == 0);
                        break;
                }
            }
        }
        else if (key > root->info)
        {
            deleteNode(root->rlink, key, isShorter);
            if (isShorter)
            {
                switch (root->bfactor)
                {
                    case 1:
                        root->bfactor = 0;
                        isShorter = true;
                        break;
                    case 0:
                        root->bfactor = -1;
                        isShorter = false;
                        break;
                    case -1:
                        balanceFromLeft(root);
                        isShorter = (root->bfactor == 0);
                        break;
                }
            }
        }
        else
        {
            if ((root->llink == nullptr) || (root->rlink == nullptr))
            {
                AVLNode<elemType> *temp = root->llink ? root->llink : root->rlink;

                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
                isShorter = true;
            }
            else
            {
                AVLNode<elemType> *current = root->rlink;
                while (current->llink != nullptr)
                    current = current->llink;

                root->info = current->info;
                deleteNode(root->rlink, current->info, isShorter);

                if (isShorter)
                {
                    switch (root->bfactor)
                    {
                        case 1:
                            root->bfactor = 0;
                            isShorter = true;
                            break;
                        case 0:
                            root->bfactor = -1;
                            isShorter = false;
                            break;
                        case -1:
                            balanceFromLeft(root);
                            isShorter = (root->bfactor == 0);
                            break;
                    }
                }
            }
        }
    }

    void deleteitem(const elemType &deleteItem)
    {
        bool isShorter = false;
        deleteNode(root, deleteItem, isShorter);
    }
/////////////////////////Display//////////////////////////////////////////////////
    void Display() const
    {
        vector<elemType> items;
        preOrder(root, items);
        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their name ascending/////////////////////////
    void displaySortedByNameascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.begin(), items.end());
        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their name descending////////////////////////
    void displaySortedByNamedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.rbegin(), items.rend());
        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their prices ascending///////////////////////
    void displaySortedByPriceascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const elemType &a, const elemType &b)
             { return a.get_price() < b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
///////////////////Display sorted by their prices descending//////////////////////
    void displaySortedByPricedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const elemType &a, const elemType &b)
             { return a.get_price() > b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
};
//---------------------------------------------------------Heaps_Implementation------------------------------------------------------

//-----------------------------------------------------------mainfunctions-----------------------------------------------------------
template <typename TreeType>
void readItems(istream &file, TreeType &tree)
{
    int itemCount;
    file >> itemCount;
    file.ignore();

    for (int i = 0; i < itemCount; ++i)
    {
        string name, category;
        int price;
        getline(file, name);
        getline(file, category);
        file >> price;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        Item item(name, category, price);
        tree.insert(item);
    }
}
//---------------------------------------------------------------main----------------------------------------------------------------
int main()
{
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    // BST<Item> binarySearchTree;
    // AVL<Item> avltree;

    ifstream file("items.txt");
    if (file.is_open())
    {
        // readItems(file, avltree);
        // readItems(file, binarySearchTree);
        
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << "\n";
    }
////////////////////////////////////////////////////////Test_BST///////////////////////////////////////////
    // Item itemToSearch0 ("milkk","daidfsy",143);
    // binarySearchTree.insert(itemToSearch0);
    // binarySearchTree.deleteitem(itemToSearch0);
    

    // Item itemToSearch1 ("omar","day",1343);
    // binarySearchTree.insert(itemToSearch1);

    // Item itemToSearch2 ("ADADSFS","dadasdiry",13323);
    // binarySearchTree.insert(itemToSearch2);

    // Item itemToSearch3 ("pepsi","drink",20);
    // binarySearchTree.deleteitem(itemToSearch3);

    // Item itemToSearch4 ("fdgdg","candy",2);
    // binarySearchTree.insert(itemToSearch4);

    // Item itemToSearch0 ("apples","fruit",66);
    // binarySearchTree.deleteitem(itemToSearch0);
    // Item itemToSearch1 ("water","drink",9);
    // binarySearchTree.deleteitem(itemToSearch1);
    // Item itemToSearch2 ("mint gum","candy",2);
    // binarySearchTree.deleteitem(itemToSearch2);

    // cout << "Items in sorted order:" << endl;
    // binarySearchTree.Display();
    // cout << endl;

    // cout << "Items sorted by name ac:" << endl;
    // binarySearchTree.displaySortedByNameascending();
    // cout << endl;

    // cout << "Items sorted by price ac:" << endl;
    // binarySearchTree.displaySortedByPriceascending();
    // cout << endl;

    // cout << "Items sorted by name de:" << endl;
    // binarySearchTree.displaySortedByNamedescending();
    // cout << endl;

    // cout << "Items sorted by price de:" << endl;
    // binarySearchTree.displaySortedByPricedescending();
    // cout << endl;

////////////////////////////////////////////////////////Test_AVL///////////////////////////////////////////
    // Item itemToSearch5 ("milkk","daidfsy",143);
    // Item itemToSearch6 ("mint gum","candy",2);
    // Item itemToSearch1 ("omar","day",1343);
    // Item itemToSearch2 ("ADADSFS","dadasdiry",13323);
    // Item itemToSearch3 ("pepsi","drink",13);
    // Item itemToSearch4 ("wfdsdf","candy",2);
    // Item itemToSearch0 ("apples","fruit",66);
    // Item itemToSearch6 ("waterr","drink",9);

    // avltree.insert(itemToSearch5);
    // avltree.insert(itemToSearch1);
    // avltree.insert(itemToSearch2);
    // avltree.insert(itemToSearch3);
    // avltree.insert(itemToSearch4);
    // avltree.deleteitem(itemToSearch0);
    // avltree.deleteitem(itemToSearch6);
    // avltree.deleteitem(itemToSearch4);

    // cout << "Items in sorted order:" << endl;
    // avltree.Display();
    // cout << endl;

    // cout << "Items sorted by name ac:" << endl;
    // avltree.displaySortedByNameascending();
    // cout << endl;

    // cout << "Items sorted by price ac:" << endl;
    // avltree.displaySortedByPriceascending();
    // cout << endl;

    // cout << "Items sorted by name de:" << endl;
    // avltree.displaySortedByNamedescending();
    // cout << endl;

    // cout << "Items sorted by price de:" << endl;
    // avltree.displaySortedByPricedescending();
    // cout << endl;
////////////////////////////////////////////////////////Test_Heap///////////////////////////////////////////
        

    return 0;
}