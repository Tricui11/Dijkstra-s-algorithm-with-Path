// These two lines prevents the file from being included multiple
// times in the same source file
#ifndef DIRECTIONS_H_
#define DIRECTIONS_H_

enum Directions
{
    None,
    Down,
    Left,
    Up,
    Right,
    Northeast,
    Northwest,
    Southeast,
    Southwest
};

// Declare (which is different from defining) a global variable, to be
// visible by all who include this file.
// The actual definition of the variable is in the gamestate.cpp file.
extern Directions State;

#endif // DIRECTIONS_H_
