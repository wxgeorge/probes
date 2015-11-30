#include "nca/operations/provision.h"
#include "nca/helpers.h"
#include "nclppv2/nclpp.h"
#include <iostream>
#include <string>
#include <memory>

int main() {
	nca::ProvisionOperation pop;

	if(!nclpp::init("provision-nca")) {
		std::cerr << "Initialization failed. Bailing out.\n";
		exit(1);
	}

	pop.set_candidate_provision_ready_callback(
		[](nca::ProvisionOperation* pop) {
			std::shared_ptr<nca::CandidateProvision> cp = pop->get_candidate_provision();
			NclBool led_hash[NCL_LEDS];
			cp->get_led_hash(led_hash);

			std::cout << "Agreed with nymi band. Led hash="
				<< led_hash[0]
				<< led_hash[1]
				<< led_hash[2]
				<< led_hash[3]
				<< led_hash[4] << "\n";
			std::cout << "Proceed with enrollment? (y/n)\n";
			std::string in;
			while(true){
				std::getline(std::cin, in);
				if(in == "y" || in == "n"){
					break;
				}
				std::cout << "Invalid character. Enter 'y' or 'n': ";
			}
			
			if(in == "y") {
				cp->accept();
			} else {
				cp->reject();
			}
		}
	);
	pop.discover_enrolled_nymis();

	std::cout << "Initiating provisioning. Please put your band in provisioning mode.\n";
	pop.execute_in_foreground();

	nclpp::finish();

	if(!pop.succeeded()) {
		std::cerr << "Provisioning failed!\n";
		std::cerr << "Failure code = " << (int)pop.get_failure_code() << "\n";
		std::cerr << "Failure details '" << pop.get_failure_details() << "'\n";
		exit(1);
	}

	std::cout << "Provisioning succeeded!\n";
	std::cout << "Provision id = '" << nca::helpers::to_hex_string(pop.get_provision().id, NCL_ID_SIZE) << "'\n";
}