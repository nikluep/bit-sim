#pragma once
#include <chrono>

namespace sim {
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() {};

		virtual void update(const std::chrono::nanoseconds& frametime) = 0;
	};
}