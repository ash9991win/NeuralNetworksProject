#include "pch.h"
#include "InputManager.h"
using namespace std;
 std::map<sf::Keyboard::Key, bool> InputManager::mKeyPressedStatus;
map<sf::Keyboard::Key, InputManager::KeyPressed> InputManager::KeyPressedTable;
 map<sf::Keyboard::Key, InputManager::KeyPressed> InputManager::KeyReleasedTable;
 InputManager::MouseReleasedDelegate InputManager::MousePressedEvents;
 InputManager::MouseReleasedDelegate InputManager::MouseReleasedEvents;
 bool InputManager::IsKeyPressed(sf::Keyboard::Key key)
 { 
	 if (mKeyPressedStatus.find(key) == mKeyPressedStatus.end())
		 return false;
	 bool result = mKeyPressedStatus[key];
	 if (result)
		 mKeyPressedStatus[key] = false;
	 return result;
 }
 bool InputManager::IsKeyReleased(sf::Keyboard::Key)
 {
	 return false;
 }
 void InputManager::HandleKeyPress(sf::Keyboard::Key key,float deltaTime)
{
	if (KeyPressedTable.find(key) != KeyPressedTable.end())
	{
		KeyPressedTable[key].Invoke(std::forward<float>(deltaTime));
	}
	mKeyPressedStatus[key] = true;
}
	

void InputManager::HandleKeyRelease(sf::Keyboard::Key key,float deltaTime)
{
	if (KeyReleasedTable.find(key) != KeyReleasedTable.end())
	{
		KeyReleasedTable[key].Invoke(std::forward<float>(deltaTime));
	}
	mKeyPressedStatus[key] = false;
}

void InputManager::HandleMouseEvents(sf::Event::EventType type)
{
	if (type == sf::Event::EventType::MouseButtonPressed)
	{
		MousePressedEvents.Invoke(sf::Mouse::getPosition());
	}
	else if (type == sf::Event::EventType::MouseButtonReleased)
	{
		MouseReleasedEvents.Invoke(sf::Mouse::getPosition());

	}
}
