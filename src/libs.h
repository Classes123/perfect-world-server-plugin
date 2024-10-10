#ifndef LIBS_H
#define LIBS_H

#include <cassert>
#include "libs/libsigscan.h"

extern "C"
{
#include "libs/libdetour.h"
}

inline void *GetFuncPtr(const char *signature)
{
    void *ptrFunc = sigscan(signature);
    assert(ptrFunc != nullptr);
    return ptrFunc;
}

inline void *GetFuncPtr(const char *module, const char *signature)
{
    void *ptrFunc = sigscan_module(module, signature);
    assert(ptrFunc != nullptr);
    return ptrFunc;
}

#endif // LIBS_H