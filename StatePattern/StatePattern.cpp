// StatePattern.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <vector>


namespace LH1 {


	class State;
	class Context;

	class State
	{
	public:
		virtual void handle(Context* _context) = 0;
	};

	class Context
	{
	public:
		Context(State *_state)
		{
			m_state = _state;
		}

		void handle()
		{
			m_state->handle(this);
		}

		void SetState(State *_state)
		{
			m_state = _state;
		}


	private:
		State *m_state = NULL;
	};

	class ConcrectState1;

	class ConcrectState3 : public State {
	public:
		virtual void handle(Context* _context) {
			std::cout << "Hello World! 黄灯\n";
			//_context->SetState(new ConcrectState1());
		}
	};

	class ConcrectState2 : public State {
	public:
		virtual void handle(Context* _context) {
			std::cout << "Hello World! 绿灯\n";
			//_context->SetState(new ConcrectState3());
		}
	};

	class ConcrectState1 : public State {
	public:
		virtual void handle(Context* _context) {
			std::cout << "Hello World! 红灯\n";
			//_context->SetState(new ConcrectState2());
		}
	};

	void StatePatternDemo() {
		Context c(new ConcrectState1());
		c.handle();
		c.SetState(new ConcrectState2());
		c.handle();
		c.SetState(new ConcrectState3());
		c.handle();
		c.SetState(new ConcrectState1());
		c.handle();
	}

}


namespace LH2 {
	enum E991LoginState {
		E991_login_1 = 0,  // 未登录
		E991_login_2 = 10,  // 登录失败
		E991_login_3 = 20,  // 登录中
		E991_login_4 = 30   // 登录成功

	};

	class HLoginHandle {
	public:
		void Handle(E991LoginState _state) {
			if (_state == E991_login_1)
			{
				std::cout << "未登录" << "\n";
			}
			else if (_state == E991_login_2) {
				std::cout << "登录失败" << "\n";
			}
			else if (_state == E991_login_3) {
				std::cout << "登录中" << "\n";
			}
			else if (_state == E991_login_4) {
				std::cout << "登录成功" << "\n";
			}
		}
	};

	using HStageChangedFunction = std::function<void(E991LoginState _stage)>;

	class HLoginHandle1 {
	public:
		void Handle(E991LoginState _stage) {
			for (auto& itr : m_listState)
			{
				itr(_stage);
			}
		}

		void AddListen(HStageChangedFunction _fun) {
			m_listState.push_back(_fun);
		}
	private:
		std::vector<HStageChangedFunction> m_listState;
	};

	class HLoginInit1 {
	public:
		HLoginInit1(HLoginHandle1& _h) {
			_h.AddListen([this](E991LoginState _stage) {
				if (_stage == E991_login_1)
				{
					std::cout << "未登录" << "\n";
				} 
			});
		}

		void Handle(E991LoginState _stage) {
			if (_stage == E991_login_1)
			{

			}
		}
	};

	class HLoginFail1 {
	public:
		HLoginFail1(HLoginHandle1& _h) {
			//_h.AddListen(std::bind(&HLoginFail1::Handle, this, std::placeholders::_1));
			_h.AddListen(std::bind(&HLoginFail1::Handle, this, std::placeholders::_1));
		}

		void Handle(E991LoginState _stage) {
			if (_stage == E991_login_2)
			{
				std::cout << "登录失败" << "\n";
			}
		}
	};

	void StatePatternDemo1() {
		HLoginHandle1 h;
		HLoginInit1 *l1 = new HLoginInit1(h);
		HLoginFail1 *l2 = new HLoginFail1(h);

		h.Handle(E991_login_1);
		h.Handle(E991_login_2);
		h.Handle(E991_login_3);
	}


	class HLoginState {
	public:
		virtual void handle() = 0;
	protected:
		//E991LoginState m_state;
	};

	class HLoginInit : public HLoginState {
	public:
		virtual void handle() override {
			std::cout << "未登录" << "\n";
		}

	};
	class HLoginFail : public HLoginState {
	public:
		virtual void handle() override {
			std::cout << "登录失败" << "\n";
		}
	};
	class HLoginIng : public HLoginState {
	public:
		virtual void handle() override {
			std::cout << "登录中" << "\n";
		}
	};
	class HLoginSuc: public HLoginState {
	public:
		virtual void handle() override {
			std::cout << "登录成功" << "\n";
		}
	};



	class HLoginMgr {
	public:
		HLoginMgr() {
			m_loginState = new HLoginInit();
		}
		void SetState(HLoginState* _state) {
			m_loginState = _state;
		}
		void Handle() {
			m_loginState->handle();
		}
	private:
		HLoginState* m_loginState;
	};


	void StatePatternDemo() {
		HLoginMgr c;
		c.Handle();
		c.SetState(new HLoginIng());
		c.Handle();

		c.SetState(new HLoginFail());
		c.Handle();

		c.SetState(new HLoginIng());
		c.Handle();

		c.SetState(new HLoginSuc());
		c.Handle();
	}
}

int main()
{
	LH2::StatePatternDemo1();

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
