#include <thread>
#include "plog/Log.h"
#include "plog/Appenders/ConsoleAppender.h"

static void* my_background_function(void* arg) {
	const char* label=(const char*)arg;

	LOGI << "Hello from thread " << label;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	LOGI << "Ping from thread " << label;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	LOGI << "Goodbye from thread " << label;

	return nullptr;
}


int main( int argc, char ** argv ) {
	std::thread* my_thread=nullptr;

	static plog::ConsoleAppender<plog::TxtFormatter> console;
	plog::init(plog::debug, &console);

	LOGI << "Hello from main thread";

	LOGI << "Main thread; pre-spawn";
	my_thread = new std::thread(my_background_function, (void*)"thread one");
	LOGI << "Main thread; post-spawn";

	LOGI << "Main thread pre-join";
	my_thread->join();
	LOGI << "Main thread post-join";

	LOGI << "Main thread pre-delete";
	delete my_thread;
	LOGI << "Main thread post-delete";

	LOGI << "Goodbye from main thread";
}