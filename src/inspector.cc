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

#include "inspector.h"
#include "common.h"

using namespace std;
using namespace Glib;

namespace FInspector {

bool Inspector::Fileinfo::operator < (const Fileinfo& rhs) {
    return (filename.lowercase() < rhs.filename.lowercase());
}

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


void showErrorCode(const char * filepath) 
{
    
    cout << "Failed to open '" << filepath << "' !! \n" << endl; 
        switch (errno) {
            case EACCES:
                cout << "Permission denied." << endl;
                break;
            case EBADF:
                cout << "fd is not a valid file descriptor opened for reading." << endl;
                break;
            case EMFILE: 
                cout << "The per-process limit on the number of open file descriptors"
                        "has been reached." << endl;
                break;
            case ENFILE: 
                cout << "The system-wide limit on the total number of open files has"
              "been reached." << endl;
                break;
            case ENOENT: 
                cout << "Directory does not exist, or name is an empty string." << endl;
                break;
            case ENOMEM:
                cout << "Insufficient memory to complete the operation." << endl;
                break;
            case ENOTDIR:
                cout << "Not a directory!" << endl;
                break;
            default:
                cout << "Error (" << errno << ") !" << endl;
        }
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
vector< Inspector::Fileinfo >
Inspector::getDirectoryContent(const ustring& p, bool includeHidden) {
    vector< Fileinfo > content;
    
    ustring tp = p; // We'll be trimming this
    tp = (Fstr::rtrim(tp, FS_DIRECTORY_SEPARATOR) + FS_DIRECTORY_SEPARATOR); // Store the trimmed version
    // First let's attempt to open the directory
    DIR * dp = opendir(tp.c_str());

    if (dp) {
        dirent * entry;
        struct stat filestat;
        while ((entry = readdir(dp))) {
            if (! includeHidden && '.' == entry->d_name[0]) {
                // This is a hidden file, skip
                continue;
            }
            ustring fullpath = tp.c_str();
            fullpath += entry->d_name;
            // Get the statistics of file
            if (stat(fullpath.c_str(), &filestat) != -1) {
                Inspector::Fileinfo info;
                info.filename = entry->d_name;
                info.lastModifed = filestat.st_mtime;
                info.path = fullpath;
                info.size = filestat.st_size;

                // Get the file type
                switch (filestat.st_mode & S_IFMT) {
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
            cout << "We really got in!" << fullpath << endl;
            } else {
                showErrorCode(fullpath.c_str());
            }
        }
        // We are done close it
        closedir(dp);

        // Sort the items
        std::sort(content.begin(), content.end());
    } else {
        showErrorCode(tp.c_str());
        // Failed to open the directory
        // Throw exception?
    }

    return content;
}
}
