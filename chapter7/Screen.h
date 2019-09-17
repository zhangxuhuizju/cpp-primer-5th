#ifndef SCREEN
#define SCREEN

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Window_mgr {
public:
    using ScreenIndex = vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    vector<Screen> screens{Screen(24, 80, ' ')};
};

class Screen{
    friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = string::size_type;
    Screen() = default;

    Screen(pos ht, pos wd, char c):height(ht), width(wd), 
                                   contents(ht*wd, c) {}
    char get() const {return contents[cursor];}  //隐式内联
    inline char get(pos ht, pos wd) const;  //显示内联
    Screen &move(pos r, pos c); //可以在定义的时候加上inline变为内联
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(ostream & os) {do_display(os); return *this;}
    const Screen &display(ostream & os) const{do_display(os); return *this;}

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;

    void do_display(ostream &os) const{
        os << contents;
    }
};

#endif