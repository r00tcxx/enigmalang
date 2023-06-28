#include "logger.h"
#include "flags.h"
#include "version.h"
#include "core/parse.h"

DECLARE_BOOL_FLAG(build, "static compilation source file to executable file", false);
DECLARE_BOOL_FLAG(run, "directly interpret and run source file", false);
DECLARE_BOOL_FLAG(help, "show usage", false);
DECLARE_BOOL_FLAG(version, "show version", false);
DECLARE_STRING_FLAG(i, "specify input", "");
DECLARE_STRING_FLAG(o, "specify output", "");
DECLARE_BOOL_FLAG(O, "optimize(remove debug infomation)", false);

void PrintUsage() {
	using namespace logger;
	Info("usage: el.exe [command] [args]... [options]...");
	Info("commands:");
	Info("\t{:<12}:static compilation source file to executable file", "build");
	Info("\t{:<12}:directly interpret and run source file", "run");
	Info("\t{:<12}:show usage", "help");
	Info("\t{:<12}:show version", "version");
}

bool Build() {



	return true;
}

bool Run() {
	return true;
}

int main(int argc, char* argv[]) {
	flags::ParseCommandLine(argc, argv);

	if (kFlag_build) return !Build();
	else if (kFlag_run) return !Run();
	else if (kFlag_help) {
		PrintUsage();
		return 0;
	}
	else if (kFlag_version) {
		logger::Info("enigmalang {}", EL_CORE_VERSION);
		return 0;
	}
	PrintUsage();
	return 1;
}

