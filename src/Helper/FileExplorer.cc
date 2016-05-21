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
#include <limits>
#include <sys/stat.h>
#include <unistd.h>

#include "FileExplorer.h"
#include "Fstr.h"
#include "Rules/BasicRule.h"
#include "stlHelpers.h"

using namespace std;
using namespace Glib;

namespace FInspector {

/**
 * Comparator operator used for sorting Fileinfo objects
 * @param rhs
 * @return 
 */
bool FileExplorer::Fileinfo::operator < (const Fileinfo& rhs) {
    return (path.lowercase() < rhs.path.lowercase());
}

/**
 * Default constructor
 */
FileExplorer::FileExplorer() {
    // We need to set the local
    std::locale::global(std::locale(""));
}

/**
 * Copy constructor
 * @param orig
 */
FileExplorer::FileExplorer(const FileExplorer& orig) {

}

/**
 * Destructor
 */
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

/**
 * Checks if file is of regular type
 * @param fi
 * @return 
 */
bool FileExplorer::isRegularFile(Fileinfo& fi) {
    return fi.type == RegularFile;

}

/**
 * Returns true if file is a directory
 * @param p
 * @return 
 */
bool FileExplorer::isDirectory(const char* p) {
    bool is = false;
    struct stat st;
    if (stat(p, &st) != -1) {
        is = S_ISDIR(st.st_mode);
    };
    
    return is;
}

/**
 * Handy function to show error code
 * @param filepath
 */
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

/**
 * Returns the string equivalent of file type
 * @param ft
 * @return Glib::ustring
 */
ustring FileExplorer::getTypeAsString(const FileType& ft) {
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
 * Gets the content of a path
 * @param p
 * @param deep
 * @param includeHidden
 * @return 
 */
vector< FileExplorer::Fileinfo >
FileExplorer::getDirectoryContent(const ustring& p, bool deep, bool includeHidden) {
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
                // Check if we are to ignore hidden files
                // On UNIX-like systems this will be anything
                // matching "." or ".."
                if ((! includeHidden && '.' == entry->d_name[0])
                || ('.' == entry->d_name[0] && '.' == entry->d_name[1])) {
                    // This is a hidden file or same directory, skip
                    continue;
                }
                Fileinfo info;
                if (getFileInfo(tp, entry, info)) {
                    // Add it
                    content.push_back(info);
                    // Check if we should add the content recursively
                    if (deep) {
                        content += getDirectoryContent(info.path, deep, includeHidden);
                    }
                }
            }
            // We are done close it
            closedir(dp);

        } else {
            showErrorCode(tp.c_str());
            // Failed to open the directory
            // Throw exception?
        }
    }
    
    /*
     * Attempt to sort the content if any
     */
    if (content.size() > 0) {
        // Sort the items
        std::sort(content.begin(), content.end());
    }

    return content;
}

/**
 * Gets the information about a file
 * Returns true if info was retrieved successfully
 * @param p ustring
 * @param entry dirent
 * @param info FileInfo
 */
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

/**
 * Attempts to get the full path of the uri.
 * On failure, returns the original uri
 * @param uri
 * @return 
 */
ustring& FileExplorer::getFullPath(ustring& uri) {
    // If it's not a valid directory attempt to combine with current working
    // directory
    if (! isDirectory(uri.c_str())) {
        char* path = realpath(uri.c_str(), NULL);
        if (path != NULL && isDirectory(path)) {
            uri = path;
        }
        delete path;
        std::cout << "cwd: '" << uri << "' " << std::endl;
    }
    return uri;
}

}

