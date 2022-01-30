/*
Kristian Kerrigan
App.cpp
This file contians all of the implementation code for the App class.
*/


#include <cassert>
#include <iostream>
#include <App.hpp>

App* App::thisApp = nullptr;

App::App() {
	assert(!thisApp && "Error: Already initialized!");
	thisApp = this;
}

int App::main(int argc, char*argv[]) {
	for (int i = 1; i < argc; ++i)
		thisApp->_args.push_back(argv[i]);
	return thisApp->execute();
}

int main(int argc, char*argv[]) try {
	return App::main(argc, argv);
}
catch (char const* msg) {
	std::cerr << "Caught string: " << msg << std::endl;
	return EXIT_FAILURE;
}
catch (std::exception const& e) {
	std::cerr << "Caught std::exception: " << e.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Error: an unknown exception has been caught.\n";
	return EXIT_FAILURE;
}