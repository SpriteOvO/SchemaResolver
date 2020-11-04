#pragma once

#include <cstdint>
#include <string>

#include <Windows.h>


enum class ConCol : uint16_t
{
    Bright = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    Yellow = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    Purple = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,
    Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
    Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    Default = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
};

template <ConCol ConsoleColor = ConCol::Default, class ...ArgsT>
void Log(const std::wstring &Format, ArgsT &&...Args)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (uint16_t)ConsoleColor);
    fwprintf(stdout, Format.c_str(), std::forward<ArgsT>(Args)...);
    SetConsoleTextAttribute(hStdOut, (uint16_t)ConCol::Default);
}
