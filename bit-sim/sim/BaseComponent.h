#pragma once
#include <chrono>

namespace sim {
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = 0;

		virtual void update(const std::chrono::nanoseconds& frametime) = 0;
	};
	inline BaseComponent::~BaseComponent() = default;
}