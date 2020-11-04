#pragma once

#include "Utils.h"

#define STATUS_SUCCESS    ((NTSTATUS)0x00000000L)

using FnRtlGetVersionT = NTSTATUS(NTAPI*)(RTL_OSVERSIONINFOW *pVersionInformation);

struct PebT
{
    void* ApiSetMap()
    {
#if defined _WIN64
        return *(void**)((uint8_t*)this + 0x68);
#else
        return *(void**)((uint8_t*)this + 0x38);
#endif
    }
};

struct TebT
{
    PebT* Peb()
    {
#if defined _WIN64
        return *(PebT**)((uint8_t*)this + 0x60);
#else
        return *(PebT**)((uint8_t*)this + 0x30);
#endif
    }
};

// Win10
//

namespace ApiSet
{
    // Windows 10
    //
    namespace _10
    {
        struct NamespaceArrayT;

        struct ValueEntryT
        {
            uint32_t Flags;
            uint32_t NameOffset;
            uint32_t NameLength;
            uint32_t ValueOffset;
            uint32_t ValueLength;

            std::wstring HostName(NamespaceArrayT *pNamespaceArray)
            {
                SR_ASSERT(ValueLength % sizeof(wchar_t) == 0);
                return std::wstring{(wchar_t*)((uint8_t*)pNamespaceArray + ValueOffset), ValueLength / 2};
            }
        };

        struct ValueArrayT
        {
            uint32_t Flags;
            uint32_t NameOffset;
            uint32_t Unk;
            uint32_t NameLength;
            uint32_t DataOffset;
            uint32_t Count;

            ValueEntryT* Entry(NamespaceArrayT *pNamespaceArray, uint32_t Index)
            {
                return (ValueEntryT*)((uint8_t*)pNamespaceArray + DataOffset + Index * sizeof(ValueEntryT));
            }
        };

        struct NamespaceEntryT
        {
            uint32_t Limit;
            uint32_t Size;
        };

        struct NamespaceArrayT
        {
            uint32_t Version;
            uint32_t Size;
            uint32_t Flags;
            uint32_t Count;
            uint32_t Start;
            uint32_t End;
            uint32_t _Unknown[2];

            NamespaceEntryT* Entry(uint32_t Index)
            {
                return (NamespaceEntryT*)((uint8_t*)this + End + Index * sizeof(NamespaceEntryT));
            }

            ValueArrayT* ValueArray(NamespaceEntryT *pEntry)
            {
                return (ValueArrayT*)((uint8_t*)this + Start + sizeof(ValueArrayT) * pEntry->Size);
            }

            std::wstring ApiName(NamespaceEntryT *pEntry)
            {
                ValueArrayT *pValueArray = ValueArray(pEntry);

                SR_ASSERT(pValueArray->NameLength % sizeof(wchar_t) == 0);
                return std::wstring{(wchar_t*)((uint8_t*)this + pValueArray->NameOffset), pValueArray->NameLength / 2};
            }
        };

    } // namespace _10

    // Windows 8.1
    //
    namespace _81
    {
        struct NamespaceArrayT;

        struct ValueEntryT
        {
            uint32_t Flags;
            uint32_t NameOffset;
            uint32_t NameLength;
            uint32_t ValueOffset;
            uint32_t ValueLength;

            std::wstring HostName(NamespaceArrayT *pNamespaceArray)
            {
                SR_ASSERT(ValueLength % sizeof(wchar_t) == 0);
                return std::wstring{(wchar_t*)((uint8_t*)pNamespaceArray + ValueOffset), ValueLength / 2};
            }
        };

        struct ValueArrayT
        {
            uint32_t Flags;
            uint32_t Count;
            ValueEntryT Array[ANYSIZE_ARRAY];

            ValueEntryT* Entry(NamespaceArrayT *pNamespaceArray, uint32_t Index)
            {
                SR_UNUSED(pNamespaceArray);
                return Array + Index;
            }
        };

        struct NamespaceEntryT
        {
            uint32_t Flags;
            uint32_t NameOffset;
            uint32_t NameLength;
            uint32_t AliasOffset;
            uint32_t AliasLength;
            uint32_t DataOffset;
        };

        struct NamespaceArrayT
        {
            uint32_t Version;
            uint32_t Size;
            uint32_t Flags;
            uint32_t Count;
            NamespaceEntryT Array[ANYSIZE_ARRAY];

            NamespaceEntryT* Entry(uint32_t Index)
            {
                return Array + Index;
            }

            ValueArrayT* ValueArray(NamespaceEntryT *pEntry)
            {
                return (ValueArrayT*)((uint8_t*)this + pEntry->DataOffset);
            }

            std::wstring ApiName(NamespaceEntryT *pEntry)
            {
                SR_ASSERT(pEntry->NameLength % sizeof(wchar_t) == 0);
                return std::wstring{(wchar_t*)((uint8_t*)this + pEntry->NameOffset), pEntry->NameLength / 2};
            }
        };

    } // namespace _81

    // Windows 7 or Windows 8
    //
    namespace _7_8
    {
        struct NamespaceArrayT;

        struct ValueEntryT
        {
            uint32_t NameOffset;
            uint32_t NameLength;
            uint32_t ValueOffset;
            uint32_t ValueLength;

            std::wstring HostName(NamespaceArrayT *pNamespaceArray)
            {
                SR_ASSERT(ValueLength % sizeof(wchar_t) == 0);
                return std::wstring{(wchar_t*)((uint8_t*)pNamespaceArray + ValueOffset), ValueLength / 2};
            }
        };

        struct ValueArrayT
        {
            uint32_t Count;
            ValueEntryT Array[ANYSIZE_ARRAY];

            ValueEntryT* Entry(NamespaceArrayT *pNamespaceArray, uint32_t Index)
            {
                SR_UNUSED(pNamespaceArray);
                return Array + Index;
            }
        };

        struct NamespaceEntryT
        {
            uint32_t NameOffset;
            uint32_t NameLength;
            uint32_t DataOffset;
        };

        struct NamespaceArrayT
        {
            uint32_t Version;
            uint32_t Count;
            NamespaceEntryT Array[ANYSIZE_ARRAY];

            NamespaceEntryT* Entry(uint32_t Index)
            {
                return Array + Index;
            }

            ValueArrayT* ValueArray(NamespaceEntryT *pEntry)
            {
                return (ValueArrayT*)((uint8_t*)this + pEntry->DataOffset);
            }

            std::wstring ApiName(NamespaceEntryT *pEntry)
            {
                SR_ASSERT(pEntry->NameLength % sizeof(wchar_t) == 0);
                return std::wstring{(wchar_t*)((uint8_t*)this + pEntry->NameOffset), pEntry->NameLength / 2};
            }
        };

    } // namespace _7_8

} // namespace ApiSet
