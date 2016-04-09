/* 
 * File:   Inspector.h
 * Author: Yinka
 *
 * Created on 2016-03-09, 13:41
 */

#ifndef __FINSPECTOR_INSPECTOR__
#define __FINSPECTOR_INSPECTOR__

#include <ctime>
#include <cstdint>
#include <sys/types.h>
#include <vector>
#include <glibmm/ustring.h>

#include "helper/fstr.h"

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

using namespace std;

namespace FInspector {

    enum FileType {
        RegularFile = 1,
        Directory,
        SymLink,
        Other
    };

    class Inspector {

    public:
        Inspector();
        Inspector(const Inspector &orig);
        virtual ~Inspector();

        struct Fileinfo {
            Glib::ustring filename;
            Glib::ustring path;
            Glib::ustring re;
            time_t lastModifed;
            uintmax_t size;
            FileType type;

            bool operator<(const Fileinfo &rhs);
        };



        vector < Fileinfo> static
        getDirectoryContent(const Glib::ustring &p, bool includeHidden = false);

        bool isRegularFile(Fileinfo &f);
        static Glib::ustring getType(FileType ft);
    protected:
        
    private:

    };

    typedef vector< Inspector::Fileinfo > DirectoryCollection;
}
#endif /* __FINSPECTOR_INSPECTOR__ */

