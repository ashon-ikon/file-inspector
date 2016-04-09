/**
 * Written by Yinka
 *
 * (c) 2016
 *
 */
#include <gtkmm/application.h>
#include <glibmm/ustring.h>
#include <vector>
#include <iostream>
#include "common.h"

using namespace FInspector;
using namespace std;

int main(int argc, char *argv[]) {

    const Glib::ustring path = "/home/yinka/Downloads";
    DirectoryCollection list = Inspector::getDirectoryContent(path);

    std::cout << "Found :" << list.size() << " items " << std::endl;



    int counter = 0;
    for (vector<Inspector::Fileinfo>::const_iterator it = list.begin();
            it != list.end(); ++it) {
        ++counter;
        cout << (*it).path.c_str() << ": " << Inspector::getType((*it).type) << endl;
    }

    return 0;
}
