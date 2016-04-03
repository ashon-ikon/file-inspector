/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fstr.cc
 * Author: yinka
 * 
 * Created on 19 March 2016, 8:05 PM
 */

#include "fstr.h"
#include <functional>
#include <algorithm>

typedef Glib::ustring gstring;

using std::string;
using std::bind;
using std::cref;
using std::locale;
using namespace std::placeholders;

namespace FInspector {

//static const gstring excludeChars = DEFAULT_TRIM_STRING;

static inline bool purgeCharacter(const gstring::value_type c, const gstring& chrList, const locale loc) {
    bool remove = false;
    if (chrList.empty()) {
        remove = !! isspace(c, loc);
    } else {
        remove = chrList.find(c) != std::string::npos;
    }
    return remove;
}

/**
 * Returns a left Trimmed string
 * @return 
 */
gstring& Fstr::ltrim(gstring& str, const gstring& purge, const std::locale& loc) {
    auto rmFn = bind(purgeCharacter, _1, std::cref(purge), std::cref(loc));
    str.erase(str.begin(), find_if(str.begin(), str.end(), rmFn));
    return str;
}

/**
 * Returns a right Trimmed string
 * @return 
 */
gstring& Fstr::rtrim(gstring& str, const gstring& purge, const std::locale& loc) {
    auto rmFn = bind(purgeCharacter, _1, std::cref(purge), std::cref(loc));
    // Erase from the first occurrence of any of the purge characters
    str.erase(find_if(str.rbegin(), str.rend(), rmFn).base(), str.end());
    return str;
}

/**
 * Returns a Trimmed string
 * @return 
 */
gstring& Fstr::trim(gstring& str, const gstring& purge, const std::locale& loc) {
    
    return ltrim(rtrim(str));
}

}
