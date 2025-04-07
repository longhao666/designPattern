// FilterPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <algorithm>

namespace LH1 {
// 菜鸟教程 https://www.runoob.com/design-pattern/filter-pattern.html
/*
过滤器模式
过滤器模式（Filter Pattern）或标准模式（Criteria Pattern）是一种设计模式，这种模式允许开发人员使用不同的标准来过滤一组对象，通过逻辑运算以解耦的方式把它们连接起来。这种类型的设计模式属于结构型模式，它结合多个标准来获得单一标准。

概要
意图
用于将对象的筛选过程封装起来，允许使用不同的筛选标准动态地筛选对象。

主要解决的问题
当需要根据多个不同的条件或标准来筛选一组对象时，过滤器模式提供了一种灵活的方式来定义这些条件，避免在客户端代码中硬编码筛选逻辑。

使用场景
当对象集合需要根据不同的标准进行筛选时。
当筛选逻辑可能变化，或者需要动态地组合多个筛选条件时。
实现方式
定义筛选接口：创建一个筛选接口，定义一个筛选方法。
实现具体筛选器：为每个筛选标准实现筛选接口，封装具体的筛选逻辑。
组合筛选器：允许筛选器之间进行组合，形成复杂的筛选逻辑。
关键代码
筛选接口：定义筛选方法，如 matches()。
具体筛选器类：实现筛选接口，封装具体的筛选逻辑。
组合筛选器：实现筛选器的组合逻辑，如逻辑与（AND）、逻辑或（OR）等。
应用实例
图书管理系统：根据作者、出版年份、类别等不同标准筛选图书。
在线购物平台：根据价格、品牌、用户评分等条件筛选商品。
优点
封装性：筛选逻辑被封装在独立的筛选器对象中。
灵活性：可以动态地添加、修改或组合筛选条件。
可扩展性：容易添加新的筛选标准，无需修改现有代码。
缺点
复杂性：随着筛选条件的增加，系统可能变得复杂。
性能问题：如果筛选器组合过于复杂，可能会影响性能。
使用建议
当筛选逻辑可能变化或需要根据不同标准动态筛选对象时，考虑使用过滤器模式。
在设计时，确保筛选器的接口和实现保持一致，以便于组合和扩展。
注意事项
确保筛选器的组合逻辑正确无误，避免引入逻辑错误。
在实现时，考虑性能影响，特别是在处理大量数据时。
概要
过滤器模式包含以下几个主要角色：

过滤器接口（Filter/Criteria）：定义一个接口，用于筛选对象。该接口通常包含一个方法，用于根据特定条件过滤对象。

具体过滤器类（Concrete Filter/Concrete Criteria）：实现过滤器接口，具体定义筛选对象的条件和逻辑。

对象集合（Items/Objects to be filtered）：要被过滤的对象集合。这些对象通常是具有共同属性的实例，例如一组人、一组产品等。

客户端（Client）：使用具体过滤器类来筛选对象集合。客户端将对象集合和过滤器结合起来，以获得符合条件的对象。
*/

class Person;


class Criteria {
public:
	virtual std::list<Person*> meetCriteria(std::list<Person*> _vecPerson) = 0;
protected:
	//std::list<Person*> m_vecPerson;
	
};

class Person {


public:
	Person() {

	}
	Person(std::string name, std::string gender, std::string maritalStatus) {
		this->m_strName = name;
		this->m_strGender = gender;
		this->m_strMaritalStatus = maritalStatus;
	}
	bool operator==(const Person& other) const {
		return m_strName == other.m_strName && m_strGender == other.m_strGender && m_strMaritalStatus == other.m_strMaritalStatus;
	}
	std::string getName() {
		return m_strName;
	}
	std::string getGender() {
		return m_strGender;
	}
	std::string getMaritalStatus() {
		return m_strMaritalStatus;
	}
private:
	std::string m_strName;
	std::string m_strGender;
	std::string m_strMaritalStatus;
};



class CriteriaFemale : public Criteria {
public:
	virtual std::list<Person*> meetCriteria(std::list<Person*> _vecPerson) override {
		std::list<Person*> femalePersons;
		for (Person* person : _vecPerson) {
			if (person->getGender().compare("FEMALE") == 0) {
				femalePersons.push_back(person);
			}
		}
		return femalePersons;
	}
};

class CriteriaMale : public Criteria {
public:
	virtual std::list<Person*> meetCriteria(std::list<Person*> _vecPerson) override {
		std::list<Person*> malePersons;
		for (Person* person : _vecPerson) {
			if (person->getGender().compare("MALE") == 0) {
				malePersons.push_back(person);
			}
		}
		return malePersons;
	}
};

class CriteriaSingle : public Criteria {
public:
	virtual std::list<Person*> meetCriteria(std::list<Person*> _vecPerson) override {
		std::list<Person*> singlePersons;
		for (Person* person : _vecPerson) {
			if (person->getMaritalStatus().compare("SINGLE") == 0) {
				singlePersons.push_back(person);
			}
		}
		return singlePersons;
	}
};

class AndCriteria : public Criteria {
public:
	AndCriteria(Criteria* _criteria, Criteria* _otherCriteria) {
		criteria = _criteria;
		otherCriteria = _otherCriteria;
	}

