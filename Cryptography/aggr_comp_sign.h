#pragma once

#include <vector>
#include "crypto_math.h"
#include "rsa.h"

namespace ACSign {

	void sortKeysFromLowToHigh(std::vector<RSA::RSA_secret_keypair>& keys);
	void sortKeysFromHighToLow(std::vector<RSA::RSA_secret_keypair>& keys);
	void sortKeysFromLowToHigh(std::vector<RSA::RSA_open_keypair>& keys);
	void sortKeysFromHighToLow(std::vector<RSA::RSA_open_keypair>& keys);

	unsigned long long sign(std::vector<RSA::RSA_secret_keypair> keys, std::vector<unsigned long long int> hashes, int setting = 0); // setting = 2 for disable; 1 for let keys>hashes
	
	bool checkSign(std::vector<RSA::RSA_open_keypair> keys, std::vector<unsigned long long int> hashes, unsigned long long sign);

}