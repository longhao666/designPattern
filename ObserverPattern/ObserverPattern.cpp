// ObserverPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>

namespace LH1 {
// 菜鸟教程
/*
观察者模式包含以下几个核心角色：

主题（Subject）：也称为被观察者或可观察者，它是具有状态的对象，并维护着一个观察者列表。主题提供了添加、删除和通知观察者的方法。
观察者（Observer）：观察者是接收主题通知的对象。观察者需要实现一个更新方法，当收到主题的通知时，调用该方法进行更新操作。
具体主题（Concrete Subject）：具体主题是主题的具体实现类。它维护着观察者列表，并在状态发生改变时通知观察者。
具体观察者（Concrete Observer）：具体观察者是观察者的具体实现类。它实现了更新方法，定义了在收到主题通知时需要执行的具体操作。
观察者模式通过将主题和观察者解耦，实现了对象之间的松耦合。当主题的状态发生改变时，所有依赖于它的观察者都会收到通知并进行相应的更新。
*/
// 主题   发布  也称为被观察者或可观察者，它是具有状态的对象，并维护着一个观察者列表。主题提供了添加、删除和通知观察者的方法。

class Observer;
class Subject;

// 观察者 订阅
class Observer {
public:
	virtual void Update() = 0;
protected:
	Subject* m_subject;
};

class Subject {
public:
	void SetState(int _state) {
		m_iState = _state;
		NotifyAllObservers();
	};
	int GetState() {
		return m_iState;
	};
	void Attach(Observer* _observer) {
		m_listObserver.push_back(_observer);
	};
	void NotifyAllObservers() {
		for (auto& itr : m_listObserver)
		{
			itr->Update();
		}
	};

private:
	std::list<Observer*> m_listObserver;
	int m_iState;
};


class BinaryObserver : public Observer {
public:
	BinaryObserver(Subject* _subject) {
		m_subject = _subject;
		m_subject->Attach(this);
	}
	virtual void Update() override {
		std::cout << "Binary String: " << std::dec << m_subject->GetState() << "\n";
	}
};

class OctalObserver : public Observer {
public:
	OctalObserver(Subject* _subject) {
		m_subject = _subject;
		m_subject->Attach(this);
	}
	virtual void Update() override {
		std::cout << "Octal String: " << std::oct <<  m_subject->GetState() << "\n";
	}
};

class HexaObserver : public Observer {
public:
	HexaObserver(Subject* _subject) {
		m_subject = _subject;
		m_subject->Attach(this);
	}
	virtual void Update() override {
		std::cout << "Hexa String: " << std::hex <<  m_subject->GetState() << "\n";
	}
};

void ObserverPatternDemo() {
	Subject* s = new Subject();

	BinaryObserver *b = new BinaryObserver(s);
	OctalObserver *o = new OctalObserver(s);
	HexaObserver *h = new HexaObserver(s);

	s->SetState(1);
	s->SetState(20);
}






}

int main()
{
	LH1::ObserverPatternDemo();
    std::cout << "Hello World!\n";
}

