/* 
 * File:   Inspector.cc
 * Author: yinka
 * 
 * Created on 10 March 2016, 7:33 AM
 */

#include <algorithm>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>

#include "Inspector.h"
#include "common.h"

using namespace std;
using namespace Glib;

namespace FInspector {

Inspector::Inspector() {
    // We need to set the local
    std::locale::global(std::locale(""));
}

Inspector::Inspector(const Inspector& orig) {

}

Inspector::~Inspector() {

}

}
