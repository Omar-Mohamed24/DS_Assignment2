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

    BSTNode(const T& key) : Key(key), leftlink(nullptr), rightlink(nullptr) {}
};
//************************************************************************
template <typename T>
class BST
{
private:
    BSTNode<T> *root;

public:
    BST() : root(NULL) {}
    BSTNode<T>* getroot() const {return root;}
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
        items.push_back(node->Key);  // Visit the root node first
        preOrder(node->leftlink, items);  // Then traverse the left subtree
        preOrder(node->rightlink, items);  // Finally traverse the right subtree
    }
/////////////////////Search////////////////////////////////
    bool search(const T &el) const
    {
        bool found = false;
        if (root == NULL)
            cout << "Cannot search the empty tree." << "\n";
        else
        {
            BSTNode<T> *p = root;
            while (p != NULL && !found)
            {
                if (el == p->Key)
                {
                    found = true;
                }
                else if (el < p->Key)
                {
                    p = p->leftlink;
                }
                else
                {
                    p = p->rightlink;
                }
            }
        }
        return found;
    }
////////////////////////// insert///////////////////////////
    void insert(const T& insertItem)
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
/////////////////////////remove////////////////////////////
    void deleteNode (BSTNode<T>*& node,const T& deleteItem) 
    {
        BSTNode<T>* temp,*current,*prev;
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
            if(node->leftlink == NULL && node->rightlink == NULL)
            {
                node = nullptr;
                delete node;
            }
            else if(node->leftlink == NULL)
            {
                temp = node;
                node = node->rightlink;
                delete temp;
            }
            else if(node->rightlink == NULL)
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

    void deleteitem(const T& deleteItem) 
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
        sort(items.begin(), items.end(), [](const T &a, const T &b) { return a.get_price() < b.get_price(); });
        
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
        sort(items.begin(), items.end(), [](const T &a, const T &b) { return a.get_price() > b.get_price(); });
        
        for (const auto &item : items)
        {
            item.display();
        }
    }
};
//---------------------------------------------------------AVL_Implementation--------------------------------------------------------

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
    BST<Item> binarySearchTree;

    ifstream file("items.txt");
    if (file.is_open())
    {
        readItems(file,binarySearchTree);
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << "\n";
    }

    // Item itemToSearch0 ("milkk","daidfsy",143);
    // binarySearchTree.insert(itemToSearch0);

    // Item itemToSearch1 ("omar","day",1343);
    // binarySearchTree.insert(itemToSearch1);

    // Item itemToSearch2 ("ADADSFS","dadasdiry",13323);
    // binarySearchTree.insert(itemToSearch2);

    // Item itemToSearch3 ("pepsi","drink",13);
    // binarySearchTree.insert(itemToSearch3);

    // Item itemToSearch4 ("A7A","candy",2);
    // binarySearchTree.insert(itemToSearch4);
    
    // cout << "Items in sorted order:" << endl;
    // binarySearchTree.Display();
    // cout << endl;

    // cout << "Items sorted by name ac:" << endl;
    // binarySearchTree.displaySortedByNameascending();
    // cout << endl;

    // Item itemToSearch0 ("apples","fruit",66);
    // binarySearchTree.deleteitem(itemToSearch0);
    // Item itemToSearch1 ("water","drink",9);
    // binarySearchTree.deleteitem(itemToSearch1);
    // Item itemToSearch2 ("mint gum","candy",2);
    // binarySearchTree.deleteitem(itemToSearch2);

    // cout << "Items sorted by price ac:" << endl;
    // binarySearchTree.displaySortedByPriceascending();
    // cout << endl;

    // cout << "Items sorted by name de:" << endl;
    // binarySearchTree.displaySortedByNamedescending();
    // cout << endl;

    // cout << "Items sorted by price de:" << endl;
    // binarySearchTree.displaySortedByPricedescending();
    // cout << endl;

    return 0;
}