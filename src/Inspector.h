/* 
 * File:   Inspector.h
 * Author: Yinka
 *
 * Created on 2016-03-09, 13:41
 */

#ifndef FINSPECTOR_INSPECTOR__
#define FINSPECTOR_INSPECTOR__

#include <ctime>
#include <cstdint>
#include <sys/types.h>
#include <vector>
#include <glibmm/ustring.h>

#include "Helper/Fstr.h"
#include "Core/FileExplorer.h"
//#include "Rules/BasicRule.h"


using namespace std;

namespace FInspector {

    class Inspector {

    public:
        // Initializers
        Inspector();
        Inspector(const Inspector &orig);
        
        // Setup related functions
        bool setDestinationFolder(const Glib::ustring& f);
        bool setSourceFolder(const Glib::ustring& f);
        // Destructor...
        virtual ~Inspector();
    protected:
        
    private:

    };

}
#endif /* FINSPECTOR_INSPECTOR__ */

