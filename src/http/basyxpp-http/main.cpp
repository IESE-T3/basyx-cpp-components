#include <basyxpp-http/SubmodelRepositoryHttpHandler.h>

#include <spdlog/spdlog.h>

#include <basyx/submodel.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>

#include <basyx/api/impl/aas_env_api.h>

#include <basyxpp-http/HttpHandler.h>

using namespace basyx;
using namespace basyx::http;

int main()
{
	spdlog::info("BaSyx C++ AAS REST server");

	AssetInformation asset_inf_1{ AssetKind::Instance };
	AssetAdministrationShell aas_1{ "aas_1", Identifier::IRI("https://admin-shell.io/cpp#aas_1"), asset_inf_1 };

	// Create submodels
	auto sm = aas_1.getSubmodels().create<Submodel>("sm1", Identifier::IRI("https://admin-shell.io/cpp#sm1"));
	sm->setCategory("test");
	sm->setSemanticId("0173-1#02-AAR972#002");
	sm->setAdministration({ "1.0", "v2" });

//  std::unique_ptr<api::SubmodelInterface> p{new api::SubmodelMetamodel(&sm)};
//  SubmodelHttpHandler handler(std::move(p), std::string("localhost"), 8080);
//	handler.run();

	Submodel sm2("sm2", Identifier::IRI("https://admin-shell.io/cpp#sm2"));

	// Add submodel elements to submodel
	sm->getSubmodelElements().add(Property<std::string>("testProperty1", "Yay a value!"));
	sm->getSubmodelElements().add(Property<std::string>("testProperty2", "Values and values! :O"));
	sm->getSubmodelElements().add(Property<uint32_t>("intProp", 32));

	sm->getSubmodelElements().add(SubmodelElementCollection("collection",
		MultiLanguageProperty("multiLang", { { "de", "beispiel" }, { "en", "example" } }),
		Property<float>("floatProp", 5.0f),
		SubmodelElementCollection("collection2",
			Property<float>("floatProp", 5.0f),
			Property<float>("floatProp2", 5.0f))));


	AssetInformation asset_inf_2{ AssetKind::Instance };
	AssetAdministrationShell aas_2{ "aas_2", Identifier::IRI("https://admin-shell.io/cpp#aas_2"), asset_inf_2 };

	Environment env;
	env.getAssetAdministrationShells().add(std::move(aas_1));
	env.getAssetAdministrationShells().add(std::move(aas_2));

	// Add to handler and start server
	auto handler = basyx::http::HttpHandler::make_http_handler<api::AasEnvApi>("127.0.0.1", 8080, env);
	handler->run();

	return 0;
}
