#ifndef COMPUTE_DYNAMIC_LIB_H
#define COMPUTE_DYNAMIC_LIB_H

#ifdef WIN32
#    ifdef COMPUTE_EXPORT
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#else
#    define LIBRARY_API
#endif

#endif