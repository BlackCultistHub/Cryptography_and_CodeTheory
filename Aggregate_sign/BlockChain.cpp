#include "BlockChain.h"

namespace BlockChain {

	BlockChain::BlockChain():
		sign_setting(0)
	{}

	BlockChain::BlockChain(std::vector<RSA::RSA_secret_keypair>& secret_keys_, std::vector<RSA::RSA_open_keypair>& public_keys_, int setting) :
		sign_setting(setting)
	{
		if (secret_keys_.size() != public_keys_.size())
			throw "Error! Sizes of secret and public key's vectors are not equal!";
		for (int pair = 0; pair < secret_keys_.size(); pair++)
		{
			keys.push_back(dataBaseKey(pair, secret_keys_[pair], public_keys_[pair]));
		}
	}

	void BlockChain::init(std::vector<RSA::RSA_secret_keypair>& secret_keys_, std::vector<RSA::RSA_open_keypair>& public_keys_, int setting)
	{
		sign_setting = setting;
		if (secret_keys_.size() != public_keys_.size())
			throw "Error! Sizes of secret and public key's vectors are not equal!";
		for (int pair = 0; pair < secret_keys_.size(); pair++)
		{
			keys.push_back(dataBaseKey(pair, secret_keys_[pair], public_keys_[pair]));
		}
	}

	bool BlockChain::addBlock(std::vector<long long int>& transactions_)
	{
		long long prevId = NULL;
		if (chain.size() != 0)
			prevId = chain.back().block_id;

		//hashing for sign
		std::vector<long long int> hashes;
		for (int i = 0; i < transactions_.size(); i++)
		{
			hashes.push_back(cryptoMath::superDuperHashFunction(transactions_[i]));
		}
		//generating sign
		std::vector<RSA::RSA_secret_keypair> SKs;
		getKeys(SKs);
		long long sign = ACSign::sign(SKs, hashes, sign_setting);
		chain.push_back(block(transactions_, sign, prevId, takeId()));
		return true;
	}

	bool BlockChain::checkBlock(int blockId)
	{
		std::vector<long long int> hashes;
		std::vector<RSA::RSA_open_keypair> PKs;
		getKeys(PKs);
		for (auto it = chain.begin(); it < chain.end(); it++)
		{
			if (it->block_id == blockId)
			{
				for (int i = 0; i < it->transactions.size(); i++)
					hashes.push_back(cryptoMath::superDuperHashFunction(it->transactions[i]));
				return ACSign::checkSign(PKs, hashes, it->sign);
			}
		}
	}

	int BlockChain::chechChain(bool& valid)
	{
		for (int i = 0; i < chain.size(); i++)
		{
			if (!checkBlock(chain[i].block_id))
			{
				valid = false;
				return chain[i].block_id;
			}
		}
		valid = true;
	}

	bool BlockChain::chechChain()
	{
		for (int i = 0; i < chain.size(); i++)
		{
			if (!checkBlock(chain[i].block_id))
				return false;
		}
		return true;
	}

	std::vector<long long int> BlockChain::scanChain()
	{
		std::vector<long long int> Ids;
		for (int i = 0; i < chain.size(); i++)
		{
			Ids.push_back(chain[i].block_id);
		}
		return Ids;
	}

	void BlockChain::getBlockInfo(long long int id, long long int& previous_block_id, std::vector< long long int>& transactions, long long int& sign)
	{
		for (int i = 0; i < chain.size(); i++)
		{
			if (id == chain[i].block_id)
			{
				previous_block_id = chain[i].previous_block_id;
				sign = chain[i].sign;
				for (int j = 0; j < chain[i].transactions.size(); j++)
					transactions.push_back(chain[i].transactions[j]);
			}
		}
	}

	long long BlockChain::takeId()
	{
		int randId = 0;
		bool unique = false;
		while (!unique)
		{
			randId = rand();
			unique = true;
			for (auto it = chain.begin(); it != chain.end(); it++)
			{
				if (it->block_id == randId)
				{
					unique = false;
					break;
				}
			}
		}
		return randId;
	}

	void BlockChain::getKeys(std::vector<RSA::RSA_secret_keypair>& secret_keys)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			secret_keys.push_back(keys[i].secret_key);
		}
	}

	void BlockChain::getKeys(std::vector<RSA::RSA_open_keypair>& public_keys)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			public_keys.push_back(keys[i].public_key);
		}
	}

}