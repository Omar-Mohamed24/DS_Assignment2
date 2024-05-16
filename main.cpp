#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
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
}

void Item::display() const
{
    display(cout);
}

bool operator<(const Item &I1, const Item &I2)
{
    return I1.itemName < I2.itemName;
}

bool operator>(const Item &I1, const Item &I2)
{
    return I1.itemName > I2.itemName;
}

bool operator==(const Item &I1, const Item &I2)
{
    return I1.itemName == I2.itemName;
}
//---------------------------------------------------------BST_Implementation--------------------------------------------------------
template <typename T>
class BSTNode
{
private:
    T Key;
    BSTNode *left;
    BSTNode *right;

public:
    BSTNode()
    {
        left = right = NULL;
    }

    BSTNode(const T &i, BSTNode *l = 0, BSTNode *r = 0)
    {
        Key = i;
        left = l;
        right = r;
    }

    BSTNode *getLeft() { return left; }
    BSTNode *getRight() { return right; }
    T getKey() { return Key; }
};
//                                        **************************************************
template <typename T>
class BST
{
private:
    BSTNode<T> *root;

public:
    BST() : root(nullptr) {}
    void clear() { root = 0; }
    bool isEmpty() { return root == 0; }

    T *search(T &el)
    {
        BSTNode<T> *p = root;
        while (p != 0)
        {
            if (el == p->getKey())
            {
                return &p->getKey();
            }
            else if (el < p->getKey())
            {
                p = p->getLeft();
            }
            else
            {
                p = p->getRight();
            }
        }
        return nullptr;
    }

    
};
//---------------------------------------------------------AVL_Implementation--------------------------------------------------------

//---------------------------------------------------------Heaps_Implementation------------------------------------------------------

//-----------------------------------------------------------mainfunctions-----------------------------------------------------------
template <typename TreeType>
void readItems(istream &file, TreeType &tree)
{
    int itemCount;
    input >> itemCount;
    input.ignore();

    for (int i = 0; i < itemCount; ++i)
    {
        string name, category;
        int price;
        getline(input, name);
        getline(input, category);
        input >> price;
        input.ignore(numeric_limits<streamsize>::max(), '\n');
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

    ifstream file("items.txt");
    if (file.is_open())
    {
        // readItems(file, bst, heap, avl);
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << "\n";
    }

    return 0;
}
