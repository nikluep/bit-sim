#pragma once
#include <memory>
#include <chrono>

#include "common.h"
#include "BasicContainer.h"

namespace ui {

	class Scene
		: public BasicContainer
	{
	public:
		Scene(const sf::Vector2f& windowSize);
		virtual ~Scene() = default;

		virtual void onFrameStart(const std::chrono::nanoseconds& lastFrametime) {};
		virtual void onFrameEnd(const std::chrono::nanoseconds& lastFrametime) {};

		void switchTo(std::unique_ptr<Scene> scene) { m_next = std::move(scene); };
		bool isSwitchTriggered() const { return !!m_next; };
		std::unique_ptr<Scene> getNextScene() { return std::move(m_next); };

	private:
		std::unique_ptr<Scene> m_next;
	};
}

