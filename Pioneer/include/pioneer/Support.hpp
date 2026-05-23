#ifndef PIONEER_SUPPORT_HPP
#define PIONEER_SUPPORT_HPP

#ifdef _WIN32
#   ifdef PIONEER_LIBRARY_BUILD
#       define PIONEER_API __declspec(dllexport)
#   else
#       define PIONEER_API __declspec(dllimport)
#   endif
#else
#   ifdef PIONEER_LIBRARY_BUILD
#       define PIONEER_API __attribute__((visibility("default")))
#   else
#       define PIONEER_API
#   endif
#endif

//#ifdef PIONEER_LIBRARY_BUILD
//#   ifdef _WIN32
//#       define PIONEER_API __declspec(dllexport)
//#   else
//#       define PIONEER_API __attribute__((visibility("default")))
//#   endif
//#else
//#   ifdef _WIN32
//#       define PIONEER_API __declspec(dllimport)
//#   else
//#       define PIONEER_API
//#   endif
//#endif

#endif // !PIONEER_SUPPORT_HPP
