#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
	int upgrade_version = 0x11111111;
	std::string fw_pack_root;
	{
		std::stringstream stream;
		stream << "Nymi-FW-" << std::hex << upgrade_version;
		fw_pack_root = stream.str();
	}
	std::string ble_image_path = fw_pack_root + "/" + "nordic_image.bin";
	std::string mcu_image_path = fw_pack_root + "/" + "atmel_image.bin";
	std::string ble_hash_path  = fw_pack_root + "/" + "nordic_hash";
	std::string mcu_hash_path  = fw_pack_root + "/" + "atmel_hash";

	// load images
	std::cout << "Opening " << ble_image_path.data() << " for ble_image\n";
	std::ifstream ble_image_file(ble_image_path.data(), std::ios::binary);
	if(ble_image_file.fail()) {
		std::cerr << "Couldn't open file " << ble_image_file << "\n";
	} else {
		std::cerr << "Successfully opened ble_image_file!\n";
	}
}