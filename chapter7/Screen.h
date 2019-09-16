#ifndef SCREEN
#define SCREEN

#include <string>
using std::string;

class Screen{
public:
    using pos = string::size_type;
    Screen() = default;

    Screen(pos ht, pos wd, char c):height(ht), width(wd), 
                                   contents(ht*wd, c) {}
    char get() const {return contents[cursor];}  //隐式内联
    inline char get(pos ht, pos wd) const;  //显示内联
    Screen &move(pos r, pos c); //可以在定义的时候加上inline变为内联

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
};

#endif