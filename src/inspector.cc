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
#include <algorithm>

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

    bool Inspector::isRegularFile(Fileinfo& fi) {
        return fi.type == RegularFile;

    }
    
    ustring Inspector::getType(FileType ft) {
        ustring type;
        
        switch (ft) {
            case RegularFile:
                type = "Regular file";
                break;
            case Directory:
                type = "Directory";
                break;
            case SymLink:
                type = "Sym-link";
                break;
            case Other:
                type = "Other type of file";
                break;
        }
        
        return type;
    }

    /**
     * 
     * @param p
     * @param includeHidden
     * @return 
     */
    vector<Inspector::Fileinfo> getDirectoryContent(const ustring& p, bool includeHidden) {
        vector<Inspector::Fileinfo> content;

        // First let's attempt to open the directory
        DIR * dp = opendir(p.c_str());

        if (dp) {
            dirent * entry;
            struct stat st;
            while ((entry = readdir(dp))) {
                if (! includeHidden && '.' == entry->d_name[0]) {
                // This is a hidden file, skip
                    continue;
                }
                ustring fullpath = p.c_str();
                fullpath += entry->d_name;
                // Get the stat of file
                if (stat(fullpath.c_str(), &st) != -1) {
                    Inspector::Fileinfo info;
                    info.filename = entry->d_name;
                    info.lastModifed = st.st_mtime;
                    info.path = fullpath;
                    info.size = st.st_size;

                    // Get the file type
                    switch (st.st_mode & S_IFMT) {
                        case S_IFDIR: info.type = Directory;
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
            
            // Sort the items
            std::sort(content.begin(), content.end());
        } else {
            // Failed to open the directory
            // Throw exception?
        }

        return content;
    }
}
