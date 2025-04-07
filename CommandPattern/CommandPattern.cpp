// CommandPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>

namespace LH1 {

// 命令接口
class Order {
public:
	virtual void Execute() = 0;

};

// 请求类
class Stock {
public:
	void Buy() {
		std::cout << "Buy" << "\n";
	}

	void Sell() {
		std::cout << "Sell" << "\n";
	}


private:
	std::string m_name;
	int m_quantigy;
};

// 实体类
class BuyStock : public Order {
public:
	BuyStock(Stock* abcStock) {
		m_stock = abcStock;
	}

	virtual void Execute() override {
		std::cout << "BuyStock" << "\n";
		m_stock->Buy();
	}



private:
	Stock* m_stock;

};
// 实体类
class SellStock : public Order {
public:
	SellStock(Stock* abcStock) {
		m_stock = abcStock;
	}

	virtual void Execute() override {
		std::cout << "SellStock" << "\n";
		m_stock->Sell();
	}

private:
	Stock* m_stock;

};
// 命令调用类
class Broker {
public:
	void TakeOrder(Order* _order) {
		m_order.push_back(_order);
	}

	void PlaceOrder() {
		for (auto& itr : m_order)
		{
			itr->Execute();
		}
		m_order.clear();
	}

private:
	std::list<Order*> m_order;


};

void fun() {
	Stock* s = new Stock();

	BuyStock* buy = new BuyStock(s);
	SellStock* sell = new SellStock(s);

	Broker* b = new Broker();

	b->TakeOrder(buy);
	b->TakeOrder(sell);

	b->PlaceOrder();

}

}

int main()
{
	LH1::fun();

    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
