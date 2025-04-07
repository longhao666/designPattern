// MementoPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

namespace LH1 {

}

namespace LH2 {
// DeepSeek https://chat.deepseek.com/a/chat/s/e9926d4e-698c-4438-ae0a-36f3d54a7f57

/*
代码说明
Memento（备忘录类）：

用于保存文本编辑器的状态（text）。

提供了 getState 方法，用于获取保存的状态。

TextEditor（原发器类）：

负责创建备忘录（createMemento）和从备忘录恢复状态（restoreFromMemento）。

提供了 setText 和 getText 方法，用于设置和获取当前文本内容。

Caretaker（管理者类）：

负责存储和管理备忘录的历史记录。

提供了 addMemento 和 getMemento 方法，用于添加和获取备忘录。

客户端代码：

创建了一个文本编辑器和一个管理者。

编辑文本并保存状态到备忘录中。

通过备忘录恢复到之前的状态。

输出结果
复制
当前文本: Version 3
恢复到第一个状态: Version 1
恢复到第二个状态: Version 2
备忘录模式的优点
封装性好：备忘录模式将对象的状态保存在外部，但不会暴露对象的内部实现细节。

支持撤销操作：可以轻松实现撤销功能，恢复到之前的状态。

简化原发器职责：原发器不需要关心状态的存储和管理，职责更加单一。

适用场景
当需要保存对象的状态并在以后恢复时。

当需要实现撤销（Undo）或回滚（Rollback）功能时。

当直接访问对象的内部状态会破坏封装性时。
*/

// 备忘录类：保存文本编辑器的状态
	class Memento {
	private:
		std::string state;  // 保存的状态

	public:
		Memento(const std::string& state) : state(state) {}

		// 获取保存的状态
		std::string getState() const {
			return state;
		}
	};

	// 原发器类：文本编辑器
	class TextEditor {
	private:
		std::string text;  // 当前文本内容

	public:
		// 设置文本内容
		void setText(const std::string& text) {
			this->text = text;
		}

		// 获取当前文本内容
		std::string getText() const {
			return text;
		}

		// 创建备忘录：保存当前状态
		Memento createMemento() const {
			return Memento(text);
		}

		// 恢复状态：从备忘录恢复
		void restoreFromMemento(const Memento& memento) {
			text = memento.getState();
		}
	};

	// 管理者类：负责保存和管理备忘录
	class Caretaker {
	private:
		std::vector<Memento> mementos;  // 存储备忘录的历史记录

	public:
		// 添加备忘录
		void addMemento(const Memento& memento) {
			mementos.push_back(memento);
		}

		// 获取指定索引的备忘录
		Memento getMemento(size_t index) const {
			if (index < mementos.size()) {
				return mementos[index];
			}
			throw std::out_of_range("Invalid index");
		}
	};

	// 客户端代码
	int main() {
		TextEditor editor;
		Caretaker caretaker;

		// 编辑文本并保存状态
		editor.setText("Version 1");
		caretaker.addMemento(editor.createMemento());

		editor.setText("Version 2");
		caretaker.addMemento(editor.createMemento());

		editor.setText("Version 3");
		caretaker.addMemento(editor.createMemento());

		// 输出当前文本
		std::cout << "当前文本: " << editor.getText() << std::endl;

		// 恢复到第一个保存的状态
		editor.restoreFromMemento(caretaker.getMemento(0));
		std::cout << "恢复到第一个状态: " << editor.getText() << std::endl;

		// 恢复到第二个保存的状态
		editor.restoreFromMemento(caretaker.getMemento(1));
		std::cout << "恢复到第二个状态: " << editor.getText() << std::endl;

		return 0;
	}


}

namespace LH3 {


	class MyClass {
	public:
		// 成员函数模板
		template <typename T>
		void print(const std::string& str, const T& value);
	};

	// 成员函数模板的定义
	template <typename T>
	void MyClass::print(const std::string& str, const T& value) {
		std::cout << "Generic template: " << value << std::endl;
	}

	// 特例化 int 版本
	template <>
	void MyClass::print<int>(const std::string& str, const int& value) {
		std::cout << "Specialized template for int: " << value << std::endl;
	}
}

int main()
{
	LH2::main();

	LH3::MyClass my;
	my.print("123", 1);
	my.print("123", "123");
	my.print("123", 1.2);
    std::cout << "Hello World!\n";
}


