#pragma once
#include "cocos2d.h"
#include "SystemHeader.h"
using namespace cocos2d;
using namespace std;
class Utility {
public:
	template<typename  T> static string to_string(T &t ) {
		ostringstream os;
		os << t;
		return os.str();
	}
	static string ToUTF8(std::string key);
	void  onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent);
	static float getRand(int start, int end);
};
