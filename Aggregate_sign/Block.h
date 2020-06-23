#pragma once
#include <vector>

namespace BlockChain {

	typedef struct block
	{
		block(std::vector<long long int>& transactions_, long long sign_, long long int previous_block_id_, long long int block_id_);
		long long int block_id;
		long long int previous_block_id;
		std::vector< long long int> transactions;
		long long int sign;
	} block;

}