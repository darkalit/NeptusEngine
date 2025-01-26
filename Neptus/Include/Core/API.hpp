#pragma once

#ifdef _MSC_VER
    #ifdef NEPTUS_SHARED
        #ifdef NEPTUS_ENGINE_EXPORTS
            #define NP_API __declspec(dllexport)
        #else
            #define NP_API __declspec(dllimport)
        #endif
    #endif
    #ifndef NP_API
        #define NP_API
    #endif
#else
    #define NP_API
#endif
