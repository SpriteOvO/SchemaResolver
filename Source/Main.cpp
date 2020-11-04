#include <iostream>

#include "Config.h"
#include "Logger.h"
#include "IResolver.h"


int main()
{
    SetConsoleTitleW(L"SchemaResolver v" SR_VERSION_STRING);

    Log<ConCol::Bright>(L"**************************************************\n");
    Log<ConCol::Bright>(L"*             Schema module resolver             *\n");
    Log<ConCol::Bright>(L"* Version: %-38S*\n", SR_VERSION_STRING);
    Log<ConCol::Bright>(L"*  GitHub: SpriteOvO/SchemaResolver              *\n");
    Log<ConCol::Bright>(L"**************************************************\n\n");
    
    while (true)
    {
        std::wstring SchemaName;
        std::vector<std::wstring> vRedirectedNames;

        Log<ConCol::Green>(L"[+] Input schema module name: ");
        std::wcin >> SchemaName;

        if (!IResolver::GetInstance().ResolveSchemaModule(SchemaName, vRedirectedNames)) {
            Log<ConCol::Red>(L"[-] Resolve failed.\n");
        }
        else
        {
            if (vRedirectedNames.empty()) {
                Log<ConCol::Red>(L"[-] No results found.\n");
            }
            else if (vRedirectedNames.size() == 1) {
                Log<ConCol::Green>(L"[+] Resolve result: ");
                Log<ConCol::Default>(vRedirectedNames.front() + L"\n");
            }
            else
            {
                Log<ConCol::Green>(L"[+] Resolve results: ");

                std::wstring RedirectedNames;
                for (auto Iterator = vRedirectedNames.cbegin(); Iterator != vRedirectedNames.cend(); ++Iterator)
                {
                    RedirectedNames += *Iterator;

                    // If not the last element
                    //
                    if (Iterator + 1 != vRedirectedNames.cend()) {
                        RedirectedNames += L" / ";
                    }
                }

                Log<ConCol::Default>(RedirectedNames + L"\n");
            }
        }

        Log(L"\n");
    }

    return 0;
}
