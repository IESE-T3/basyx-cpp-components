#pragma once

#include <basyx/environment.h>
#include <basyx/api/aas_api.h>

namespace basyx {
namespace api {

class AasEnvApi : public basyx::api::AasInterface
{
private:
	Environment & env;
public:
	AasEnvApi(Environment & env) : env(env) {};
public:
	std::vector<AssetAdministrationShell*> getAssetAdministrationShells() override
	{
		std::vector<AssetAdministrationShell*> aasList;

		for (const auto & entry : env.getAssetAdministrationShells())
			aasList.push_back(entry.get());

		return aasList;
	};

	AssetAdministrationShell * getAssetAdministrationShell(util::string_view idShort) override
	{
		return env.getAssetAdministrationShells().get(idShort);
	};

	AssetAdministrationShell * getAssetAdministrationShell(Identifier identifier) override
	{
		for (const auto & entry : env.getAssetAdministrationShells())
			if (entry->getIdentification() == identifier)
				return entry.get();

		return nullptr;
	};

	AssetAdministrationShell * putAssetAdministrationShell(const AssetAdministrationShell & aas) override
	{
		for (const auto & entry : env.getAssetAdministrationShells())
			if (entry->getIdentification() == aas.getIdentification())
				return nullptr;

		return this->env.getAssetAdministrationShells().add(aas);
	};

	AssetAdministrationShell * patchAssetAdministrationShell(AssetAdministrationShell & aas) override
	{
		return nullptr;
	};

	Reference putSubmodelReference(Reference & submodel) override
	{
		return Reference{ Key("test") };
	};

	bool removeSubmodelReference(Reference & submodel) override
	{
		return false;
	};
};

}
}
