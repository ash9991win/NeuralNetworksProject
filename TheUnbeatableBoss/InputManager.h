#pragma once
#include"pch.h"
#include<map>
class Actor;
/*!
\class InputManager
\brief The handler of the inputs
*/
class InputManager
{
	
private:
	typedef delegate<void, float> KeyPressed;
	typedef delegate<void, sf::Vector2i> MousePressedDelegate;
	typedef delegate<void, sf::Vector2i> MouseReleasedDelegate;
	static std::map<sf::Keyboard::Key, bool> mKeyPressedStatus;
public:
	/*!
	\var KeyPressedTable
	\brief The map of all the keys and their corresponding delegates
	*/
	static std::map<sf::Keyboard::Key, KeyPressed> KeyPressedTable;
	/*!
	\var KeyReleasedTable
	\brief The map of all the keys and their corresponding delegates
	*/
	static std::map<sf::Keyboard::Key, KeyPressed> KeyReleasedTable;
	/*!
	\fn IsKeyPressed
	\brief Returns true if the given key was pressed at that frame
	\param The key to check for
	\return Returns true if the key was pressed
	*/
	static bool IsKeyPressed(sf::Keyboard::Key);
	static bool IsKeyReleased(sf::Keyboard::Key);
	/*!
	\var MousePressedEvents
	\brief The delegate for mouse press
	*/
	static MousePressedDelegate MousePressedEvents;
	/*!
	\var MouseReleasedEvents
	\brief The delegate for mouse release
	*/
	static MouseReleasedDelegate MouseReleasedEvents;
	/*!
	\fn HandleKeyPress
	\brief handled by the gameloop
	\param The key to check for and deltatime
	*/
	static void HandleKeyPress(sf::Keyboard::Key,float deltaTime);
	/*!
	\fn HandleKeyRelease
	\brief handled by the gameloop
	\param The key to check for and deltatim
	*/
	static void HandleKeyRelease(sf::Keyboard::Key,float deltaTime);
	/*!
	\fn HandleMouseEvents
	\brief handled by the gameloop
	\param The type of the event 
	*/
	static void HandleMouseEvents(sf::Event::EventType type, const sf::Window& window);
};

