// ProxyPattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>


namespace LH1 {
	class Proxy {

	};

	class Subject {

	};

	class ProxySubject : Subject {

	};

	class VirtualSubject : Subject {

	};

	class RealSubject : Subject {

	};
}

namespace LH2 {
	class Image {
	public:
		virtual void Display() = 0;
	};

	class RealImage : public Image {
	public:
		RealImage(std::string _filename) {
			m_filename = _filename;
			std::cout << "Loading:" << m_filename << "\n";
		}

		virtual void Display() override {
			std::cout << "Displaying:" << m_filename << "\n";
		}

	private:
		std::string m_filename;

	};

	class ProxyImage : public Image {
	public:
		ProxyImage(std::string _fileName) {
			m_realImage = NULL;
			m_fileName = _fileName;
		}

		virtual void Display() override {
			if (m_realImage == NULL)
			{
				m_realImage = new RealImage(m_fileName);
			}
			m_realImage->Display();
		}

	private:
		RealImage* m_realImage;
		std::string m_fileName;
	};
}

int main()
{
	LH2::Image* image = new LH2::ProxyImage("test_10mb.jpg");

	// 图像将从磁盘加载
	image->Display();

	// 图像不需要从磁盘加载
	image->Display();

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
