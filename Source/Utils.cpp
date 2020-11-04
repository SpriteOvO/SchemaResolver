#include "Utils.h"

#include <algorithm>


namespace Text
{
    std::wstring ToLower(const std::wstring &String)
    {
        std::wstring Result = String;
        std::transform(Result.begin(), Result.end(), Result.begin(), towlower);
        return Result;
    }

} // namespace Text


namespace System
{
    namespace Version
    {
        class WinVerT
        {
        public:
            static WinVerT& GetInstance()
            {
                static WinVerT i;
                return i;
            }

            WinVerT()
            {
                InitVersionInfo();
            }

            bool IsVersionOrGreater(uint16_t MajorVersion, uint16_t MinorVersion, uint16_t ServicePackMajor, uint16_t BuildVersion)
            {
                if (VersionInfo.dwMajorVersion != 0)
                {
                    if (VersionInfo.dwMajorVersion > MajorVersion) {
                        return true;
                    }
                    else if (VersionInfo.dwMajorVersion < MajorVersion) {
                        return false;
                    }

                    if (VersionInfo.dwMinorVersion > MinorVersion) {
                        return true;
                    }
                    else if (VersionInfo.dwMinorVersion < MinorVersion) {
                        return false;
                    }

                    if (VersionInfo.wServicePackMajor > ServicePackMajor) {
                        return true;
                    }
                    else if (VersionInfo.wServicePackMajor < ServicePackMajor) {
                        return false;
                    }

                    if (VersionInfo.dwBuildNumber >= BuildVersion) {
                        return true;
                    }
                }

                return false;
            }

        private:
            RTL_OSVERSIONINFOEXW VersionInfo;

            void InitVersionInfo()
            {
                memset(&VersionInfo, 0, sizeof(VersionInfo));

                HMODULE NtdllModule = GetModuleHandleW(L"ntdll.dll");
                if (NtdllModule == NULL) {
                    return;
                }

                auto FnRtlGetVersion = (FnRtlGetVersionT)GetProcAddress(NtdllModule, "RtlGetVersion");
                if (FnRtlGetVersion == NULL) {
                    return;
                }

                VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
                if (FnRtlGetVersion((RTL_OSVERSIONINFOW*)&VersionInfo) != STATUS_SUCCESS) {
                    return;
                }
            }

        };

        bool IsXpOrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0, 0);
        }

        bool IsXpSp1OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 1, 0);
        }

        bool IsXpSp2OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 2, 0);
        }

        bool IsXpSp3OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 3, 0);
        }

        bool IsVistaOrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0, 0);
        }

        bool IsVistaSp1OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 1, 0);
        }

        bool IsVistaSp2OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 2, 0);
        }

        bool Is7OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0, 0);
        }

        bool Is7Sp1OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 1, 0);
        }

        bool Is8OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0, 0);
        }

        bool Is81OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), LOBYTE(_WIN32_WINNT_WINBLUE), 0, 0);
        }

        bool Is10OrGreater()
        {
            return WinVerT::GetInstance().IsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0, 0);
        }

    } // namespace Version

} // namespace System


namespace Thread
{
    TebT* GetCurrentTeb()
    {
        return (TebT*)NtCurrentTeb();
    }

} // namespace Thread


namespace Process
{
    PebT* GetCurrentPeb()
    {
        return Thread::GetCurrentTeb()->Peb();
    }

} // namespace Process
