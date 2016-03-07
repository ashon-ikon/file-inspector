##
## Written by Yinka
##
##

AC_INIT([file-inspector], [0.0.1], [gigalimit20@yahoo.com])

## Automake stuff
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIRS([m4])

## Configuration stuff
AC_CONFIG_HEADERS([config.h])

## Build Tools Checks
AC_PROG_CXX
AC_PROG_LIBTOOL


## Dependency checks
PKG_CHECK_MODULES([FI_DEPS], [gtkmm-3.0 >= 3.8.0 glibmm-2.4])


## Make files
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT

echo -e "\n\n"
echo -e "All is very good!"
echo -e "\n\n"
echo -e "\n\n"

