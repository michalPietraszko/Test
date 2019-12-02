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
		std::string toString() const { std::stringstream ss; ss<<"example str"; return ss.str(); }
		const char* getName() const { return "example char"; }
	};

	class API Layer
	{
	public:
		virtual void onEvent(Event&) {}
	};

	class API Application
	{
	public:
		Application() = default;
		Application(const Application&) = delete;
		Application(Application&&) = default;
		Application& operator=(Application&&) = default;
		Application& operator=(const Application&) = delete;
		~Application() = default;
			   
		template<typename T>
		void pushLayer()
		{
			vec.push_back(std::make_unique<T>());
		}

		void run()
		{	
			bool doneOnce{ false };
			while (true) 
			{
				if (!doneOnce) 
				{
					Event e{};
					(*vec.begin())->onEvent(e);
					doneOnce = true;
				}
			}
		}

		std::vector<std::unique_ptr<Layer>> vec;
	};

    Application* createApplication(); // define in client
}// namespace