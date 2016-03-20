/* 
 * File:   ustring.h
 * Author: yinka
 *
 * Created on 19 March 2016, 10:05 PM
 */

#ifndef __FINSPECTOR_FSTR_H__
#define __FINSPECTOR_FSTR_H__

#include <glibmm/ustring.h>
#include <iostream>

namespace FInspector {

class Fstr {
public:
    /**
     * Returns a new trimmed Fstr object
     * @return 
     */
    static
    Fstr trim();
    /**
     * Returns a new left trimmed Fstr object
     * @return 
     */
    static
    Fstr ltrim();
    /**
     * Returns a new right trimmed Fstr object
     */
    static
    Fstr rtrim();
private:

};

}
#endif /* __FINSPECTOR_FSTR_H__ */

