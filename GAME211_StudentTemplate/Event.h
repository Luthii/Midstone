#pragma once

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