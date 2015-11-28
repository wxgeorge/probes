#include "nymi-api.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace nymi;

std::string neaName = "provision-test";

int main() {
	// We begin by configuring persistence.
	// We will not save the results from these run.
	{
		PersistenceConfiguration pConfig;
		pConfig.strategy = Persistence::none;
		pConfig.neaName = neaName;
		Nymi::api().configurePersistence(pConfig);
	}

	if(!Nymi::api().init(neaName)) {
		std::cerr << "Nymi::api()::init() failed! Bailing out.\n";
		exit(1);
	}

	std::cout << "Setting up provisioning ... ";
	// now confi

	std::condition_variable provisioning_complete;
	Nymi::api().configureProvisioning(
		[&provisioning_complete]
		(std::shared_ptr<ProvisionAPI> papi) {
			papi->onDiscovery(
				[](int tid, int rssi, double srssi, bool approached) {
					std::cout << "Discovery received from handle " << tid
						<< ".  Initiating provisioning\n";
					return true;
				});
			papi->onLEDPatternChange(
				[]
				(std::shared_ptr< std::unordered_set< std::string > > LEDPatterns) {
					std::cout << "LEDPatterns updated. Current set is: \n";
					for( std::string pattern : *LEDPatterns ) {
						std::cout << pattern << "\n";
					}
					std::cout << "Enter a pattern to continue provisioning\n";
					std::string my_pattern;
					std::cin >> my_pattern;
					Nymi::api().setUserLEDs(my_pattern);
				});
			papi->onProvisioned(
				[&provisioning_complete]
				(std::string pid){
					std::cout << "New provision available: " << pid << "\n";
					provisioning_complete.notify_all();
				});
		});
	std::cout << " complete!\n";

	std::cout << "Put your device in provisioning mode to continue!\n";

	std::mutex m;
	std::unique_lock<std::mutex> lk(m);
	auto cv_status = provisioning_complete.wait_for(lk, std::chrono::seconds(60));
	if(cv_status == std::cv_status::timeout) {
		std::cerr << "Timed-out waiting for provision.";
	}
	Nymi::api().finish();
	return 0;
}