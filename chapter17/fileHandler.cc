#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2)
        cout << "please tell the filename to handle!" << endl;
    fstream inOut(*++argv, fstream::ate | fstream::in | fstream::out);
    if (!inOut) {
        cerr << "Cannot open the file!" << endl;
        return EXIT_FAILURE;
    }
    auto end_mark = inOut.tellg();
    inOut.seekg(0, fstream::beg);
    size_t cnt = 0;
    string line;
    while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) {
        cnt += line.size() + 1;
        auto mark = inOut.tellg();
        inOut.seekp(0, fstream::end);
        inOut << cnt;
        if (mark != end_mark)
            inOut << ' ';
        inOut.seekg(mark);
    }
    inOut.seekp(0, fstream::end);
    inOut << "\n";
    inOut.close();
    return 0;
}
