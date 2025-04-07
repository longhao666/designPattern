// IteratorPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

namespace LH1 {
// 菜鸟教程  
/*
迭代器模式
迭代器模式（Iterator Pattern）是 Java 和 .Net 编程环境中非常常用的设计模式。

迭代器模式提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露其内部的表示。

迭代器模式属于行为型模式。

介绍
意图
允许顺序访问一个聚合对象中的元素，同时不暴露对象的内部表示。

主要解决的问题
提供一种统一的方法来遍历不同的聚合对象。
使用场景
当需要遍历一个聚合对象，而又不希望暴露其内部结构时。
实现方式
定义迭代器接口：包含hasNext()和next()等方法，用于遍历元素。
创建具体迭代器：实现迭代器接口，定义如何遍历特定的聚合对象。
聚合类：定义一个接口用于返回一个迭代器对象。
关键代码
迭代器接口：规定了遍历元素的方法。
具体迭代器：实现了迭代器接口，包含遍历逻辑。
应用实例
Java中的Iterator：Java集合框架中的迭代器用于遍历集合元素。
优点
支持多种遍历方式：不同的迭代器可以定义不同的遍历方式。
简化聚合类：聚合类不需要关心遍历逻辑。
多遍历支持：可以同时对同一个聚合对象进行多次遍历。
扩展性：增加新的聚合类和迭代器类都很方便，无需修改现有代码。
缺点
系统复杂性：每增加一个聚合类，就需要增加一个对应的迭代器类，增加了类的数量。
使用建议
当需要访问聚合对象内容而不暴露其内部表示时，使用迭代器模式。
当需要为聚合对象提供多种遍历方式时，考虑使用迭代器模式。
注意事项
迭代器模式通过分离集合对象的遍历行为，使得外部代码可以透明地访问集合内部数据，同时不暴露集合的内部结构。
结构
迭代器模式包含以下几个主要角色：

迭代器接口（Iterator）：定义了访问和遍历聚合对象中各个元素的方法，通常包括获取下一个元素、判断是否还有元素、获取当前位置等方法。

具体迭代器（Concrete Iterator）：实现了迭代器接口，负责对聚合对象进行遍历和访问，同时记录遍历的当前位置。

聚合对象接口（Aggregate）：定义了创建迭代器对象的接口，通常包括一个工厂方法用于创建迭代器对象。

具体聚合对象（Concrete Aggregate）：实现了聚合对象接口，负责创建具体的迭代器对象，并提供需要遍历的数据
*/

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual void* next() = 0;
};

class Container {
public:
	virtual Iterator* GetIterator() = 0;

};





class NameRepository : public Container {
public:
	//std::string[] names = {"Robert" , "John" ,"Julie" , "Lora"};
	std::vector<std::string> names;
	NameRepository() {
		names.push_back("Robert");
		names.push_back("John");
		names.push_back("Julie");
		names.push_back("Lora");
	}

	Iterator* getIterator() {
		return new NameIterator();
	}

private:
	class NameIterator : public Iterator {
	private:
		int index;

	public:
		virtual bool hasNext() override {
			//if (index < names.size()) {
			//	return true;
			//}
			return false;
		}

		virtual void* next() override {
			//if (this->hasNext()) {
			//	return names[index++];
			//}
			return NULL;
		}
	};
};



void IteratorPatternDemo() {
	//NameRepository* namesRepository = new NameRepository();

	//for (Iterator* iter = namesRepository->getIterator(); iter->hasNext();) {
	//	std::string name = (std::string)iter.next();
	//	std::cout << "Name : " << name;
	//}
}

}

namespace LH2 {
// DeekSeek  https://chat.deepseek.com/a/chat/s/44e779f9-861f-4af9-a42d-33fb23945ea0


	// 迭代器接口
	class Iterator {
	public:
		virtual int next() = 0;       // 返回下一个元素
		virtual bool hasNext() = 0;   // 检查是否还有下一个元素
		virtual ~Iterator() = default;
	};

	// 具体迭代器
	class MyIterator : public Iterator {
	private:
		std::vector<int> data; // 数据集合
		size_t index;          // 当前索引

	public:
		MyIterator(const std::vector<int>& d) : data(d), index(0) {}

		int next() override {
			if (hasNext()) {
				return data[index++];
			}
			throw std::out_of_range("No more elements");
		}

		bool hasNext() override {
			return index < data.size();
		}
	};

	// 聚合接口
	class Aggregate {
	public:
		virtual Iterator* createIterator() = 0; // 创建迭代器
		virtual ~Aggregate() = default;
	};

	// 具体聚合类
	class MyCollection : public Aggregate {
	private:
		std::vector<int> data; // 数据集合

	public:
		void add(int value) {
			data.push_back(value);
		}

		Iterator* createIterator() override {
			return new MyIterator(data);
		}
	};

	// 客户端代码
	int IteratorPatternDemo() {
		MyCollection collection;
		collection.add(1);
		collection.add(2);
		collection.add(3);

		Iterator* it = collection.createIterator();
		while (it->hasNext()) {
			std::cout << it->next() << std::endl;
		}

		delete it; // 释放迭代器
		return 0;
	}
}

int main()
{
	LH2::IteratorPatternDemo();
    std::cout << "Hello World!\n";
}

