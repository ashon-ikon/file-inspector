/* 
 * File:   FileExplorer.h
 * Author: Yinka
 *
 * Created on 9 April 2016, 3:51 PM
 */

#ifndef FINSPECTOR_HELPER_FILE_EXPLORER_H__
#define FINSPECTOR_HELPER_FILE_EXPLORER_H__

#include <algorithm>
#include <glibmm/ustring.h>
#include <functional>
#include <vector>

/*
 * Some macros
 * 
 */
// Define directory separator
#if defined(OS_WINDOWS) || defined(_WIN32) || defined(WIN32)
    #ifndef FS_DIRECTORY_SEPARATOR
        #define FS_DIRECTORY_SEPARATOR '\\'
    #endif
#else
    #ifndef FS_DIRECTORY_SEPARATOR
        #define FS_DIRECTORY_SEPARATOR '/'
    #endif
#endif


using std::vector;


namespace FInspector {

/**
 * Types of File
 */
enum FileType {
    RegularFile = 1,
    Directory,
    SymLink,
    Other
};


/**
 * File Explorer class
 */
class FileExplorer {
public:
    FileExplorer ();
    FileExplorer (const FileExplorer &orig);
    virtual ~ FileExplorer ();

    struct Fileinfo {
        Glib::ustring filename;
        Glib::ustring path;
        Glib::ustring re;
        time_t lastModifed;
        uintmax_t size;
        FileType type;

        bool operator<(const Fileinfo &rhs);
    };
    /**
     * True if string is a directory
     * @param 
     * @return 
     */
    bool static isDirectory(const char*);
    vector < Fileinfo > static
    getDirectoryContent(const Glib::ustring &p, bool includeHidden = false);

    bool isRegularFile(Fileinfo &f);
    static Glib::ustring getType(const FileType& ft);
private:

};

typedef vector< FileExplorer::Fileinfo > DirectoryCollection;

}
#endif /* FINSPECTOR_HELPER_FILE_EXPLORER_H__ */

