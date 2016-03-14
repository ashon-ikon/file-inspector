/**
 * Written by Yinka
 *
 * (c) 2016
 *
 */
#include <gtkmm/application.h>
#include <glibmm/ustring.h>
#include "inspector.h"
#include <vector>
#include <iostream>

using namespace FInspector;
using namespace std;

int main(int argc, char *argv[]) {

    DirectoryCollection list = getDirectoryContent("./");

    std::cout << "Found :" << list.size() << " items " << std::endl;
    
    

    int counter = 0;
    for (vector<Inspector::Fileinfo>::const_iterator it = list.begin();
            it != list.end(); ++it) {
        ++counter;
        cout << (*it).path.c_str() << ": " << Inspector::getType((*it).type) << endl;
    }

    return 0;
}
