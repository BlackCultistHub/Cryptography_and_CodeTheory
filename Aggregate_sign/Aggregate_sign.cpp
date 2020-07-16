//input streams
#include <conio.h>
#include <iostream>

//logic
#include <aggr_comp_sign.h>
#include "BlockChain.h"

//winapi
#include <Windows.h>

// 100 337 257

#define GEN_LOWEST 100
#define GEN_MAX 
#define GEN_MODULE 337
#define GEN_TRANSACTION_MODULE 257
#define GEN_CHECK_MSG 257

typedef std::pair<unsigned long long int, unsigned long long int> secret_pair;

namespace graphics {

	void logo();
	void keyShow(std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<RSA::RSA_open_keypair>& public_keys);
	void blockChainShow(BlockChain::BlockChain chain);

	void chainCheck(BlockChain::BlockChain chain);
	void blockCheck(BlockChain::BlockChain chain);
}

namespace logic {

	void autoGen(int amount, std::vector<RSA::RSA_secret_keypair>& secret_keys,	std::vector<RSA::RSA_open_keypair>& public_keys);
	void inputKeys(std::vector<secret_pair> secret_input, std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<RSA::RSA_open_keypair>& public_keys);

	void bcAutoGen(int amount, std::vector<unsigned long long int>& docs_input, BlockChain::BlockChain& chain);
	void bcInput(std::vector<unsigned long long int>& docs_input, BlockChain::BlockChain& chain);
}


