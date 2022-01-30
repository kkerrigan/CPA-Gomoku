/*
Kristian Kerrigan
App.hpp
This file contains the Singleton App class that invokes the main of the App on creation.
*/


#pragma once
#include <string>
#include <vector>

#if defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "gomokulib-mt-gd.lib")
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "gomokulib-mt-sgd.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "gomokulib-mt.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "gomokulib-mt-s.lib")
#endif

class App {
	using Args = std::vector<std::string>;
	Args _args;
	static App* thisApp;
	friend int main(int argc, char* argv[]);
	static int main(int argc, char* argv[]);
protected:
	App();
	virtual ~App() = default;
	virtual int execute() = 0;
	Args const& QueryArgs() const { return _args; }
};