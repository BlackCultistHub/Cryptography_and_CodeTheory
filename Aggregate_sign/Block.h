#pragma once
#include <vector>

namespace BlockChain {

	typedef struct block
	{
		block(std::vector<unsigned long long int>& transactions_, std::vector<unsigned long long int> key_ids_, unsigned long long sign_, unsigned long long int previous_block_id_, unsigned long long int block_id_);
		unsigned long long int block_id;
		unsigned long long int previous_block_id;
		std::vector<unsigned long long int> transactions;
		std::vector<unsigned long long int> key_ids;
		unsigned long long int sign;
	} block;

}