int main()
{
	try
	{
		using std::cout;
		using std::endl;
		using std::cin;

		//variables
		int keysAmount = 0;
		unsigned long long inp1 = 0, inp2 = 0;
		int i = 0;
		bool input = true;
		//data inputs
		std::vector<secret_pair> secret_input;
		std::vector<unsigned long long int> docs_input;
		//keys
		std::vector<RSA::RSA_secret_keypair> secret_keys;
		std::vector<RSA::RSA_open_keypair> public_keys;
		//chain
		BlockChain::BlockChain chain;
		//BlockChain::BlockChain chain(secret_keys, public_keys, 1);


		graphics::logo();
	main:
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*      1. Generate secret keys              *" << endl;
		cout << "*                automatically              *" << endl;
		cout << "*      2. Input keys manually               *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ main page ]*******************************" << endl;
		cout << "=============================================" << endl;
	mainCH:
		switch (_getch())
		{
		case '1':
			goto autoKey;
			break;
		case '2':
			goto inputKey;
			break;
		default:
			goto mainCH;
			break;
		}
	autoKey:
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*        Enter amount of keys.              *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ keys autogen 1 ]**************************" << endl;
		cout << "Input: ";
		cin >> keysAmount;
		if (keysAmount == 0)
		{
			system("cls");
			cout << "*********[ BlockChain via AC Sign ]**********" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*        Keys cannot be created with        *" << endl;
			cout << "*              no secret pairs!             *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*[ keys autogen 1 ]***************************" << endl;
			cout << "Press any key to return...";
			_getch();
			system("cls");
			goto main;
		}
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*         Please wait...                    *" << endl;
		cout << "*         Generating keys...                *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ keys autogen 2 ]**************************" << endl;
		cout << "=============================================" << endl;
		Sleep(1000);
		logic::autoGen(keysAmount, secret_keys, public_keys);
		system("cls");
		goto bcInit;
	inputKey:
		system("cls");
		i = 1;
		input = true;
		while (input)
		{
			for (int j = 0; j < 2; j++)
			{
				if (j == 0)
				{
					cout << "*********[ BlockChain via AC Sign ]**********" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*      Please input pair #" << i << " 'P'             *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*      Press 0 to exit                      *" << endl;
					cout << "*                                           *" << endl;
					cout << "*[ keys manual 1 ]***************************" << endl;
					cout << "Input: ";
					cin >> inp1;
					system("cls");
					if (inp1 == 0)
					{
						input = false;
						break;
					}
				}
				else if (j == 1)
				{
					cout << "*********[ BlockChain via AC Sign ]**********" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*      Please input pair #" << i << " 'Q'             *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*                                           *" << endl;
					cout << "*      Press 0 to exit                      *" << endl;
					cout << "*                                           *" << endl;
					cout << "*[ keys manual 2 ]***************************" << endl;
					cout << "Input: ";
					cin >> inp2;
					system("cls");
					if (inp2 == 0)
					{
						input = false;
						break;
					}
				}
			}
			if (input)
				secret_input.push_back(std::make_pair(inp1, inp2));
			i++;
		}
		if (secret_input.size() == 0)
		{
			cout << "*********[ BlockChain via AC Sign ]**********" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*        Keys cannot be created with        *" << endl;
			cout << "*              no secret pairs!             *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*[ keys manual 3 ]***************************" << endl;
			cout << "Press any key to return...";
			_getch();
			system("cls");
			goto main;
		}
		logic::inputKeys(secret_input, secret_keys, public_keys);
		goto bcInit;
	bcInit:
		chain.init(secret_keys, public_keys, 1);
	blockchain:
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*       Keys successfully generated.        *" << endl;
		cout << "*       BlockChain initialized.             *" << endl;
		cout << "*                                           *" << endl;
		cout << "*      1. Show keys (may be a long table)   *" << endl;
		cout << "*      2. Show blocks                       *" << endl;
		cout << "*      3. Generate block                    *" << endl;
		cout << "*      4. Input block data                  *" << endl;
		cout << "*      5. Check sign                        *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ blockchain main ]*************************" << endl;
		cout << "=============================================" << endl;
	blockchainCH:
		switch (_getch())
		{
		case '1':
			goto keyShow;
			break;
		case '2':
			goto blockShow;
			break;
		case '3':
			goto bcAutoGen;
			break;
		case '4':
			goto bcInput;
			break;
		case '5':
			goto bcCheck;
			break;
		default:
			goto blockchainCH;
			break;
		}
	keyShow:
		system("cls");
		graphics::keyShow(secret_keys, public_keys);
		cout << "Press any key to return...";
		_getch();
		system("cls");
		goto blockchain;
	blockShow:
		system("cls");
		graphics::blockChainShow(chain);
		cout << "Press any key to return...";
		_getch();
		system("cls");
		goto blockchain;
	bcAutoGen:
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*        Enter amount of transactions       *" << endl;
		cout << "*              for new block.               *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*      Press 0 to exit                      *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ block auto 1 ]****************************" << endl;
		cout << "Input: ";
		cin >> keysAmount;
		if (keysAmount == 0)
			goto blockchain;
		system("cls");
		logic::bcAutoGen(keysAmount, docs_input, chain);
		goto blockchain;
	bcInput:
		i = 1;
		input = true;
		system("cls");
		while (input)
		{
			cout << "*********[ BlockChain via AC Sign ]**********" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*      Please input transaction #" << i << "          *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*      Press 0 to exit                      *" << endl;
			cout << "*                                           *" << endl;
			cout << "*[ block manual 1 ]**************************" << endl;
			cout << "Input: ";
			cin >> inp1;
			system("cls");
			if (inp1 == 0)
			{
				input = false;
				break;
			}
			if (input)
				docs_input.push_back(inp1);
			i++;
		}
		if (docs_input.size() == 0)
		{
			cout << "*********[ BlockChain via AC Sign ]**********" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*        Block cannot be created with       *" << endl;
			cout << "*              no transactions!             *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*[ block manual 2 ]**************************" << endl;
			cout << "Press any key to return...";
			_getch();
			goto blockchain;
		}
		logic::bcInput(docs_input, chain);
		goto blockchain;
	bcCheck:
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*           Sign check.                     *" << endl;
		cout << "*                                           *" << endl;
		cout << "*         1. Check chain                    *" << endl;
		cout << "*         2. Check block                    *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*      Press 0 to exit                      *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ check main ]******************************" << endl;
		cout << "=============================================" << endl;
		switch (_getch())
		{
		case '0':
			goto blockchain;
			break;
		case '1':
			goto bcChainCheck;
			break;
		case '2':
			goto bcBlockCheck;
			break;
		defaut:
			goto bcCheck;
			break;
		}
	bcChainCheck:
		system("cls");
		graphics::chainCheck(chain);
		_getch();
		goto bcCheck;
	bcBlockCheck:
		system("cls");
		graphics::blockCheck(chain);
		//_getch();
		goto bcCheck;
	}
	catch (const char* exception)
	{
		system("cls");
		std::cout << "\n=====[ EXCEPTION ]=====" << std::endl;
		std::cout << exception << std::endl;
		std::cout << "=======================" << std::endl;
		return -1;
	}

}


