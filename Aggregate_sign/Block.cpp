#include "Block.h"

namespace BlockChain {

	block::block(std::vector<long long int>& transactions_, long long sign_, long long int previous_block_id_, long long int block_id_) :
		sign(sign_),
		block_id(block_id_),
		previous_block_id(previous_block_id_)
	{
		//saving transactions
		for (int i = 0; i < transactions_.size(); i++)
		{
			transactions.push_back(transactions_[i]);
		}
	}
}