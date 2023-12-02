#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>

using namespace std;

class ShopItem
{
protected:
	int id;
	string name;
	int price;
public:
	ShopItem(int _id, string _name, int _price) : name(_name), price(_price)
	{
		if (_id > 9999 || _id < 1000)
		{
			cout << "Incorrect ID!" << endl;
			cout << "ID have to contain 4 numbers, started with 1 or higher" << endl;
			cout << "ID is set to default: 1010" << endl;
			id = 1010;
		}
		else id = _id;
	}
	ShopItem(const ShopItem& a): id(a.id), name(a.name), price(a.price){}
	~ShopItem(){}
	void setId()
	{
		int a = 0;
		do
		{
			cout << "\nEnter new ID:" << endl;
			cin >> a;
			if (a > 9999 || a < 1000)
			{
				cout << "Incorrect ID!" << endl;
				cout << "Try again!" << endl;
			}
			else id = a;
		} while (a > 9999 || a < 1000);
	}
	void setPrice()
	{
		int a = 0;
		while (a == 0)
		{
			cout << "Enter new price: " << endl;
			cin >> a;
			price = a;
		}
	}
	void setName()
	{
		cout << "Enter new item name: " << endl;
		getline(cin, name);
	}

	void printItem()
	{
		cout << "\nItem ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Price: " << price << endl;
		cout << endl;
	}
	int getID() { return id; }
	string getName() { return name; }
	int getPrice() { return price; }

	ShopItem& operator=(ShopItem&& a)noexcept
	{
		if (&a == this)return *this;

		id = move(a.id);
		name = move(a.name);
		price = move(a.price);
		return *this;
	}

	bool operator==(const ShopItem& a)const
	{
		return (id == a.id &&
				name == a.name &&
				price == a.price);
	}
};

class ShopOrder
{
protected:
	vector<shared_ptr<ShopItem>> avalible;
	int total;
	map<shared_ptr<ShopItem>, int> cart;
public:
	ShopOrder() {};
	~ShopOrder() {};
	void addAvalible(shared_ptr<ShopItem> a){ avalible.push_back(a); }
	void checkout()
	{
		int choise = 0;
		int quantity = 0;
		char echoise = ' ';
		bool ext;
		map<shared_ptr<ShopItem>, int>::iterator it;

		do
		{
			cout << "Avalible items :" << endl;
			for (int i = 0; i < avalible.size(); ++i)
			{
				cout << i + 1 << ". ";
				avalible[i]->printItem();
			}

			cout << "Select one of the avalible items: " << endl; // выбор товара который хотим купить

			choise = 0;
			cin >> choise;
			while (choise > avalible.size() || choise < 1)
			{
				cout << "No product with this id was found!" << endl;
				cout << "Try again!" << endl;
				cin >> choise;
			}
			cout << "How many of these items do you want to add? (maximum - 10)" << endl; //выбираем количество которое хотим купить
			quantity = 0;
			cin >> quantity;
			while (quantity > 10 || quantity < 1)
			{
				cout << "You out of limits! \nMinimal amount: 1, Maximum: 10" << endl;
				cout << "Try again!" << endl;
				cin >> quantity;
			}
			for (int i = 0; i < avalible.size(); ++i) // добавляем товар в чек
			{
				if (cart.find(avalible[choise - 1]) == cart.end()) //если нет еще в чеке
				{
					cart.emplace(avalible[choise - 1], quantity);
					it = cart.find(avalible[choise - 1]);
					break;
				}
				else if (cart.find(avalible[choise - 1]) != cart.end()) //если уже есть
				{
					it = cart.find(avalible[choise - 1]);
					it->second += quantity;
					break;
				}
			}
			cout << endl;
			cout << "Your cart contain this items:" << endl; //вывод чека

			total = 0;	// при каждом выводе чека цена считается заново
			cout << "Item name\t Quanity\t Price for 1" << endl; 
			for (auto i = cart.begin(); i != cart.end(); ++i)
			{
				cout << setw(20) << left << i->first->getName();
				cout << setw(15) << i->second; 
				cout << setw(20) << i->first->getPrice() << endl;

				total += (i->first->getPrice() * i->second);
			}
			cout << "Total price: " << total << endl;

			cout << "\nWant to add something else?" << endl;  //если хотим добавить в чек что то еще или закончить операцию
			cout << "Type - y - to add some more. - n - to exit" << endl;
			cin >> echoise;
			while (echoise != 'y' && echoise != 'n')
			{
				cout << "Invalid input" << endl;
				cout << "Try again!" << endl;
				cin >> echoise;
			}
			if (echoise == 'y') ext = true;
			else if (echoise == 'n') ext = false;
			cout <<"\n" << endl;
		} while (ext != false);
	}
};


int main()
{
	auto key = make_shared<ShopItem>(1016, "Keyboard", 2800);
	auto mice = make_shared<ShopItem>(1230, "Mice", 2100);
	auto hset = make_shared<ShopItem>(1230, "Headset", 5000);

	ShopOrder shop;
	shop.addAvalible(key);
	shop.addAvalible(mice);
	shop.addAvalible(hset);

	shop.checkout();

	return 0;
}