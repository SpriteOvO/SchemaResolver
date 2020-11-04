#pragma once

#include <string>

#include <Windows.h>
#include <assert.h>

#include "Config.h"

#define SR_TO_STRING_INTERNAL(v)       # v
#define SR_TO_STRING(v)                SR_TO_STRING_INTERNAL(v)

#if defined _DEBUG
# define SR_ASSERT(condition)    while(!(condition)) { __debugbreak(); }
#else
# define SR_ASSERT(condition)    while(!(condition)) { MessageBoxW(NULL, L"An runtime error has occurred!\n\nCondition: " SR_TO_STRING(condition) "\nFunction: " __FUNCTION__ "\nLine: " SR_TO_STRING(__LINE__) "\nFile: " __FILE__, L"SchemaResolver v" SR_VERSION_STRING, MB_ICONERROR); std::terminate(); }
#endif

#define SR_UNUSED(...)          __VA_ARGS__

#include "Native.h"


namespace std
{
#ifdef UNICODE
    using tstring = std::wstring;
#else
    using tstring = std::string;
#endif

} // namespace std


namespace System
{
    namespace Version
    {
        bool IsXpOrGreater();
        bool IsXpSp1OrGreater();
        bool IsXpSp2OrGreater();
        bool IsXpSp3OrGreater();
        bool IsVistaOrGreater();
        bool IsVistaSp1OrGreater();
        bool IsVistaSp2OrGreater();
        bool Is7OrGreater();
        bool Is7Sp1OrGreater();
        bool Is8OrGreater();
        bool Is81OrGreater();
        bool Is10OrGreater();

    } // namespace Version

} // namespace System


namespace Text
{
    std::wstring ToLower(const std::wstring &String);

} // namespace Text


namespace Thread
{
    TebT* GetCurrentTeb();

} // namespace Thread


namespace Process
{
    PebT* GetCurrentPeb();

} // namespace Process
