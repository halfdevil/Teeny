#pragma once

#include "Core/StdHeaders.h"
#include "Core/Observer.h"
#include "Core/Window.h"

struct InputAction
{
  std::string name;
  std::vector<int32_t> keys;
};

struct InputAxis
{
  std::string name;
  std::vector<std::pair<int32_t, float>> keys;
};

enum InputEvent : uint32_t
{
  Pressed = 0,
  Released,
  Max
};

class Input
{
public:

  Input() = default;
  ~Input()
  {
    destroy();
  }

  void create(Window& window);
  void destroy();
  void update();

  void addAction(const InputAction& action);
  void addAxis(const InputAxis& axis);

  void bindAction(const std::string& actionName, InputEvent event, 
    std::function<void(int32_t)> callback);

  void bindAxis(const std::string&axisName, std::function<void(float)> callback);

private:

  void onKeyCallback(int32_t key, bool pressed);

private:

  std::vector<bool> mKeyStates;
  std::unordered_map<std::string, InputAction> mActionMap;
  std::unordered_map<std::string, InputAxis> mAxisMap;
  std::unordered_map<int32_t, std::string> mKeyActionMap;
  std::vector<std::unordered_map<std::string, Observer<int32_t>>> mActionBindings;
  std::unordered_map<std::string, Observer<float>> mAxisBindings;
};