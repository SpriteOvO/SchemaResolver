#include "IResolver.h"
#include "Utils.h"


IResolver& IResolver::GetInstance()
{
    static IResolver i;
    return i;
}

IResolver::IResolver()
{
    InitializeApiSchema();
}

bool IResolver::ResolveSchemaModule(const std::wstring &SchemaModuleName, std::vector<std::wstring> &RedirectedModuleName)
{
    std::wstring SchemaName = Text::ToLower(SchemaModuleName);

    auto Iterator = std::find_if(_ApiSchema.begin(), _ApiSchema.end(),
        [&SchemaModuleName](const auto &rhs) {
            return SchemaModuleName.find(rhs.first) != std::wstring::npos;
        }
    );

    if (Iterator == _ApiSchema.end()) {
        return false;
    }

    const std::vector<std::wstring> &vHosts = Iterator->second;
    if (vHosts.empty()) {
        return false;
    }

    RedirectedModuleName = vHosts;
    return true;
}

void IResolver::InitializeApiSchema()
{
    if (System::Version::Is10OrGreater())
    {
        InitializeApiSchemaInternal<
            ApiSet::_10::NamespaceArrayT,
            ApiSet::_10::NamespaceEntryT,
            ApiSet::_10::ValueArrayT,
            ApiSet::_10::ValueEntryT
        >();
    }
    else if (System::Version::Is81OrGreater())
    {
        InitializeApiSchemaInternal<
            ApiSet::_81::NamespaceArrayT,
            ApiSet::_81::NamespaceEntryT,
            ApiSet::_81::ValueArrayT,
            ApiSet::_81::ValueEntryT
        >();
    }
    else if (System::Version::Is7OrGreater())
    {
        InitializeApiSchemaInternal<
            ApiSet::_7_8::NamespaceArrayT,
            ApiSet::_7_8::NamespaceEntryT,
            ApiSet::_7_8::ValueArrayT,
            ApiSet::_7_8::ValueEntryT
        >();
    }
}

template <class ApiSetMapT, class ApiSetEntryT, class HostArrayT, class HostEntryT>
void IResolver::InitializeApiSchemaInternal()
{
    PebT *pPeb = Process::GetCurrentPeb();
    ApiSetMapT *pApiSetMap = (ApiSetMapT*)pPeb->ApiSetMap();

    for (uint32_t i = 0; i < pApiSetMap->Count; ++i)
    {
        ApiSetEntryT *pDescriptor = pApiSetMap->Entry(i);
        HostArrayT *pHostArray = pApiSetMap->ValueArray(pDescriptor);

        std::vector<std::wstring> vHosts;
        std::wstring ModuleName = Text::ToLower(pApiSetMap->ApiName(pDescriptor));

        for (uint32_t j = 0; j < pHostArray->Count; ++j)
        {
            HostEntryT *pHost = pHostArray->Entry(pApiSetMap, j);

            std::wstring HostName = pHost->HostName(pApiSetMap);
            if (!HostName.empty()) {
                vHosts.emplace_back(std::move(HostName));
            }
        }

        _ApiSchema.emplace_back(std::make_pair(ModuleName, std::move(vHosts)));
    }
}