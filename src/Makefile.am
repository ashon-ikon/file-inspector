##
## Written by Yinka
##
## This is our main source make file template
##
##
bin_PROGRAMS=$(top_builddir)/bin/inspector
__top_builddir__bin_inspector_SOURCES= \
	Helper/Fstr.cc \
	Helper/FileExplorer.cc \
	Inspector.cc \
	main.cc
__top_builddir__bin_inspector_LDADD=$(FI_DEPS_LIBS)
__top_builddir__bin_inspector_CXXFLAGS=-g -std=c++11 -Wall -Werror -pedantic
__top_builddir__bin_inspector_CPPFLAGS=$(FI_DEPS_CFLAGS)