	virtual std::list<Person*> meetCriteria(std::list<Person*> _vecPerson) override {
		std::list<Person*> firstCriteriaPersons = criteria->meetCriteria(_vecPerson);
		return otherCriteria->meetCriteria(firstCriteriaPersons);
	}


private:
	Criteria* criteria;
	Criteria* otherCriteria;

};

class OrCriteria : public Criteria {
public:
	OrCriteria(Criteria* _criteria, Criteria* _otherCriteria) {
		criteria = _criteria;
		otherCriteria = _otherCriteria;
	}

	virtual std::list<Person*> meetCriteria(std::list<Person*> _vecPerson) override {
		std::list<Person*> firstCriteriaItems = criteria->meetCriteria(_vecPerson);
		std::list<Person*> otherCriteriaItems = otherCriteria->meetCriteria(_vecPerson);
		Person tmp;
		for (Person* person : otherCriteriaItems) {

			//tmp = *person;
			//auto itr = std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person);

			//auto itr = std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), tmp);
			//auto itr = std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), [](auto obj1, auto obj2) {
			//	return true; 
			//});
			if (std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person) == firstCriteriaItems.end()) {
				firstCriteriaItems.push_back(person);
			}
		}
		return firstCriteriaItems;
	}


private:
	Criteria* criteria;
	Criteria* otherCriteria;
};


class MyClass {
public:
	int id;
	std::string name;

	// 重载 == 运算符
	bool operator==(const MyClass& other) const {
		return id == other.id && name == other.name;
	}
};

void CriteriaPatternDemo() {
	Person tmp;

	Person tmp2;

	bool b = tmp == tmp2;

	std::vector<MyClass> vec = { {1, "Alice"}, {2, "Bob"}, {3, "Charlie"} };

	// 查找 id 为 2 的对象
	MyClass target = { 2, "Bob" };
	auto it = std::find(vec.begin(), vec.end(), target);

	if (it != vec.end()) {
		std::cout << "找到对象: " << it->name << std::endl;
	}
	else {
		std::cout << "未找到对象" << std::endl;
	}
}

void printPersons(std::list<Person*> persons) {
	for (Person* person : persons) {
		std::cout << "Person : [ Name : " + person->getName()
			<< ", Gender : " + person->getGender()
			<< ", Marital Status : " + person->getMaritalStatus()
			<< " ]" << "\n";
	}
}

void CriteriaPatternDemo2() {
	std::list<Person*> persons;

	persons.push_back(new Person("ROBERT", "MALE", "SINGLE"));
	persons.push_back(new Person("JOHN", "MALE", "MARRIED"));
	persons.push_back(new Person("LAURA", "FEMALE", "MARRIED"));
	persons.push_back(new Person("DIANA", "FEMALE", "SINGLE"));
	persons.push_back(new Person("MIKE", "MALE", "SINGLE"));
	persons.push_back(new Person("BOBBY", "MALE", "SINGLE"));

	Criteria* male = new CriteriaMale();
	Criteria* female = new CriteriaFemale();
	Criteria* single = new CriteriaSingle();
	Criteria* singleMale = new AndCriteria(single, male);
	Criteria* singleOrFemale = new OrCriteria(single, female);

	std::cout << "Males:" << "\n";
	printPersons(male->meetCriteria(persons));

	std::cout << "\nFemales:" << "\n";
	printPersons(female->meetCriteria(persons));

	std::cout << "\nSingle Males:" << "\n";
	printPersons(singleMale->meetCriteria(persons));

	std::cout << "\nSingle Or Females:" << "\n";
	printPersons(singleOrFemale->meetCriteria(persons));
}



}


namespace LHtest {
	template <typename T>
	class MySingleton
	{
	public:
		static T& GetInstance()
		{
			static T t;
			return t;
		}
		static T* GetInstance1()
		{
			static T t;
			return &t;
		}
	protected:
		MySingleton() {}
	};

	class A {
	friend MySingleton<A>;
	private:
		A() {
			int b = 10;
		}
	//public:
		//A(const A& _a) {
		//	a = _a.a;
		//	int b = 10;
		//}
	public:
		A& operator=(const A& _a) {
			this->a = _a.a;
			return *this;
		}
	public:
		~A() {

		}

		int a = 10;

	};

	void Demo() {
		auto pSpaTread = MySingleton<A>::GetInstance();
		pSpaTread.a = 20;
		std::cout << pSpaTread.a << "," << MySingleton<A>::GetInstance().a << std::endl;
		auto pSpaTread1 = MySingleton<A>::GetInstance1();
		*pSpaTread1 = pSpaTread;
		//pSpaTread1->a = 20;
		//std::cout << pSpaTread1->a << "," << MySingleton<A>::GetInstance1()->a << std::endl;
	}
}
int main()
{
	//LHtest::Demo();
	LH1::CriteriaPatternDemo2();
    std::cout << "Hello World!\n";
}

