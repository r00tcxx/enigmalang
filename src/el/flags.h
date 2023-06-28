#pragma once
#include "tk/singleton.h"
#include <unordered_map>
#include <variant>
#include <algorithm>

namespace flags {
	template<typename T>
	concept FlagType = std::is_same_v<T, std::uint64_t> || std::is_same_v<T, std::int64_t>
		|| std::is_same_v<T, std::string> || std::is_same_v<T, bool> || std::is_same_v<T, double>;

	class FlagBase {
	public:
		static inline std::unordered_map<std::string, FlagBase*> kDefinedCommandsMap;
	public:
		NO_COPYABLE_MOVEABLE(FlagBase);
		FlagBase(
			const char* name,
			const char* desc) : name_(name), desc_(desc)  {
			kDefinedCommandsMap.emplace(name, this);
		}
		~FlagBase() {}
		const char* Name() const { return name_; }
		const char* Desc() const { return desc_; }
		virtual bool Parse(const std::string& cmd) = 0;

	protected:
		const char* name_;
		const char* desc_;
	};


	template<FlagType T>
	class Flag : public FlagBase {
	public:
		Flag(
			const char* name,
			const char* desc,
			const T& default_value) : FlagBase(name, desc), value_(default_value) {
		}
		virtual ~Flag() {}

		bool Parse(
			const std::string& cmd) override {
			if (cmd.empty()) return true;
			try {
				if constexpr (std::is_same_v<std::uint64_t, T>)
					value_ = std::strtoull(cmd.c_str(), nullptr, 10);
				else if constexpr (std::is_same_v<std::int64_t, T>)
					value_ = std::strtoll(cmd.c_str(), nullptr, 10);
				else if constexpr (std::is_same_v<std::string, T>)
					value_ = cmd;
				else if constexpr (std::is_same_v<bool, T>) {
					std::string lowercase;
					std::transform(
						cmd.begin(),
						cmd.end(),
						lowercase.begin(),
						::tolower);
					value_ =  lowercase == "false" ? false : true;
				}
				else value_ = std::strtod(cmd.c_str(), nullptr);
			}
			catch (...) {
				return false;
			}
			return true;
		}

		inline void SetValue(
			const T& value) {
			value_ = value;
		}

		inline T Value() const {
			return value_;
		}

		operator T() const {
			return value_;
		}
	private:
		T value_;
	};

	inline void ParseCommandLine(
		int argc,
		char* argv[]) {
		if (1 == argc) return;
		for (int i = 1; i < argc; ++i) {
			auto fist_not_hyphen = strspn(argv[i], "-");
			std::string cmd(argv[i], fist_not_hyphen, strlen(argv[i]) - fist_not_hyphen);
			std::string cmd_name;
			if (auto has_eql = cmd.find_first_of('='); has_eql != std::string::npos) {
				cmd_name = cmd.substr(0, has_eql);
				cmd = cmd.substr(has_eql);
			}
			else cmd_name = cmd, cmd = "";
			if (auto match_cmd = FlagBase::kDefinedCommandsMap.find(cmd_name); match_cmd != FlagBase::kDefinedCommandsMap.end())
				match_cmd->second->Parse(cmd);
		}
	}
}

#define DECLARE_FLAG(TYPE,NAME,DESC, DEFAULT_VALUE) \
extern flags::Flag<TYPE> kFlag_##NAME(#NAME, DESC, DEFAULT_VALUE);

#define DECLARE_BOOL_FLAG(NAME,DESC, DEFAULT_VALUE) DECLARE_FLAG(bool, NAME, DESC, DEFAULT_VALUE)
#define DECLARE_STRING_FLAG(NAME,DESC, DEFAULT_VALUE) DECLARE_FLAG(std::string, NAME, DESC, DEFAULT_VALUE)
#define DECLARE_INT64_FLAG(NAME,DESC, DEFAULT_VALUE) DECLARE_FLAG(std::int64_t, NAME, DESC, DEFAULT_VALUE)
#define DECLARE_UINT64_FLAG(NAME,DESC, DEFAULT_VALUE) DECLARE_FLAG(std::uint64_t, NAME, DESC, DEFAULT_VALUE)
#define DECLARE_FLOAT64_FLAG(NAME,DESC, DEFAULT_VALUE) DECLARE_FLAG(double, NAME, DESC, DEFAULT_VALUE)