namespace graphics {
	void logo()
	{
		for (int i = 0; i < 5; i++, std::cout << "\n") {}
		std::cout << "\t\t*********[ BlockChain via AC Sign ]**********" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*      BlockChain via Aggregate Sign        *" << std::endl;
		std::cout << "\t\t*         by Rumata(Arkov I.A.)             *" << std::endl;
		std::cout << "\t\t*            BlackCultist(Makarsky A.A.)    *" << std::endl;
		std::cout << "\t\t*            Wolfgang(Zherebtsov I.A.)      *" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*                           SUAI group 3745 *" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*********[ Saint-Petersburg, 2020 ]**********" << std::endl;
		//alone ver
		/*std::cout << "\t\t*********[ BlockChain via AC Sign ]**********" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*      BlockChain via Aggregate Sign        *" << std::endl;
		std::cout << "\t\t*         by BlackCultist(Makarsky A.A.)    *" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*                           SUAI group 3745 *" << std::endl;
		std::cout << "\t\t*                                           *" << std::endl;
		std::cout << "\t\t*********[ Saint-Petersburg, 2020 ]**********" << std::endl;*/
		Sleep(4000);
		system("cls");
	}

	void keyShow(std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<RSA::RSA_open_keypair>& public_keys)
	{
		using std::cout;
		using std::endl;
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "|" << endl;
		for (int i = 0; i < secret_keys.size(); i++)
		{
			cout << "|       Key #"<< i <<": d="<< secret_keys[i].d <<", e="<< public_keys[i].e <<", N=" << public_keys[i].N << endl;
		}
		cout << "|" << endl;
		cout << "|       BAD KEYS: " << endl;
		std::vector<int> badKeysId;
		for (int i = 0; i < secret_keys.size(); i++)
		{
			long long testMsg = GEN_CHECK_MSG;
			long long E = RSA::encript(testMsg, public_keys[i].e, public_keys[i].N);
			long long D = RSA::decript(E, secret_keys[i].d, secret_keys[i].N);
			if (testMsg != D)
				badKeysId.push_back(i);
		}
		for (int i = 0; i < badKeysId.size(); i++)
			cout << "|    Key#" << badKeysId[i] << endl;
		cout << "|" << endl;
		cout << "*[ key show ]********************************" << endl;
		//cout << "Press any key to return...";
		//_getch();
	}

	void blockChainShow(BlockChain::BlockChain chain)
	{
		using std::cout;
		using std::endl;
		unsigned long long prevId = 0,
			   				sign = 0;
		std::vector<unsigned long long int> transactions;
		std::vector<unsigned long long int> keyIds;
		std::vector<unsigned long long int> blocks = chain.scanChain();
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "|" << endl;
		for (int i = 0; i < blocks.size(); i++)
		{
			chain.getBlockInfo(blocks[i], prevId, transactions, keyIds, sign);
			cout << "|    |=====[ Block #" << blocks[i] << ": ]=====" << endl;
			//cout << "|	  | Block #" << blocks[i] << ":" << endl;
			cout << "|    |   Previous block: " << prevId << endl;
			cout << "|    |   Sign: " << sign << endl;
			cout << "|    |   Transactions: " << endl;
			for (int j = 0; j < transactions.size(); j++)
			{
				cout << "|    |      |TR#" << j << ":" << transactions[j] << endl;
			}
			transactions.clear();
			cout << "|    |   Keys(id): " << endl;
			for (int j = 0; j < keyIds.size(); j++)
			{
				cout << "|    |      |KEY#" << j << ":" << keyIds[j] << endl;
			}
			transactions.clear();
			keyIds.clear();
		}
		cout << "|" << endl;
		cout << "*[ block show ]******************************" << endl;
		//cout << "Press any key to return...";
		//_getch();
	}

	void chainCheck(BlockChain::BlockChain chain)
	{
		using std::cout;
		using std::endl;
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*         Checking chain...                 *" << endl;
		cout << "*                                           *" << endl;
		if (chain.chechChain())
			cout << "*         Chain valid! OK                   *" << endl;
		else
			cout << "*         Chain not valid! BAD              *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ check chain ]*****************************" << endl;
		cout << "Press any key to return...";
	}

