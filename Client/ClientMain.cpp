#include <Main.hpp>

class Example : public lib::Layer
{
public:
	void onEvent(lib::Event& e) override
	{
		e.toString(); // returns std::string, crashes application
		e.getName(); // returns const char*, works fine
	}
};

extern lib::Application* lib::createApplication();
lib::Application* lib::createApplication()
{
	return new Sandbox();
}

class Client : public lib::Application
{
public:
	Client() { pushLayer<Example>(); } // 1
}

int main(int argc, char** argv)
{
	auto app = lib::createApplication(); // return new Client
	app->run();
	delete app;
}