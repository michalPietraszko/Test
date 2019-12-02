#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#ifdef BUILD_DLL
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif

namespace lib
{
	class API Event
	{
	public:
		std::string toString() const { std::stringstream ss; ss<<"example"; return ss.str(); }
		const char* getName() const { return "example"; }
	};

	class API Layer
	{
	public:
		virtual void onEvent(Event&) {}
	};

	class API Application
	{
	public:
		template<typename T>
		void pushLayer()
		{
			vec.emplace_back(new T);
		}

		void run()
		{
			vec.begin()->onEvent();
		}

		std::vector<std::unique_ptr<Layer>> vec;
	};

    Application* createApplication();
}// namespace