	void blockCheck(BlockChain::BlockChain chain)
	{
		using std::cout;
		using std::cin;
		using std::endl;
	list:
		unsigned long long inp;
		std::vector<unsigned long long int> blocks = chain.scanChain();
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*           Sign check by block.            *" << endl;
		cout << "*          Choose block to check.           *" << endl;
		cout << "*                                           *" << endl;
		cout << "*         Blocks list:                      *" << endl;
		for (int i = 0; i < blocks.size(); i++)
		{
			cout << "*      id " << blocks[i] << "-->>" << endl;
		}
		cout << "*                                           *" << endl;
		cout << "*      Press 0 to exit                      *" << endl;
		cout << "*                                           *" << endl;
		cout << "*[ check block ]*****************************" << endl;
		cout << "Input: ";
		cin >> inp;
		if (inp == 0)
			return;
		system("cls");
		cout << "*********[ BlockChain via AC Sign ]**********" << endl;
		cout << "*                                           *" << endl;
		cout << "*           Sign check by block.            *" << endl;
		cout << "*             Checking...                   *" << endl;
		cout << "*                                           *" << endl;
		if (chain.checkBlock(inp))
		{
			cout << "*            Block Valid. OK                *" << endl;
			cout << "*                                           *" << endl;
			cout << "*         1. Go to block list               *" << endl;
			cout << "*         2. Exit block check               *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*[ check block 2 ]***************************" << endl;
			cout << "=============================================" << endl;
		valid:
			switch (_getch())
			{
			case '1':
				goto list;
				break;
			case '2':
				return;
				break;
			default:
				goto valid;
				break;
			}
		}
		else
		{
			cout << "*            Block Invalid! BAD             *" << endl;
			cout << "*                                           *" << endl;
			cout << "*         1. Go to block list               *" << endl;
			cout << "*         2. Exit block check               *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*                                           *" << endl;
			cout << "*[ check block 2 ]***************************" << endl;
			cout << "=============================================" << endl;
		invalid:
			switch (_getch())
			{
			case '1':
				goto list;
				break;
			case '2':
				return;
				break;
			default:
				goto invalid;
				break;
			}
		}
	}
}

namespace logic {

	void autoGen(int amount, std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<RSA::RSA_open_keypair>& public_keys)
	{
		for (int keyToGen = 0; keyToGen < amount; keyToGen++)
		{
			auto uniqueKey = [secret_keys](unsigned long long backExp)
			{
				for (int i = 0; i < secret_keys.size(); i++)
				{
					if (secret_keys[i].d == backExp)
						return false;
				}
				return true;
			};
			auto checkValidKey = [](unsigned long long d, unsigned long long e, unsigned long long mod)
			{
				unsigned long long msg = GEN_CHECK_MSG;
				unsigned long long E = RSA::encript(msg, e, mod);
				unsigned long long D = RSA::decript(E, d, mod);
				if (msg != D)
					return false;
				return true;
			};
			
			unsigned long long exp;
			unsigned long long mod;
			unsigned long long backExp = 0;
			unsigned long long rnumbP = 0;
			do
			{
				while (rnumbP < GEN_LOWEST)
					rnumbP = rand() % GEN_MODULE;
				unsigned long long primeP = cryptoMath::GetNextPrime(rnumbP);
				unsigned long long rnumbQ = 0;
				while (rnumbQ < GEN_LOWEST)
					rnumbQ = rand() % GEN_MODULE;
				unsigned long long primeQ = cryptoMath::GetNextPrime(rnumbQ);

				RSA::keyGen(primeP, primeQ, exp, mod, backExp);
			} while (!(uniqueKey(backExp) && checkValidKey(backExp, exp, mod)));
			RSA::RSA_open_keypair openKey(exp, mod);
			RSA::RSA_secret_keypair secretKey(backExp, mod);

			public_keys.push_back(openKey);
			secret_keys.push_back(secretKey);
		}
	}
	void inputKeys(std::vector<secret_pair> secret_input, std::vector<RSA::RSA_secret_keypair>& secret_keys, std::vector<RSA::RSA_open_keypair>& public_keys)
	{
		//getting keys via RSA
		for (int i = 0; i < secret_input.size(); i++)
		{
			unsigned long long exp;
			unsigned long long mod;
			unsigned long long backExp;
			RSA::keyGen(secret_input[i].first, secret_input[i].second, exp, mod, backExp);
			RSA::RSA_open_keypair openKey(exp, mod);
			public_keys.push_back(openKey);
			RSA::RSA_secret_keypair secretKey(backExp, mod);
			secret_keys.push_back(secretKey);
		}
	}
	void bcAutoGen(int amount, std::vector<unsigned long long int>& docs_input, BlockChain::BlockChain& chain)
	{
		for (int i = 0; i < amount; i++)
		{
			unsigned long long r = rand() % GEN_TRANSACTION_MODULE;
			docs_input.push_back(r);
		}
		chain.addBlock(docs_input);
		docs_input.clear();
	}
	void bcInput(std::vector<unsigned long long int>& docs_input, BlockChain::BlockChain& chain)
	{
		chain.addBlock(docs_input);
		docs_input.clear();
	}


}