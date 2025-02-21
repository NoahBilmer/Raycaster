#pragma once
#include <memory>
#include <type_traits>
#include "Input.h"
#include "raylib.h"
#include <array>

/*
The screen array (and it's related methods) are static because all subclasses that inherit 
from Screen need to have access to every screen in the program so we may transition to a new screen regardless
of which screen we are on. 
*/
class Screen {
public:
    // Rendering related stuff
    RenderTexture2D mainLayer;
    unsigned char mainLayerTransparency;
    RenderTexture2D secondaryLayer;
    unsigned char secondaryLayerTransparency;
    
    static const int screenCount = 3;
    static const int screenWidth = 1200;
    static const int screenHeight = 1000;
    static float scale;
    virtual std::shared_ptr<Screen> update(Input& input) = 0;
    Screen();
    virtual ~Screen() {}
    static void setupScreenArray(); // mandatory in order to use the class
    bool isUsingSecondaryLayer();

    template <class T>
    static std::shared_ptr<Screen> getInstanceOf() {
        std::shared_ptr<Screen> ret;
        for (int i = 0; i < screenCount; i++) {
            ret = std::dynamic_pointer_cast<T>(screenArr[i]);
            // Attempt to dynamic cast the provided class with each element of the screen arr. 
            if (ret != nullptr) {
                return ret;
            }
        }
        return nullptr;
    }

protected:
    bool useSecondaryLayer = false;
    void clearScreen();
    template <class T>
    static void addToArr(std::shared_ptr<T> screen) {
        for (int i = 0; i < screenCount; i++) {
            if (screenArr[i] == nullptr) {
                screenArr[i] = std::dynamic_pointer_cast<T>(screen);
                break;
            }
        }
    }
    int index = 0;
    static std::array<std::shared_ptr<Screen>,screenCount> screenArr; // Array containing the instances of every screen.
};