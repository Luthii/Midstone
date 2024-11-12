#include <iostream>

#include "EventHandler.h"

bool EventHandler::Subscribe(const Event::EventType& eventType, Listener&& listener_, const char* functionID)
{
	if (listenerMap.find(eventType) == listenerMap.end()) {
		if (listenerMap.insert({ eventType, std::vector<functionPair>() }).second == false) {
			std::cout << "Unable to subscribe event. Event type: " << eventType << ", function ID: " << functionID <<  "\n";
			return false;
		}
	}

	listenerMap[eventType].push_back(functionPair{ functionID, listener_ });

	return true;
}

bool EventHandler::Unsubscribe(const Event::EventType& eventType, const char* functionID)
{
	if (listenerMap.find(eventType) == listenerMap.end()) {
		std::cout << "There is no event of this type registered. Event type: " << eventType << ".\n";
		return false;
	}


	auto&& listenersList = listenerMap.at(eventType);

	for (std::size_t position = 0; position < listenersList.size(); position++) {
		auto&& listenerFunction = std::next(listenersList.begin(), position);
		if (static_cast<functionPair>(*listenerFunction).first == functionID) {
			listenersList.erase(listenerFunction);
		}
	}

	return true;
}

void EventHandler::Broadcast(const Event& event) const
{
	Event::EventType eventType = event.getType();

	//there is no function listening to the event
	if (listenerMap.find(eventType) == listenerMap.end()) {
		return;
	}

	auto&& listenersList = listenerMap.at(eventType);

	for (auto&& listenerFunction : listenersList) {
		static_cast<functionPair>(listenerFunction).second(event);
	}
}


