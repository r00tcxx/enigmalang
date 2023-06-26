#pragma once
#include <tuple>
#include <string>
#include <optional>
#include <string>

namespace tk {
	class error {
	public:
		error() {}
		error(
			const std::uint32_t code,
			const std::string& message) : code_(code), message_(message) {}
		error(
			const error& l) noexcept {
			operator=(l);
		}

		error(
			error&& l) noexcept {
			operator=(std::move(l));
		}

		error& operator=(
			const error& l) {
			code_ = l.code_, message_ = l.message_;
			return *this;
		}

		error& operator=(
			error&& l)  noexcept {
			code_ = l.code_, message_ = std::move(l.message_);
			return *this;
		}

		operator bool() {
			return !code_;
		}

		std::uint32_t code() const {
			return code_;
		}

		const std::string& string() const {
			return message_;
		}
	private:
		std::uint32_t code_{ 0 };
		std::string message_;
	};

	template<typename Err = tk::error, typename ...Ts>
	struct result {
		using value_type = std::tuple<Err, Ts...>;
		//result(
		//	Ts&&... vals) : values_(std::forward<Ts>(vals)...){}

		std::tuple<Err, Ts...> values_;
	};

	template<typename ...Ts>
	using result_t = result<error, Ts...>;

	//template<typename ...Ts>
	//auto make_fail(
	//	const std::uint32_t code = 0,
	//	const std::string& message = "") {
	//	return result_t<Ts...>(error(), ...);
	//}
}

namespace std {
	template <typename Err, typename ...Ts> 
	struct tuple_size<tk::result<Err, Ts...>> :
		std::integral_constant<std::size_t, sizeof...(Ts) + 1> {};

	template<size_t I, typename Err, typename... Ts>
	struct tuple_element<I, tk::result<Err, Ts...>> 
		: std::tuple_element<I, typename tk::result<Err, Ts...>::value_type> {
	};

	template<std::size_t I, typename Err, typename... Ts>
	decltype(auto) get(const tk::result<Err, Ts...>& res) {
		return std::get<I>(res.values_);
	}

	template<std::size_t I, typename Err, typename... Ts>
	decltype(auto) get(tk::result<Err, Ts...>& res) {
		return std::get<I>(res.values_);
	}

	template<std::size_t I, typename Err, typename... Ts>
	decltype(auto) get(tk::result<Err, Ts...>&& res) {
		return std::move(std::get<I>(res.values_));
	}
}
