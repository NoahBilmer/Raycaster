#pragma once
#include <memory>

/*
The screen array (and it's related methods) are static because all subclasses that inherit 
from Screen need to have access to every screen in the program so we may transition to a new screen regardless
of which screen we are on. 
*/
class Screen {
public:
    static const int screenCount = 3;
    virtual int update() = 0;
    void setIndex(int i);
    int getIndex();
    virtual ~Screen() {}
    static void setupScreenArray(); // mandatory in order to use the class
    static std::shared_ptr<Screen> getScreen(int i);  

private:
    static void addToArr(std::shared_ptr<Screen> screen);
    int index = 0;

protected:
    static std::shared_ptr<Screen> screenArr[screenCount]; // Array containing the instances of every screen.
};