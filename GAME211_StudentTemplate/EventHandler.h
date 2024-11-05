#pragma once

//C++ includes
#include <functional>
#include <map>
#include <vector>


//project includes
#include "Event.h"

using functionPair = std::pair<const char*, std::function<void(const Event&)>>;

//this will be a SINGLETON as well
class EventHandler
{
private:
	//simple renaming to not use the long type
	using Listener = std::function<void(const Event&)>;

//Attributes
	static EventHandler* instance;
	EventHandler() {}

	//creates a map where the key is an EventType (that shoudl be unique) and a list of all the functions that should be executed
	//	if the event is dispatched
	std::map<Event::EventType, std::vector<functionPair>> listenerMap;

public:
	//"delete" the methods that allow the class to be copied
	EventHandler(const EventHandler& obj) = delete;
	EventHandler& operator=(EventHandler const&) = delete;
	static EventHandler* GetInstance() {
		if (instance == NULL)
			instance = new EventHandler();

		return instance;
	}

	bool Subscribe(const Event::EventType& eventType, Listener&& listener, const char* functionID);
	bool Unsubscribe(const Event::EventType& eventType, const char* functionID);
	void Broadcast(const Event& event) const;
};

