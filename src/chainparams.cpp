// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0x4a;
        vAlertPubKey = ParseHex("04e22531e96c9056be6b659c91a15648ebeb5d5176987abdc56ab452f7c2f81f85d131a669df3be161393f454852a2d08c6314bba5ca3cbe5616262da3d4a6efac");
        nDefaultPort = 44412;
        nRPCPort = 44526;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Cryptocurrency Markets Bleeding – Double Digits Losses Across the Board | Mark | December 25th, 2018";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = 1 * COIN;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1545948000, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1545948000; // Thur, December 27, 2018 10:00:00 PM
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 304072;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 18e4d94f5a8d36ce12e7081df5c406e1baef99be022173531ae5e04e3de60aed
        block.nTime = 1545948000
        block.nNonce = 304072
        block.GetHash = 0000e2807314cfafdb5a66f55b87c027a3fd1a5818590183cc76813b6c6ddbe8

        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000e2807314cfafdb5a66f55b87c027a3fd1a5818590183cc76813b6c6ddbe8"));
        assert(genesis.hashMerkleRoot == uint256("0x18e4d94f5a8d36ce12e7081df5c406e1baef99be022173531ae5e04e3de60aed"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,107);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,109);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,87);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        //vSeeds.push_back(CDNSSeedData("node1",  ""));
        //vSeeds.push_back(CDNSSeedData("node2",  ""));
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 9;
        strMNenginePoolDummyAddress = "iGrwXgFQbhiSBsxVSSCeQmty2qzCt4uS7Q"; // TODO: change with public key of Katz Wallet
        nEndPoWBlock = 0x7fffffff;
        nStartPoSBlock = 5000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2b;
        pchMessageStart[1] = 0x3b;
        pchMessageStart[2] = 0x4b;
        pchMessageStart[3] = 0xc5;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 14);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);
        vAlertPubKey = ParseHex("02e22531e96c9016789b659c91a94fbfebeb5d5257f1568974589abab1c2f81f85d131a669df3be611393f454852a2d08c6314bba5ca3cbe5616262db3d4a6efac");
        nDefaultPort = 44413;
        nRPCPort = 44527;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1545948000+30;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 41863 ;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 18e4d94f5a8d36ce12e7081df5c406e1baef99be022173531ae5e04e3de60aed
        block.nTime = 1545948030
        block.nNonce = 41863
        block.GetHash = 00005d99bd1c6459eec9fd0a11050f1727aee36295cf6f1befc8a987e4a5afa6

        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00005d99bd1c6459eec9fd0a11050f1727aee36295cf6f1befc8a987e4a5afa6"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,27);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,142);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,143);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xc2;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0x5e;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1545948000+90;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 44414;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 18e4d94f5a8d36ce12e7081df5c406e1baef99be022173531ae5e04e3de60aed
        block.nTime = 1545948090
        block.nNonce = 8
        block.GetHash = 27843e800fb481b4382fb156aca8c472624ec2072cfdb461f116726176a52ce2

        */

        assert(hashGenesisBlock == uint256("0x27843e800fb481b4382fb156aca8c472624ec2072cfdb461f116726176a52ce2"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
