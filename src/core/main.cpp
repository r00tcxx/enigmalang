#include "logger.h"
#include "version.h"

#include "tk/function.h"
#include <queue>
#include <unordered_map>

struct Command {
	std::string cmd;
	std::queue<std::string> parts;
};

void PrintUsage() {
	Info("usage: el.exe [command] [args]... [options]...\n"
		"commands:\n"
		"\tbuild\t\t:static compilation source file to executable file\n"
		"\trunt\t\t:directly interpret and run source file\n"
		"\tinstall\t\t:install el package\n"
		"\tuninstall\t\t:remove el package\n"
		"\tlistpkg\t\t:show all installed el packages\n"
		"\thelp\t\t:show usage\n"
		"\tversion\t\t:show current el core version\n"
		"options:\n"
		"\t-o\t\t:specify output file path\n"
		"\t-O\t\t:use optimization(remove debug infomation)\n"
	);
}

int CommandBuild(
	const Command& cmd) {
	if (cmd.parts.empty()) {
		Error("missing source file");
		return 1;
	}
	auto source_file = cmd.parts.front();



	return false;
}

int CommandRun(
	const Command& cmd) {
	//todo
	return false;
}

int CommandInstall(
	const Command& cmd) {
	//todo
	return false;
}

int CommandUninstall(
	const Command& cmd) {
	//todo
	return false;
}

int CommandListPKG(
	const Command& cmd) {
	//todo
	return false;
}

bool ParseCommand(
	int argc,
	char* argv[],
	Command& command) {
	if (1 >= argc) return false;
	for (int i = 1; i < argc; ++i) {
		if (1 == i) command.cmd = argv[i];
		else command.parts.push(argv[i]);
	}
	return true;
}

int main(int argc, char* argv[]) {
	static std::unordered_map<std::string, std::function<int(const Command&)>> kCommands {
		{ "build",		tk::to_function(CommandBuild)		},
		{ "run",		tk::to_function(CommandRun)			},
		{ "help",		[](const Command&) { PrintUsage(); return true;  }},
		{ "version",	[](const Command&) { Info("enigmalang {}", EL_CORE_VERSION); return true; }},
		{ "install",	tk::to_function(CommandInstall)		},
		{ "uninstall",	tk::to_function(CommandUninstall)	},
		{ "listpkg",	tk::to_function(CommandListPKG)		},
	};

	Command cmd;
	if (ParseCommand(argc, argv, cmd)) {
		if (auto target_cmd_func = kCommands.find(cmd.cmd);
			target_cmd_func != kCommands.end()) 
			return target_cmd_func->second(cmd);
	}
	if (!cmd.cmd.empty()) {
		Error("invalid command");
		PrintUsage();
	}
	return 1;
}

