// strategyPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

namespace LH1 {

	class Stragety {
	public:
		virtual void handle(int i, int j) = 0;
	};

	class Context {
	public:
		void SetStragety(Stragety* _stragety) {
			m_stragety = _stragety;
		}
		void handle(int i, int j) {
			m_stragety->handle(i, j);
		}


	private:
		Stragety* m_stragety;
	};

	class Stragety1 : public Stragety {
	public:
		virtual void handle(int i, int j) override {
			std::cout << i+j << "Hello World! Stragety1 \n";
		}
	};
	class Stragety2 : public Stragety {
	public:
		virtual void handle(int i, int j) override {
			std::cout << i - j << "Hello World! Stragety2 \n";
		}
	};
}

namespace LH2 {
// 菜鸟教程   https://www.runoob.com/design-pattern/strategy-pattern.html
/*
策略模式
在策略模式（Strategy Pattern）中一个类的行为或其算法可以在运行时更改。这种类型的设计模式属于行为型模式。

在策略模式定义了一系列算法或策略，并将每个算法封装在独立的类中，使得它们可以互相替换。通过使用策略模式，可以在运行时根据需要选择不同的算法，而不需要修改客户端代码。

在策略模式中，我们创建表示各种策略的对象和一个行为随着策略对象改变而改变的 context 对象。策略对象改变 context 对象的执行算法。

介绍
意图
将每个算法封装起来，使它们可以互换使用。

主要解决的问题
解决在多种相似算法存在时，使用条件语句（如if...else）导致的复杂性和难以维护的问题。
使用场景
当一个系统中有许多类，它们之间的区别仅在于它们的行为时。
实现方式
定义策略接口：所有策略类都将实现这个统一的接口。
创建具体策略类：每个策略类封装一个具体的算法或行为。
上下文类：包含一个策略对象的引用，并通过该引用调用策略。
关键代码
策略接口：规定了所有策略类必须实现的方法。
具体策略类：实现了策略接口，包含具体的算法实现。
应用实例
锦囊妙计：每个锦囊代表一个策略，包含不同的计策。
旅行方式选择：骑自行车、坐汽车等，每种方式都是一个可替换的策略。
Java AWT的LayoutManager：不同的布局管理器实现了相同的接口，但提供了不同的布局算法。
优点
算法切换自由：可以在运行时根据需要切换算法。
避免多重条件判断：消除了复杂的条件语句。
扩展性好：新增算法只需新增一个策略类，无需修改现有代码。
缺点
策略类数量增多：每增加一个算法，就需要增加一个策略类。
所有策略类都需要暴露：策略类需要对外公开，以便可以被选择和使用。
使用建议
当系统中有多种算法或行为，且它们之间可以相互替换时，使用策略模式。
当系统需要动态选择算法时，策略模式是一个合适的选择。
注意事项
如果系统中策略类数量过多，考虑使用其他模式或设计技巧来解决类膨胀问题。
结构
策略模式包含以下几个核心角色：

环境（Context）：维护一个对策略对象的引用，负责将客户端请求委派给具体的策略对象执行。环境类可以通过依赖注入、简单工厂等方式来获取具体策略对象。
抽象策略（Abstract Strategy）：定义了策略对象的公共接口或抽象类，规定了具体策略类必须实现的方法。
具体策略（Concrete Strategy）：实现了抽象策略定义的接口或抽象类，包含了具体的算法实现。
策略模式通过将算法与使用算法的代码解耦，提供了一种动态选择不同算法的方法。客户端代码不需要知道具体的算法细节，而是通过调用环境类来使用所选择的策略。
*/

	class LayoutManager {

	};

	class Container {
	public:
		void SetLayout(LayoutManager* _layout) {
			m_layoutMgr = _layout;
		}
		LayoutManager* GetLayout() {
			return m_layoutMgr;
		}

	private:
		LayoutManager* m_layoutMgr;
	};

	class Stragety1 : public LayoutManager {

	};

	class Stragety2 : public LayoutManager {

	};
}

int main()
{
	LH1::Context c;

	c.SetStragety(new LH1::Stragety1());
	c.handle(10, 5);
	c.SetStragety(new LH1::Stragety2());
	c.handle(10, 5);


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
