#include "aggr_comp_sign.h"

namespace ACSign {

	void sortKeysFromLowToHigh(std::vector<RSA::RSA_secret_keypair>& keys)
	{
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (long i = 0; i < keys.size() - 1; i++)
			{
				if (keys[i].N > keys[i + 1].N)
				{
					RSA::RSA_secret_keypair temp = keys[i];
					keys[i] = keys[i + 1];
					keys[i + 1] = temp;
					sorted = false;
				}
			}
		}
	}

	void sortKeysFromHighToLow(std::vector<RSA::RSA_secret_keypair>& keys)
	{
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (size_t i = 0; i < keys.size() - 1; i++)
			{
				if (keys[i].N < keys[i + 1].N)
				{
					RSA::RSA_secret_keypair temp = keys[i];
					keys[i] = keys[i + 1];
					keys[i + 1] = temp;
					sorted = false;
				}
			}
		}
	}

	void sortKeysFromLowToHigh(std::vector<RSA::RSA_open_keypair>& keys)
	{
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (size_t i = 0; i < keys.size() - 1; i++)
			{
				if (keys[i].N > keys[i + 1].N)
				{
					RSA::RSA_open_keypair temp = keys[i];
					keys[i] = keys[i + 1];
					keys[i + 1] = temp;
					sorted = false;
				}
			}
		}
	}

	void sortKeysFromHighToLow(std::vector<RSA::RSA_open_keypair>& keys)
	{
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i < keys.size() - 1; i++)
			{
				if (keys[i].N < keys[i + 1].N)
				{
					RSA::RSA_open_keypair temp = keys[i];
					keys[i] = keys[i + 1];
					keys[i + 1] = temp;
					sorted = false;
				}
			}
		}
	}

	void fillHashes(std::vector<unsigned long long int>& hashes, int target_size, int setting = 0) //0 for copies; 1 for one's
	{
		if (target_size > hashes.size())
		{
			if (setting == 0)
			{
				int initial_size = hashes.size();
				while (target_size > hashes.size())  //dublicate docs if need
					hashes.push_back(hashes[hashes.size() - initial_size]);
			}
			else if (setting == 1)
			{
				for (int hash = 0 + (target_size - (target_size - hashes.size())); hash < target_size; hash++) //make not used hashes as 1
					hashes.push_back(1);
			}
		}
	}

	unsigned long long sign(std::vector<RSA::RSA_secret_keypair> keys, std::vector<unsigned long long int> hashes, int setting) // setting = 2 for disable; 1 for let keys>hashes
	{
		if ((hashes.size() > keys.size()) && setting <= 1)
			throw std::exception("Error creating ACSign. Recieved too many hashes.");
		if ((keys.size() > hashes.size()) && setting == 0)
			throw std::exception("Error creating ACSign. Recieved too many keys.");
		if (keys.size() > hashes.size())
			fillHashes(hashes, keys.size());
		std::vector<unsigned long long int> signs;
		sortKeysFromLowToHigh(keys);
		for (int keypair = 0; keypair < keys.size(); keypair++)
		{
			//Sm = (Sm-1 * Hm)^dm mod Nm
			unsigned long long multiplication = keypair == 0 ? hashes[keypair] : signs.back() * hashes[keypair];
			unsigned long long signM = cryptoMath::modexp(multiplication, keys[keypair].d, keys[keypair].N);
			signs.push_back(signM);
		}
		return signs.back();
	}

	bool checkSign(std::vector<RSA::RSA_open_keypair> keys, std::vector<unsigned long long int> hashes, unsigned long long sign)
	{
		//fill hashes
		if (keys.size() > hashes.size())
			fillHashes(hashes, keys.size());
		//sort backwards
		sortKeysFromHighToLow(keys);
		unsigned long long last_sign = sign;
		for (int keypair = 0; keypair < keys.size()-1; keypair++) // -1?????
		{
			//Sm-1 = (Sm^em) * Hm(-1) mod Nm = (Sm^em mod N * Hm(-1) mod Nm) mod Nm = (mod1 * mod2) mod Nm
			unsigned long long mod1 = cryptoMath::modexp(keypair == 0 ? sign : last_sign, keys[keypair].e, keys[keypair].N);
			unsigned long long mod2 = cryptoMath::getMultiplBack(hashes[keys.size() - keypair - 1], keys[keypair].N); // -1?????
			last_sign = (mod1 * mod2) % keys[keypair].N;
		}
		unsigned long long HashXBase = hashes[0] % keys.back().N;
		//Hx = S1^e1 mod N1
		unsigned long long HashX = cryptoMath::modexp(last_sign, keys.back().e, keys.back().N);
		if (HashXBase == HashX)
			return true;
		else
			return false;
	}
}