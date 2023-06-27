#pragma once
#include <functional>
#include <type_traits>
#include <utility>

namespace tk {
	template<typename F> 
	constexpr auto to_function(F&& f) {
		return std::function{ std::forward<F>(f) };
	}

	template<typename T, typename R, typename ...Args>
	decltype(auto) to_function(R(T::* mem_func)(Args...), T* instance) {
		return std::function([=](Args... args) {
			return (instance->*mem_func)(std::forward<Args>(args)...);
		});
	}
}