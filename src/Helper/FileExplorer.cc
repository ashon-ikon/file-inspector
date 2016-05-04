/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileExplorer.cc
 * Author: Yinka
 * 
 * Created on 9 April 2016, 3:51 PM
 */

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>

#include "FileExplorer.h"
#include "Fstr.h"

using namespace std;
using namespace Glib;

namespace FInspector {

bool FileExplorer::Fileinfo::operator < (const Fileinfo& rhs) {
    return (filename.lowercase() < rhs.filename.lowercase());
}

FileExplorer::FileExplorer() {
    // We need to set the local
    std::locale::global(std::locale(""));
}

FileExplorer::FileExplorer(const FileExplorer& orig) {

}

FileExplorer::~FileExplorer() {

}

/**
 * Makes Directory
 * @param f
 * @return 
 */
bool FileExplorer::makeDirectory(const Glib::ustring& f) {
    return true;
}

/**
 * Removes Directory
 * @param f
 * @return 
 */
bool FileExplorer::removeDirectory(const Glib::ustring& f) {
    return true;
}


bool FileExplorer::isRegularFile(Fileinfo& fi) {
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

ustring FileExplorer::getType(const FileType& ft) {
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

bool FileExplorer::isDirectory(const char* p) {
    bool is = false;
    struct stat st;
    if (stat(p, &st) != -1) {
        is = S_ISDIR(st.st_mode);
    };
    
    return is;
}

/**
 * Gets the content of a path
 * @param p
 * @param includeHidden
 * @return 
 */
vector< FileExplorer::Fileinfo >
FileExplorer::getDirectoryContent(const ustring& p, bool includeHidden) {
    vector< Fileinfo > content;
    
    ustring tp = p; // We'll be trimming this
    tp = (Fstr::rtrim(tp, FS_DIRECTORY_SEPARATOR) + FS_DIRECTORY_SEPARATOR); // Store the trimmed version
    const char *ctp = tp.c_str();
    if (isDirectory(ctp)) {
        // First let's attempt to open the directory
        DIR * dp = opendir(ctp);

        if (dp) {
            dirent * entry;
            // Check that it is 
            while ((entry = readdir(dp))) {
                if (! includeHidden && '.' == entry->d_name[0]) {
                    // This is a hidden file, skip
                    continue;
                }
                Fileinfo info;
                if (getFileInfo(tp, entry, info)) {
                    // Add it
                    content.push_back(info);
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
    }

    return content;
}

bool FileExplorer::getFileInfo(const ustring& p, dirent * entry, FileExplorer::Fileinfo& info)
{
    struct stat filestat;
    ustring fullpath = p;
    fullpath += entry->d_name;
    // Get the statistics of file
    if (stat(fullpath.c_str(), &filestat) != -1) {
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
        return true;
    } else {
        showErrorCode(fullpath.c_str());
        return false;
    }
}

}

