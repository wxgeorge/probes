#include "nymi-api.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace nymi;

std::string neaName = "provision-test";
static std::string current_time_as_string(std::string format="%Y-%m-%d_%H_%M_%S");


int main() {
	// We begin by configuring persistence.
	// We will not save the results from these run.
	{
		PersistenceConfiguration pConfig;
		pConfig.neaName = neaName;
		pConfig.strategy = Persistence::file;
		pConfig.filename = "napi-" + current_time_as_string() + ".json";
		Nymi::api().configurePersistence(pConfig);
	}

	bool init_result = Nymi::api().init(neaName,
		[](std::shared_ptr<InitAPI> iapi){ iapi->setLog("ncl.log"); } );
	if(!init_result) {
		std::cerr << "Nymi::api()::init() failed! Bailing out.\n";
		return 1;
	}

	std::cout << "Setting up provisioning ... ";
	// now confi

	std::condition_variable provisioning_complete;
	std::string m_prov_id;
	bool provisioning_succeeded=false;
	Nymi::api().configureProvisioning(
		[&provisioning_complete, &m_prov_id,&provisioning_succeeded]
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
				[&provisioning_complete,&m_prov_id,&provisioning_succeeded]
				(std::string pid){
					std::cout << "New provision available: " << pid << "\n";
					m_prov_id=pid;
					provisioning_succeeded=true;
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
		return 1;
	}

	if(!provisioning_succeeded) {
		std::cerr << "Done waiting for provisioning, but provisioning not marked as succeeded. Bailing out.\n";
		return 1;
	}

	std::cout << "Initiating GetSymmetricKey ...\n";
    std::shared_ptr< GetSymmetricKeyAPI > getsk = Nymi::api().getSymmetricKey(m_prov_id);
    WorkOutcome wout = getsk->waitForDone();

    if(WorkOutcome::succeeded != wout) {
        // handle error.
        std::cerr << "GetSymmetricKeyAPI failed. Outcome: " << wout;
        std::vector < std::pair< int, std::string > > v;
        getsk->getErrors(v);
        if(v.size() > 0) {
            std::cerr << "More details:";
            for ( std::pair< int, std::string> p : v ) {
                std::cerr << std::get<0>(p) << " " << std::get<1>(p);
            }
        }
        return 1;
    }

    std::cout << "GetSymmetricKeyAPI succeeded.\n";
    std::cout << "Id  = " << getsk->getSymmetricKeyIdAsString() << "\n";
    std::cout << "Key = " << getsk->getSymmetricKeyAsString()   << "\n";

	Nymi::api().finish();
	return 0;
}

#include <ctime>
// from heartid/CodeCpp
/// Returns the system time in Y-M-D_HH_MM_SS format
std::string current_time_as_string(std::string format_string)
{
	time_t timeSeconds=std::time(NULL);
#pragma warning(push)
#pragma warning(disable: 4996) // disable _CRT_SECURE_NO_WARNINGS 
	struct tm* timeStruct=localtime(&timeSeconds);
#pragma warning(pop)
	char buffer[256];
	strftime(
		buffer, sizeof(buffer),
		format_string.c_str(),
		timeStruct
	);
	return std::string(buffer);
}
