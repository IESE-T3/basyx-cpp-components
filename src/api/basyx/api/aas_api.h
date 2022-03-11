#pragma once

#include <basyx/assetadministrationshell.h>

namespace basyx {
namespace api {

class AasInterface
{
public:
	virtual ~AasInterface() = default;
public:
	virtual std::vector<AssetAdministrationShell*> getAssetAdministrationShells() = 0;
	virtual AssetAdministrationShell * getAssetAdministrationShell(util::string_view idShort) = 0;
	virtual AssetAdministrationShell * getAssetAdministrationShell(Identifier identifier) = 0;
	virtual AssetAdministrationShell * putAssetAdministrationShell(const AssetAdministrationShell & aas) = 0;
	virtual AssetAdministrationShell * patchAssetAdministrationShell(AssetAdministrationShell & aas) = 0;

	virtual Reference putSubmodelReference(Reference & submodel) = 0;
	virtual bool removeSubmodelReference(Reference & submodel) = 0;
};

}
}
