#include <Main.hpp>

class Example : public lib::Layer
{
public:
	void onEvent(lib::Event& e) override
	{
		std::cout << "On Event" << std::endl;

		std::string s = e.toString(); // crashes application upon exiting the scope
		std::cout << s << std::endl; 

		//std::cout << e.toString() << std::endl; // crashes after this line

		//e.getName(); // returns const char*, works fine
		
		std::cout << "I did run ok" << std::endl;
	}
};

extern lib::Application* lib::createApplication();

class Client : public lib::Application
{
public:
	Client() { pushLayer<Example>(); }
};

lib::Application* lib::createApplication()
{
	return new Client();
}

int main(int argc, char** argv)
{
	auto app = lib::createApplication();
	app->run();
	delete app;
}