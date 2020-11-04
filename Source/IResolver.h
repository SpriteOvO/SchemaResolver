#pragma once

#include <string>
#include <vector>
#include <list>


class IResolver
{
public:
    static IResolver& GetInstance();

    IResolver();

    bool ResolveSchemaModule(const std::wstring &SchemaModuleName, std::vector<std::wstring> &RedirectedModuleName);

private:
    std::list<std::pair<std::wstring, std::vector<std::wstring>>> _ApiSchema;

    void InitializeApiSchema();

    template <class ApiSetMapT, class ApiSetEntry, class HostArrayT, class HostEntryT>
    void InitializeApiSchemaInternal();

};
