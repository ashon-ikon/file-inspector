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

            bool operator<(const Fileinfo &rhs) {
                return (filename.lowercase() < rhs.filename.lowercase());
            }
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

