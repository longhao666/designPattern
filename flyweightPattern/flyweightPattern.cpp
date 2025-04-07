// flyweightPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <map>
#include <string>

// 单纯享元模式
namespace LH1 {
	class Flyweight {

	};

	class FlyweightFactory {

	};

	class ConcreteFlyweight1 : public Flyweight {

	};
}

// 复合享元模式
namespace LH2 {
	class Flyweight {

	};

	class FlyweightFactory {

	};

	class ConcreteFlyweight1 : public Flyweight {

	};

	class ConcreteCompositeFlyweight1 : public Flyweight {

	};
}

namespace LH3 {
	class Shape {
	public:
		virtual void Draw() = 0;
	};

	class Circle : public Shape {
	public:
		virtual void Draw() override{
			std::cout << "Circle: Draw() [Color : " << color << ", x : " << x << ", y :" << y << ", radius :" << radius << "\n";
		}

		void SetColor(std::string _color) {
			color = _color;
		}

	private:
		std::string color = "123";
		int x = 10;
		int y = 20;
		int radius = 3;
	};

	class ShapeFactory {
	public:
		static Shape* GetCircle(std::string _color) {
			Shape* shape = NULL;
			int iRet = m_mapCircleShape.count(_color);
			if (iRet == 0) {
				shape = new Circle();
				m_mapCircleShape.insert(std::pair<std::string, Shape*>(_color, shape));
				std::cout << "Creating circle of color : " << _color << "\n";
			}
			else {
				shape = m_mapCircleShape.at(_color);
			}
			return shape;
		}

		static Shape* GetCircle1(std::string _color) {
			std::cout << "123 "<< "\n";
			return NULL;
		}

		static Shape* GetCircle2(std::string _color) {
			std::cout << "123 " << "\n";
			return NULL;
		}


	private:
		static std::map<std::string, Shape*> m_mapCircleShape;
	};

}

std::map<std::string, LH3::Shape*> LH3::ShapeFactory::m_mapCircleShape = {};

int main()
{
	std::string colors[] = { "Red", "Green", "Blue", "White", "Black" };

	for (int i = 0; i < 20; ++i) {
		int j = i % 5;
		LH3::Circle* circle = (LH3::Circle*)LH3::ShapeFactory::GetCircle(colors[j]);
		circle->SetColor(colors[j]);
		circle->Draw();
	}
    std::cout << "Hello World!\n";
}
