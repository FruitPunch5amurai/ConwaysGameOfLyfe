#include "InputManager.h"
#include <BasicLogger.h>
#include <string>
namespace GameEngine
{
	InputManager::InputManager() : _mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::KeyPress(unsigned int keyId)
	{
		_keyMap[keyId] = true;
	}

	void InputManager::KeyRelease(unsigned int keyId)
	{
		_keyMap[keyId] = false;
	}

	void InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyId)
	{
		auto it = _keyMap.find(keyId);
		if (it != _keyMap.end())
		{
			return it->second;
		}
		return false;
	}

}