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
#include <string>
#include <locale>

namespace FInspector {
    
    extern static const std::string excludeChars;

class Fstr {
public:
    /**
     * Returns a new trimmed string object
     * @return Glib::ustring 
     */
    static Glib::ustring trim(
        const Glib::ustring &,
        const Glib::ustring purge = excludeChars,
        std::locale &loc = std::locale::classic()
    );

    /**
     * 
     * @param  Glib::ustring str
     * @param std::locale loc
     * @return Glib::ustring 
     */
    static Glib::ustring trim(
        const std::string &,
        const std::string purge = excludeChars,
        std::locale &loc = std::locale::classic()
    );

    /**
     * Removes any unwanted characters from left
     * @param Glib::ustring str
     * @param std::locale loc
     * @return Glib::ustring
     */
    static Glib::ustring ltrim(
        const Glib::ustring &,
        const Glib::ustring purge = excludeChars,
        std::locale &loc = std::locale::classic()
    );

    /**
     * Returns a new right trimmed string object
     * @param Glib::ustring str
     * @param std::locale loc
     * @return  Glib::ustring
     */
    static Glib::ustring rtrim(
        const Glib::ustring &,
        const Glib::ustring purge = excludeChars,
        std::locale &loc = std::locale::classic()
    );

protected:
private:

};

}
#endif /* __FINSPECTOR_FSTR_H__ */

