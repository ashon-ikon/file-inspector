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

#include "Helper/Fstr.h"
#include "Helper/FileExplorer.h"


using namespace std;

namespace FInspector {

    class Inspector {

    public:
        Inspector();
        Inspector(const Inspector &orig);
        virtual ~Inspector();
    protected:
        
    private:

    };

}
#endif /* __FINSPECTOR_INSPECTOR__ */

