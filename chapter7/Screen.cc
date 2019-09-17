#include "Screen.h"


inline                    //指定内联
Screen &Screen::move(pos r, pos c){
    pos row = r * width;  //计算行的位置
    cursor = row + c;     //在行内将光标移动到指定的列
    return *this;         //以左值的形式返回对象
}

char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}

inline Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch) {
    contents[r *width + col] = ch;
    return *this;
}

void Window_mgr::clear(ScreenIndex i) {
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}

int main(int argc, char const *argv[])
{
    Screen myScreen(5, 5, 'x');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";
    return 0;
}

