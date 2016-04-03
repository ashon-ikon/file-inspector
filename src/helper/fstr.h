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

#define FS_DEFAULT_TRIM_STRING " \t\n\r\v\f"
#define FS_DEFAULT_TRIM_CHAR ' '

namespace FInspector {
    

class Fstr {
public:
    /**
     * Returns a new trimmed string object
     * @param Glib::ustring str
     * @param Glib::ustring purge
     * @param std::locale loc
     * @return Glib::ustring 
     */
    static Glib::ustring& trim(
        Glib::ustring& str,
        const Glib::ustring& purge = FS_DEFAULT_TRIM_STRING,
        const std::locale& loc = std::locale::classic()
    );
    /** 
     * Returns a new trimmed string object
     * @param Glib::ustring str
     * @param char purge
     * @param std::locale loc
     * @return Glib::ustring 
     */
    static Glib::ustring& trim(
        Glib::ustring& str,
        const char& purge = FS_DEFAULT_TRIM_CHAR,
        const std::locale& loc = std::locale::classic()
    );

    /**
     * Removes any unwanted characters from left
     * @param Glib::ustring str
     * @param std::locale loc
     * @return Glib::ustring
     */
    static Glib::ustring& ltrim(
        Glib::ustring&,
        const Glib::ustring& purge = FS_DEFAULT_TRIM_STRING,
        const std::locale& loc = std::locale::classic()
    );

    /**
     * Removes any unwanted characters from left
     * @param Glib::ustring str
     * @param char loc
     * @return Glib::ustring
     */
    static Glib::ustring& ltrim(
        Glib::ustring&,
        const char& purge = FS_DEFAULT_TRIM_CHAR,
        const std::locale& loc = std::locale::classic()
    );

    /**
     * Returns a new right trimmed string object
     * @param Glib::ustring str
     * @param std::locale loc
     * @return  Glib::ustring
     */
    static Glib::ustring& rtrim(
        Glib::ustring&,
        const Glib::ustring& purge = FS_DEFAULT_TRIM_STRING,
        const std::locale& loc = std::locale::classic()
    );

    /**
     * Returns a new right trimmed string object
     * @param Glib::ustring str
     * @param std::locale loc
     * @return  Glib::ustring
     */
    static Glib::ustring& rtrim(
        Glib::ustring&,
        const char& purge = FS_DEFAULT_TRIM_CHAR,
        const std::locale& loc = std::locale::classic()
    );

protected:
private:

};

}
#endif /* __FINSPECTOR_FSTR_H__ */

