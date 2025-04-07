// Interpreterpattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

// 菜鸟教程
namespace LH1 {
class Expression {
public:
	virtual bool Interpret(std::string _context) = 0;
};

class TerminalExpression : public Expression {
public:
	TerminalExpression(std::string _data) {
		m_data = _data;
	}
	virtual bool Interpret(std::string _context) override {
		if (m_data == _context)
		{
			return true;
		}
		return false;
	}

private:
	std::string m_data;
};

class AndExpression : public Expression {
public:
	AndExpression(Expression* expr1, Expression* expr2) {
		m_expr1 = expr1;
		m_expr2 = expr2;
	}
	virtual bool Interpret(std::string _context) override {
		return m_expr1->Interpret(_context) && m_expr2->Interpret(_context);
	}
private:
	Expression* m_expr1;
	Expression* m_expr2;
};

class OrExpression : public Expression {
public:
	OrExpression(Expression* expr1, Expression* expr2) {
		m_expr1 = expr1;
		m_expr2 = expr2;
	}
	virtual bool Interpret(std::string _context) override {
		return m_expr1->Interpret(_context) || m_expr2->Interpret(_context);
	}

private:
	Expression* m_expr1;
	Expression* m_expr2;
};

//规则：Robert 和 John 是男性
Expression* getMaleExpression() {
	Expression* robert = new TerminalExpression("Robert");
	Expression* john = new TerminalExpression("John");
	return new OrExpression(robert, john);
}

//规则：Julie 是一个已婚的女性
Expression* getMarriedWomanExpression() {
	Expression* julie = new TerminalExpression("Julie");
	Expression* married = new TerminalExpression("Married");
	return new AndExpression(julie, married);
}


void fun() {
	Expression* isMale = getMaleExpression();
	Expression* isMarriedWoman = getMarriedWomanExpression();

	std::cout << "John is male? " << isMale->Interpret("John") << "\n";
	std::cout << "Julie is a married women? " << isMarriedWoman->Interpret("Married Julie") << "\n";
}

}

int main()
{
	LH1::fun();

    std::cout << "Hello World!\n";
}
