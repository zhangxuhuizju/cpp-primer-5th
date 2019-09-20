#include <list>
#include <iostream>
#include <forward_list>
using namespace std;

int main(int argc, char const *argv[])
{
    list<int> li = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    forward_list<int> fli(li.begin(), li.end());

    auto iter = li.begin();
    while (iter != li.end()) {
        if (*iter % 2) {
            iter = li.insert(iter, *iter);
            ++iter;
            ++iter;
        } else {
            iter = li.erase(iter);
        }
    }

    auto front = fli.before_begin();
    auto index = fli.begin();
    while (index != fli.end()){
        if (*index % 2) {
            front = fli.insert_after(front, *index);
            front++;
            index++;
        } else {
            index = fli.erase_after(front);
        }
    }
    for (auto i : li)
        cout << i << ' ';
    cout << endl;
      for (auto i : fli)
        cout << i << ' ';
    cout << endl;
    return 0;
}
