#pragma once

#if defined(SHARED)
#define KW_EXPORT __declspec(dllexport)
#else
#define KW_EXPORT __declspec(dllimport)
#endif
