/* 
 * File:   Inspector.cc
 * Author: yinka
 * 
 * Created on 10 March 2016, 7:33 AM
 */

#include "inspector.h"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

namespace FInspector {

    Inspector::Inspector() {
        // We need to set the local
        std::locale::global(std::locale(""));
    }

    Inspector::Inspector(const Inspector& orig) {

    }

    Inspector::~Inspector() {

    }

    bool Inspector::isRegularFile(Fileinfo& fi) {
        return fi.type == RegularFile;

    }

    vector<Inspector::Fileinfo> getDirectoryContent(const Glib::ustring& p) {
        vector<Inspector::Fileinfo> content;

        // First let's attempt to open the directory
        DIR * dp = opendir(p.c_str());

        if (dp) {
            dirent * entry;
            struct stat st;
            while ((entry = readdir(dp))) {
                std::cout << entry->d_name << "... " << std::endl;
                // Get the stat of file
                if (stat(entry->d_name, &st) != -1) {
                    Inspector::Fileinfo info;
                    info.filename = entry->d_name;
                    info.lastModifed = st.st_mtime;
                    info.path = entry->d_name;
                    info.size = st.st_size;

                    // Get the file type
                    switch (st.st_mode) {
                        case S_IFDIR: info.type = RegularFile;
                            break;
                        case S_IFLNK: info.type = SymLink;
                            break;
                        case S_IFREG: info.type = RegularFile;
                            break;
                        default:      info.type = Other;
                            break;
                    }

                    // Add it
                    content.push_back(info);
                }
            }
            // We are done close it
            closedir(dp);
        } else {
            // Failed to open the directory
            // Throw exception?
        }

        return content;
    }
}
