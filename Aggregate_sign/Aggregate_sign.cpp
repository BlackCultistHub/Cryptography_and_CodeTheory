#include <iostream>

#include <aggr_comp_sign.h>

typedef std::pair<long long int, long long int> secret_pair;
//typedef std::pair<RSA::RSA_open_keypair, RSA::RSA_secret_keypair> full_keypair;

int main()
{
    //input keys
    std::vector<secret_pair> secret_input;
    secret_input.push_back(std::make_pair(5, 7));
    secret_input.push_back(std::make_pair(17, 23));
    secret_input.push_back(std::make_pair(29, 37));
    //input docs
    std::vector<long long int> docs_input;
    docs_input.push_back(12345);

    //hashing docs
    std::vector<long long int> hashed_docs;
    for (int i = 0; i < docs_input.size(); i++)
        hashed_docs.push_back(cryptoMath::superDuperHashFunction(docs_input[i]));

    std::vector<RSA::RSA_secret_keypair> secret_keys;
    std::vector<RSA::RSA_open_keypair> public_keys;
    //getting keys via RSA
    for (int i = 0; i < secret_input.size(); i++)
    {
        long long exp;
        long long mod;
        long long backExp;
        RSA::keyGen(secret_input[i].first, secret_input[i].second, exp, mod, backExp);
        RSA::RSA_open_keypair openKey(exp, mod);
        public_keys.push_back(openKey);
        RSA::RSA_secret_keypair secretKey(backExp, mod);
        secret_keys.push_back(secretKey);
    }

    //signing hashed docs
    long long sign = ACSign::sign(secret_keys, hashed_docs, 1);

    //checking sign
    ACSign::checkSign(public_keys, hashed_docs, sign);
}