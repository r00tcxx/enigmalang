#pragma once
#include <mutex>
#include <memory>

namespace tk {

#define NO_COPYABLE(CLS) \
	CLS(const CLS&) = delete; \
	CLS& operator=(const CLS&) = delete; \
	
#define NO_MOVEABLE(CLS) \
	CLS(CLS&&) = delete; \
	CLS& operator=(CLS&&) = delete; \

#define NO_COPYABLE_MOVEABLE(CLS) \
	NO_COPYABLE(CLS)	\
	NO_MOVEABLE(CLS)	\

	template<class T>
	class Singleton {
	public:
		Singleton() = default;
		virtual ~Singleton() {}

		template<typename ...Args>
		static T& Instance(Args&& ...args) {
			static std::once_flag once_flag;
			std::call_once(
				once_flag, 
				[&args...] {
					instance_.reset(new T(std::forward<Args>(args)...));
				});
			return *instance_;
		}

		NO_COPYABLE_MOVEABLE(Singleton)
	private:
		static std::unique_ptr<T> instance_;
	};

	template <typename T>
	std::unique_ptr<T> Singleton<T>::instance_;
}

