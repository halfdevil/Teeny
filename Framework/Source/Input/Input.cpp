#include "Input/Input.h"
#include "Core/Core.h"

void Input::create(Window& window)
{
	window.onKeyCallback.subscribe([this](int32_t key, bool pressed) {
		onKeyCallback(key, pressed);
		});

	mKeyStates.resize(GLFW_KEY_LAST + 1);
	mActionBindings.resize(InputEvent::Max);
}

void Input::destroy()
{
}

void Input::update()
{
	for (auto& inputAxis : mAxisMap)
	{
		auto bindingIt = mAxisBindings.find(inputAxis.first);
		if (bindingIt == mAxisBindings.end())
		{
			continue;
		}

		for (auto& key : inputAxis.second.keys)
		{
			bindingIt->second.notify(mKeyStates[key.first] ? 1.0f : 0.0f);
		}
	}
}

void Input::addAction(const InputAction& action)
{
	mActionMap.insert({ action.name, action });

	for (int32_t key : action.keys)
	{
		mKeyActionMap.insert({ key, action.name });
	}
}

void Input::addAxis(const InputAxis& axis)
{
	mAxisMap.insert({ axis.name, axis });
}

void Input::bindAction(const std::string& actionName, InputEvent event, std::function<void(int32_t)> callback)
{
	auto& bindings = mActionBindings[event];
	bindings[actionName].subscribe(callback);
}

void Input::bindAxis(const std::string& axisName, std::function<void(float)> callback)
{
	mAxisBindings[axisName].subscribe(callback);
}

void Input::onKeyCallback(int32_t key, bool pressed)
{
	mKeyStates[key] = pressed;

	auto keyIt = mKeyActionMap.find(key);
	if (keyIt == mKeyActionMap.end())
	{
		return;
	}

	auto& bindings = pressed ? mActionBindings[InputEvent::Pressed] :
		mActionBindings[InputEvent::Released];

	auto bindingIt = bindings.find(keyIt->second);
	if (bindingIt == bindings.end())
	{
		return;
	}

	bindingIt->second.notify(key);
}