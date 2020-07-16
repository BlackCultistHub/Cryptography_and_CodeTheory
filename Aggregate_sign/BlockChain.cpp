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

	bool BlockChain::addBlock(std::vector<unsigned long long int>& transactions_)
	{
		unsigned long long prevId = NULL;
		if (chain.size() != 0)
			prevId = chain.back().block_id;

		//hashing for sign
		std::vector<unsigned long long int> hashes;
		for (int i = 0; i < transactions_.size(); i++)
		{
			#ifdef  USE_SUPER_HASH
				hashes.push_back(cryptoMath::superDuperHashFunction(transactions_[i]));
			#else
				hashes.push_back(transactions_[i]);
			#endif
		}
		//generating sign
		std::vector<RSA::RSA_secret_keypair> SKs;
		std::vector<unsigned long long int> ids;
		getKeys(SKs, ids, transactions_.size());		
		unsigned long long sign = ACSign::sign(SKs, hashes, sign_setting);

		chain.push_back(block(transactions_, ids, sign, prevId, takeId()));
		return true;
	}

	bool BlockChain::checkBlock(int blockId)
	{
		std::vector<unsigned long long int> hashes;
		std::vector<RSA::RSA_open_keypair> PKs;
		for (auto it = chain.begin(); it < chain.end(); it++)
		{
			if (it->block_id == blockId)
			{
				std::vector<unsigned long long int> ids;
				for (int i = 0; i < it->key_ids.size(); i++)
				{
					ids.push_back(it->key_ids[i]);
				}
				getKeys(PKs, ids);
				for (int i = 0; i < it->transactions.size(); i++)
				{
					#ifdef USE_SUPER_HASH
						hashes.push_back(cryptoMath::superDuperHashFunction(it->transactions[i]));
					#else
						hashes.push_back(it->transactions[i]);
					#endif
				}
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

	std::vector<unsigned long long int> BlockChain::scanChain()
	{
		std::vector<unsigned long long int> Ids;
		for (int i = 0; i < chain.size(); i++)
		{
			Ids.push_back(chain[i].block_id);
		}
		return Ids;
	}

	void BlockChain::getBlockInfo(unsigned long long int id, unsigned long long int& previous_block_id, std::vector<unsigned long long int>& transactions, std::vector<unsigned long long int>& keyIds, unsigned long long int& sign)
	{
		for (int i = 0; i < chain.size(); i++)
		{
			if (id == chain[i].block_id)
			{
				previous_block_id = chain[i].previous_block_id;
				sign = chain[i].sign;
				for (int j = 0; j < chain[i].transactions.size(); j++)
					transactions.push_back(chain[i].transactions[j]);
				for (int j = 0; j < chain[i].key_ids.size(); j++)
					keyIds.push_back(chain[i].key_ids[j]);
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

	void BlockChain::getKeys(std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<unsigned long long int>& ids, unsigned long long int transactions_amount)
	{
		std::vector<dataBaseKey> usedKeys;
		unsigned long long keysAmount = transactions_amount + 2 > keys.size() ? transactions_amount : transactions_amount + 2;
		for (int i = 0; i < keysAmount; i++)
		{
			auto UniqueKey = [usedKeys](dataBaseKey toCheck)
			{
				for (int i = 0; i < usedKeys.size(); i++)
				{
					if (usedKeys[i].id == toCheck.id)
						return false;
				}
				return true;
			};

			dataBaseKey keyToGo = keys[rand() % keys.size()];
			while (!UniqueKey(keyToGo))
				keyToGo = keys[rand() % keys.size()];
			usedKeys.push_back(keyToGo);
			secret_keys.push_back(keyToGo.secret_key);
			//getting key's ids
			ids.push_back(keyToGo.id);
		}
	}

	void BlockChain::getKeys(std::vector<RSA::RSA_open_keypair>& public_keys, std::vector<unsigned long long int> ids)
	{
		for (int i = 0; i < ids.size(); i++)
		{
			for (int j = 0; j < keys.size(); j++)
			{
				if (keys[j].id == ids[i])
					public_keys.push_back(keys[j].public_key);
			}
		}		
	}

}