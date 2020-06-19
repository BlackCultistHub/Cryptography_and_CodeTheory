#include "aggr_comp_sign.h"

namespace ACSign {

	void sortKeysFromLowToHigh(std::vector<RSA::RSA_secret_keypair>& keys)
	{
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i < keys.size() - 1; i++)
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
			for (int i = 0; i < keys.size() - 1; i++)
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
			for (int i = 0; i < keys.size() - 1; i++)
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

	long long sign(std::vector<RSA::RSA_secret_keypair> keys, std::vector<long long int> hashes, int setting=0) // setting = 2 for disable; 1 for let keys>hashes
	{
		if ((hashes.size() > keys.size()) && setting <= 1)
			throw std::exception("Error creating ACSign. Recieved too many hashes.");
		if ((keys.size() > hashes.size()) && setting == 0)
			throw std::exception("Error creating ACSign. Recieved too many keys.");
		if (keys.size() > hashes.size())
			for (int hash = 0 + (keys.size() - (keys.size() - hashes.size())); hash < hashes.size(); hash++) //make not used hashes as 1
				hashes[hash] = 1;
		std::vector<long long int> signs;
		sortKeysFromLowToHigh(keys);
		for (int keypair = 0; keypair < keys.size(); keypair++)
		{
			//Sm = (Sm-1 * Hm)^dm mod Nm
			long long multiplication = keypair == 0 ? 1 : signs.back() * hashes[keypair];
			long long signM = cryptoMath::modexp(multiplication, keys[keypair].d, keys[keypair].N);
			signs.push_back(signM);
		}
		return signs.back();
	}

	bool checkSign(std::vector<RSA::RSA_open_keypair> keys, std::vector<long long int> hashes, long long sign)
	{
		std::vector<long long int> signs;
		//sort backwards
		sortKeysFromHighToLow(keys);
		for (int keypair = 0; keypair < keys.size()-1; keypair++) // -1?????
		{
			//Sm-1 = (Sm^em) * Hm(-1) mod Nm = (Sm^em mod N * Hm(-1) mod Nm) mod Nm = (mod1 * mod2) mod Nm
			long long mod1 = cryptoMath::modexp(keypair == 0 ? sign : signs.back(), keys[keypair].e, keys[keypair].N);
			long long mod2 = cryptoMath::getMultiplBack(hashes[keys.size() - keypair -1], keys[keypair].N) % keys[keypair].N; // -1?????
			long long signMinusOne = (mod1 * mod2) % keys[keypair].N;
		}
		long long HashXBase = hashes[0] % keys.back().N;
		//Hx = S1^e1 mod N1
		long long HashX = cryptoMath::modexp(signs.back(), keys.back().e, keys.back().N);
		if (HashXBase == HashX)
			return true;
		else
			return false;
	}
}