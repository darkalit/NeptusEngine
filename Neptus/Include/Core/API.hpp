#pragma once

#ifdef _MSC_VER
#define NP_API
#ifdef NEPTUS_ENGINE_SHARED
#define NP_API __declspec(dllexport)
#endif
#else
#define NP_API
#endif
