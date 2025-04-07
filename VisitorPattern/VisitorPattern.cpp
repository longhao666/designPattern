﻿// VisitorPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

namespace LH1 {
// 菜鸟教程 https://www.runoob.com/design-pattern/design-pattern-intro.html
/*
访问者模式
在访问者模式（Visitor Pattern）中，我们使用了一个访问者类，它改变了元素类的执行算法。通过这种方式，元素的执行算法可以随着访问者改变而改变。这种类型的设计模式属于行为型模式。根据模式，元素对象已接受访问者对象，这样访问者对象就可以处理元素对象上的操作。

介绍
意图
旨在将数据结构与在该数据结构上执行的操作分离，从而使得添加新的操作变得更容易，而无需修改数据结构本身。

主要解决的问题
解决在稳定数据结构和易变操作之间的耦合问题，使得操作可以独立于数据结构变化。
使用场景
当需要对一个对象结构中的对象执行多种不同的且不相关的操作时，尤其是这些操作需要避免"污染"对象类本身。
实现方式
定义访问者接口：声明一系列访问方法，一个访问方法对应数据结构中的一个元素类。
创建具体访问者：实现访问者接口，为每个访问方法提供具体实现。
定义元素接口：声明一个接受访问者的方法。
创建具体元素：实现元素接口，每个具体元素类对应数据结构中的一个具体对象。
关键代码
访问者接口：包含访问不同元素的方法。
具体访问者：实现了访问者接口，包含对每个元素类的访问逻辑。
元素接口：包含一个接受访问者的方法。
具体元素：实现了元素接口，提供给访问者访问的入口。
应用实例
做客场景：访问者（如您）访问朋友家，朋友作为元素提供信息，访问者根据信息做出判断。
优点
单一职责原则：访问者模式符合单一职责原则，每个类只负责一项职责。
扩展性：容易为数据结构添加新的操作。
灵活性：访问者可以独立于数据结构变化。
缺点
违反迪米特原则：元素需要向访问者公开其内部信息。
元素类难以变更：元素类需要维持与访问者的兼容。
依赖具体类：访问者模式依赖于具体类而不是接口，违反了依赖倒置原则。
使用建议
当对象结构稳定，但需要在其上定义多种新操作时，考虑使用访问者模式。
当需要避免操作"污染"对象类时，使用访问者模式封装操作。
注意事项
访问者模式可以用于功能统一，如报表生成、用户界面显示、拦截器和过滤器等。
包含的几个主要角色
访问者（Visitor）：

定义了访问元素的接口。
具体访问者（Concrete Visitor）：

实现访问者接口，提供对每个具体元素类的访问和相应操作。
元素（Element）：

定义了一个接受访问者的方法。
具体元素（Concrete Element）：

实现元素接口，提供一个accept方法，允许访问者访问并操作。
对象结构（Object Structure）（可选）：

定义了如何组装具体元素，如一个组合类。
客户端（Client）（可选）：

使用访问者模式对对象结构进行操作。
*/


class ComputerPartVisitor;
class Computer;
class Mouse;
class Keyboard;
class Monitor;

class ComputerPartVisitor {
public:
	virtual void visit(Computer* computer) = 0;
	virtual void visit(Mouse* mouse) = 0;
	virtual void visit(Keyboard* keyboard) = 0;
	virtual void visit(Monitor* monitor) = 0;
};

class ComputerPart {
public:
	virtual void accept(ComputerPartVisitor* computerPartVisitor) = 0;
};



class Mouse : public ComputerPart {
public:
	virtual void accept(ComputerPartVisitor* computerPartVisitor) override {
		computerPartVisitor->visit(this);
	}
};

class Keyboard : public ComputerPart {
public:
	virtual void accept(ComputerPartVisitor* computerPartVisitor) override {
		computerPartVisitor->visit(this);
	}
};

class Monitor : public ComputerPart {
public:
	virtual void accept(ComputerPartVisitor* computerPartVisitor) override {
		computerPartVisitor->visit(this);
	}
};

class Computer : public ComputerPart {
public:
	Computer() {
		//parts = new ComputerPart{ new Mouse(), new Keyboard(), new Monitor() };
		parts.push_back(new Mouse());
		parts.push_back(new Keyboard());
		parts.push_back(new Monitor());
	}
	virtual void accept(ComputerPartVisitor* computerPartVisitor) override {
		for (int i = 0; i < parts.size(); i++) {
			parts[i]->accept(computerPartVisitor);
		}
		computerPartVisitor->visit(this);
	}
private:
	std::vector<ComputerPart*> parts;
	//ComputerPart* parts[];
};



class ComputerPartDisplayVisitor : public ComputerPartVisitor {
public:
	virtual void visit(Computer* computer) override {
		std::cout << "Displaying Computer." << "\n";
	}
	virtual void visit(Mouse* mouse) override {
		std::cout << "Displaying Mouse." << "\n";
	}
	virtual void visit(Keyboard* keyboard) override {
		std::cout << "Displaying keyboard." << "\n";
	}
	virtual void visit(Monitor* monitor) override {
		std::cout << "Displaying monitor." << "\n";
	}
};

void VisitorPatternDemo() {
	ComputerPart* computer = new Computer();
	computer->accept(new ComputerPartDisplayVisitor());
}

}

int main()
{
	LH1::VisitorPatternDemo();
    std::cout << "Hello World!\n";
}


