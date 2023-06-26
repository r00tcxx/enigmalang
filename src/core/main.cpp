
#include "logger.h"

void PrintUsage() {



}

int main(int argc, char* argv[]) {

	auto command = parse_command(argc, argv);
	if (!command) {
		PrintUsage();
		return -1;
	}
	auto handled = handle_command(command);
	return 0;
}

