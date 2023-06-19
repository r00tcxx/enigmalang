#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

#include "tk/function.h"
#include "tk/result.h"

bool command_build() {
	return false;
}

bool command_run() {
	return false;
}

bool command_version() {
	return false;
}

struct Command {

};


tk::result_t<std::string, int> foo() {

	return  { tk::error(1, "123") };
}

int main(int argc, char* argv[]) {
	//std::unordered_map<std::string, std::function<bool(const Command&)>> commands {
	//	{ "build",		tk::to_function(command_build) },
	//	{ "run",		tk::to_function(command_run) },
	//	{ "version",	tk::to_function(command_version) }
	//};

	auto [error, ret1, ret2] = foo();
	if (error) {
		error.code();
		error.string();
	}

	return 0;

	//auto[error, cmd] = ParseCommand(argc, argv);
	//if (error)
	//	log::info("enigmalang: {}", error.string());
	//if (auto match_command = cmd.empty() ? commands.end() : commands.find(cmd.name()); match_command != commands.end())
	//	return !match_command->second(cmd);
	//else
	//	print_useage();
	//return 1;
}

