#pragma once

#include "Block.h"
#include <rsa.h>
#include <aggr_comp_sign.h>
#include <vector>

namespace BlockChain {

	typedef struct dataBaseKey
	{
		dataBaseKey(long long id_, RSA::RSA_secret_keypair secret_key_, RSA::RSA_open_keypair public_key_) :
			id(id_),
			secret_key(secret_key_),
			public_key(public_key_) {}
		long long id;
		RSA::RSA_secret_keypair secret_key;
		RSA::RSA_open_keypair public_key;
	} dataBaseKey;

	class BlockChain
	{
	public:
		BlockChain();
		BlockChain(std::vector<RSA::RSA_secret_keypair>& secret_keys_, std::vector<RSA::RSA_open_keypair>& public_keys_, int setting = 0);

		void init(std::vector<RSA::RSA_secret_keypair>& secret_keys_, std::vector<RSA::RSA_open_keypair>& public_keys_, int setting = 0);

		bool addBlock(std::vector<long long int>& transactions_);
		bool checkBlock(int blockId);

		int chechChain(bool& valid);
		bool chechChain();

		std::vector<long long int> scanChain();
		void getBlockInfo(long long int id, long long int& previous_block_id, std::vector< long long int>& transactions, std::vector< long long int>& keyIds, long long int& sign);
	private:
		long long takeId();
		void getKeys(std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<long long int>& ids, long long int transactions_amount);
		void getKeys(std::vector<RSA::RSA_open_keypair>& public_keys, std::vector<long long int> ids);
		int sign_setting;
		std::vector<block> chain;
		//database
		std::vector<dataBaseKey> keys;
	};

}