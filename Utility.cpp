#include "Utility.h"
USING_NS_CC;
string Utility::ToUTF8(string key) {
	auto string = Dictionary::createWithContentsOfFile("ToUTF8.xml");
	const char *str1 = ((String*)string->objectForKey(key))->getCString();
	return str1;
}

void Utility::onKeyReleased(EventKeyboard::KeyCode keycode, Event * pEvent) {
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Director::getInstance()->popScene();
}
float Utility::getRand(int start, int end)
{
	float i = CCRANDOM_0_1()*(end - start + 0.99) + start;  //产生一个从start到end间的随机数  
	return i;
}