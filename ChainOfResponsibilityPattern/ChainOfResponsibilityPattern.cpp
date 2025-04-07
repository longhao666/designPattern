﻿// ChainOfResponsibilityPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

namespace LH1 {
// 菜鸟教程  https://www.runoob.com/design-pattern/chain-of-responsibility-pattern.html
/*
责任链模式
责任链模式（Chain of Responsibility Pattern）为请求创建了一个接收者对象的链。这种模式给予请求的类型，对请求的发送者和接收者进行解耦。这种类型的设计模式属于行为型模式。

责任链模式通过将多个处理器（处理对象）以链式结构连接起来，使得请求沿着这条链传递，直到有一个处理器处理该请求为止。

责任链模式允许多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。

介绍
意图
允许将请求沿着处理者链传递，直到请求被处理为止。。

主要解决的问题
解耦请求发送者和接收者，使多个对象都有可能接收请求，而发送者不需要知道哪个对象会处理它。
使用场景
当有多个对象可以处理请求，且具体由哪个对象处理由运行时决定时。
当需要向多个对象中的一个提交请求，而不想明确指定接收者时。
实现方式
定义处理者接口：所有处理者必须实现同一个接口。
创建具体处理者：实现接口的具体类，包含请求处理逻辑和指向链中下一个处理者的引用。
关键代码
Handler接口：定义一个方法用于处理请求。
ConcreteHandler类：实现Handler接口，包含请求处理逻辑和对下一个处理者的引用。
应用实例
击鼓传花：游戏中的传递行为，直到音乐停止。
事件冒泡：在JavaScript中，事件从最具体的元素开始，逐级向上传播。
Web服务器：如Apache Tomcat处理字符编码，Struts2的拦截器，以及Servlet的Filter。
优点
降低耦合度：发送者和接收者之间解耦。
简化对象：对象不需要知道链的结构。
灵活性：通过改变链的成员或顺序，动态地新增或删除责任。
易于扩展：增加新的请求处理类很方便。
缺点
请求未被处理：不能保证请求一定会被链中的某个处理者接收。
性能影响：可能影响系统性能，且调试困难，可能导致循环调用。
难以观察：运行时特征不明显，可能妨碍除错。
使用建议
在处理请求时，如果有多个潜在的处理者，考虑使用责任链模式。
确保链中的每个处理者都明确知道如何传递请求到链的下一个环节。
注意事项
在Java Web开发中，责任链模式有广泛应用，如过滤器链、拦截器等。
结构
主要涉及到以下几个核心角色：

抽象处理者（Handler）:

定义一个处理请求的接口，通常包含一个处理请求的方法（如 handleRequest）和一个指向下一个处理者的引用（后继者）。
具体处理者（ConcreteHandler）:

实现了抽象处理者接口，负责处理请求。如果能够处理该请求，则直接处理；否则，将请求传递给下一个处理者。
客户端（Client）:

创建处理者对象，并将它们连接成一条责任链。通常，客户端只需要将请求发送给责任链的第一个处理者，无需关心请求的具体处理过程。
*/

class AbstractLogger {
public:
	static int INFO;
	static int DEBUG;
	static int ERROR;

protected:
	int level;

	//责任链中的下一个元素
protected:
	AbstractLogger* nextLogger;

public:
	void setNextLogger(AbstractLogger* nextLogger) {
		this->nextLogger = nextLogger;
	}

	void logMessage(int level, std::string message) {
		if (this->level <= level) {
			write(message);
		}
		if (nextLogger != NULL) {
			nextLogger->logMessage(level, message);
		}
	}
protected:
	virtual void write(std::string message) = 0;
};

int AbstractLogger::INFO = 1;
int AbstractLogger::DEBUG = 2;
int AbstractLogger::ERROR = 3;


class ConsoleLogger : public AbstractLogger {
public:
	ConsoleLogger(int level) {
		this->level = level;
	}

	
protected:
	virtual void write(std::string message) override{
		std::cout << "Standard Console::Logger: " << message << "\n";
	}
};

class ErrorLogger : public AbstractLogger {
public:
	ErrorLogger(int level) {
		this->level = level;
	}


protected:
	virtual void write(std::string message) override {
		std::cout << "error ErrorLogger::Logger: " << message << "\n";
	}
};


class FileLogger : public AbstractLogger {
public:
	FileLogger(int level) {
		this->level = level;
	}


protected:
	virtual void write(std::string message) override {
		std::cout << "FileLogger::Logger: " << message << "\n";
	}
};

AbstractLogger* getChainOfLoggers() {

	AbstractLogger* errorLogger = new ErrorLogger(AbstractLogger::ERROR);
	AbstractLogger *fileLogger = new FileLogger(AbstractLogger::DEBUG);
	AbstractLogger *consoleLogger = new ConsoleLogger(AbstractLogger::INFO);

	errorLogger->setNextLogger(fileLogger);
	fileLogger->setNextLogger(consoleLogger);

	return errorLogger;
}

void ChainOfResponsibilityPatternDemo() {
	AbstractLogger* loggerChain = getChainOfLoggers();

	loggerChain->logMessage(AbstractLogger::INFO, "This is an information.");

	loggerChain->logMessage(AbstractLogger::DEBUG, "This is a debug level information.");

	loggerChain->logMessage(AbstractLogger::ERROR, "This is an error information.");
}


}



int main()
{
	LH1::ChainOfResponsibilityPatternDemo();
    std::cout << "Hello World!\n";
}


