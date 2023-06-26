#pragma once
#include <functional>
#include <type_traits>
#include <utility>

namespace tk {
	template<typename F, typename ...Args>
	decltype(auto) to_function(F&& f) {
		using return_type =  std::invoke_result_t<F, Args...>;
		using function_type = std::function<return_type(Args...)>;
		return function_type(std::forward<F>(f));
	}

	template<typename T, typename R, typename ...Args>
	decltype(auto) to_function(R(T::* mem_func)(Args...), T* instance) {
		return std::function([=](Args... args) {
			return (instance->*mem_func)(std::forward<Args>(args)...);
			});
	}
}