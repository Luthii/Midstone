#pragma once
#include "DataCollection.h"

class Event {
public:
	using EventType = const char*;
	virtual ~Event() {}
	virtual EventType getType() const = 0;

};

// Test event
//class ScreamEvent :public Event {
//public:
//	ScreamEvent() {}
//	~ ScreamEvent() {}
//
//	static constexpr EventType eventType = "ScreamEvent";
//	EventType getType() const { return eventType; }
//};


class QuitEvent : public Event {
public:
	QuitEvent() {}
	~QuitEvent() {}

	static constexpr EventType eventType = "QuitEvent";
	EventType getType() const { return eventType; }
};

class ChangeSceneEvent : public Event {
public:
	ChangeSceneEvent(SCENES sceneChange_) { sceneChange = sceneChange_; }
	~ChangeSceneEvent() {}

	static constexpr EventType eventType = "ChangeScene";
	EventType getType() const { return eventType; }
	SCENES sceneChange;
};