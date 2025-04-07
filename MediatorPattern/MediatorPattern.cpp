// MediatorPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

namespace LH1 {
// 菜鸟教程 https://www.runoob.com/design-pattern/mediator-pattern.html
/*
中介者模式
中介者模式（Mediator Pattern）是用来降低多个对象和类之间的通信复杂性，属于行为型模式。

中介者模式定义了一个中介对象来封装一系列对象之间的交互。中介者使各对象之间不需要显式地相互引用，从而使其耦合松散，且可以独立地改变它们之间的交互。

介绍
意图
通过引入一个中介者对象来封装和协调多个对象之间的交互，从而降低对象间的耦合度。

主要解决的问题
解决对象间复杂的一对多关联问题，避免对象之间的高度耦合，简化系统结构。
使用场景
当系统中多个类相互耦合，形成网状结构时。
实现方式
定义中介者接口：规定中介者必须实现的接口。
创建具体中介者：实现中介者接口，包含协调各同事对象交互的逻辑。
定义同事类：各个对象不需要显式地相互引用，而是通过中介者来进行交互。
关键代码
中介者：封装了对象间的交互逻辑。
同事类：通过中介者进行通信。
应用实例
WTO：中国加入WTO后，各国通过WTO进行贸易，简化了双边关系。
机场调度系统：协调飞机起降、跑道使用等。
MVC框架：控制器作为模型和视图的中介者。
优点
降低复杂度：将多个对象间的一对多关系转换为一对一关系。
解耦：对象之间不再直接引用，通过中介者进行交互。
符合迪米特原则：对象只需知道中介者，不需要知道其他对象。
缺点
中介者复杂性：中介者可能会变得庞大和复杂，难以维护。
使用建议
当系统中对象间存在复杂的引用关系时，考虑使用中介者模式。
通过中介者封装多个类的行为，避免生成过多的子类。
注意事项
避免在职责不明确或混乱的情况下使用中介者模式，这可能导致中介者承担过多职责。
结构
中介者模式包含以下几个主要角色：

中介者（Mediator）：定义了一个接口用于与各个同事对象通信，并管理各个同事对象之间的关系。通常包括一个或多个事件处理方法，用于处理各种交互事件。

具体中介者（Concrete Mediator）：实现了中介者接口，负责实现各个同事对象之间的通信逻辑。它会维护一个对各个同事对象的引用，并协调它们的交互。

同事对象（Colleague）：定义了一个接口，用于与中介者进行通信。通常包括一个发送消息的方法，以及一个接收消息的方法。

具体同事对象（Concrete Colleague）：实现了同事对象接口，是真正参与到交互中的对象。它会将自己的消息发送给中介者，由中介者转发给其他同事对象。
*/

class User;
class ChatRoom;

class User {
private:
	std::string name;

public: 
	std::string getName() {
		return name;
	}

	void setName(std::string name) {
		this->name = name;
	}

	User(std::string name) {
		this->name = name;
	}

	void sendMessage(std::string message) {
		//ChatRoom::showMessage(this, message);
	}
};

class ChatRoom {
public:
	static void showMessage(User* user, std::string message) {
		std::cout << "250110:" << " [" + user->getName() << "] : " << message << "\n";
	}
};



void MediatorPatternDemo() {

}

}

namespace LH2 {
// DeepSeek https://chat.deepseek.com/a/chat/s/44e779f9-861f-4af9-a42d-33fb23945ea0


	// 前向声明
	class User;

	// 中介者接口
	class Mediator {
	public:
		virtual void sendMessage(const std::string& message, User* user) = 0;
	};

	// 同事类：用户
	class User {
	private:
		std::string name;
		Mediator* mediator;  // 每个用户都知道中介者

	public:
		User(const std::string& name, Mediator* mediator)
			: name(name), mediator(mediator) {}

		void send(const std::string& message) {
			std::cout << name << " 发送消息: " << message << std::endl;
			mediator->sendMessage(message, this);  // 通过中介者发送消息
		}

		void receive(const std::string& message) {
			std::cout << name << " 收到消息: " << message << std::endl;
		}
	};

	// 具体中介者：聊天室
	class ChatRoom : public Mediator {
	private:
		std::vector<User*> users;  // 存储所有用户

	public:
		void addUser(User* user) {
			users.push_back(user);
		}

		void sendMessage(const std::string& message, User* user) override {
			for (auto u : users) {
				// 不将消息发送给自己
				if (u != user) {
					u->receive(message);
				}
			}
		}
	};



	// 客户端代码
	int MediatorPatternDemo() {
		// 创建中介者（聊天室）
		ChatRoom chatRoom;

		// 创建用户
		User user1("Alice", &chatRoom);
		User user2("Bob", &chatRoom);
		User user3("Charlie", &chatRoom);

		// 将用户添加到聊天室
		chatRoom.addUser(&user1);
		chatRoom.addUser(&user2);
		chatRoom.addUser(&user3);

		// 用户发送消息
		user1.send("大家好！");
		user2.send("你好，Alice！");
		user3.send("欢迎来到聊天室！");

		return 0;
	}

}

int main()
{
	LH2::MediatorPatternDemo();
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
