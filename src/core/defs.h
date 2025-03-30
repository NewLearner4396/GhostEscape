#ifndef DEFS_H
#define DEFS_H

#define DEBUG_MODE

enum class ObjectType {
    NONE = 0,
    OBJECT_SCREEN,
    OBJECT_WORLD,
    ENEMY,
};

enum class Anchor{
    NONE = 0,
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};

#endif // DEFS_H
