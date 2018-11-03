// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

int main() {
    cout << "Please select the action that you want to perform." << endl;
    string option = getLine("Please enter the filename.");

    bool wrapOption = getYesOrNo("do you want to wrap around the cell world? Yes | No ");

    cout << "a | animate - t | tick - q | quit" << endl;
    char action = getchar();
    return 0;
}
