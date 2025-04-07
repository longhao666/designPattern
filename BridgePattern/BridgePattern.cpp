// BridgePattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

// 菜鸟教程 https://www.runoob.com/design-pattern/bridge-pattern.html
namespace LH1 {
// 桥接模式

class DrawAPI;
class Shape {
public:
	Shape() {

	}
	virtual void Draw() = 0;

private:
	DrawAPI* m_drawApi;
};

class DrawAPI {
public:	
	virtual void DrawCircle() = 0;
};

class Circle : public Shape {

};

class RedCircle : public DrawAPI {
public:
	virtual void DrawCircle() override {

	}
};

class GreenCircle : public DrawAPI {
public:
	virtual void DrawCircle() override {

	}
};

void BridgePatternDemo() {

}



}

int main()
{
    std::cout << "Hello World!\n";
}


