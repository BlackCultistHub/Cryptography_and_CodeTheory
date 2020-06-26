#include <iostream>
#include <cmath>
#include <vector>

#include <crypto_math.h>

//#define EXTENDED_OUT

uint64_t binStringToInt(std::string&);
bool getBit(unsigned char code, int pointer);

unsigned char multGalua(unsigned char a, unsigned char b, unsigned binDegree = 4);
std::vector<unsigned char> divGalua(std::vector<unsigned char> msg, std::vector<unsigned char> gx);

std::vector<unsigned char> makeRSCRC(std::vector<unsigned char>& msg, std::vector<unsigned char> gx);
bool checkRSCRC(std::vector<unsigned char> msg, std::vector<unsigned char> gx);


int main()
{
    using std::cout;
    using std::endl;
    using std::cin;

    int inp;
    std::vector<unsigned char> msg;

    cout << "Enter input vector's numbers for GF(16) one by one. -1 to end." << endl;
    while (msg.size() < 7)
    {
        cin >> inp;
        if (inp == -1)
            break;
        if (inp < -1 || inp > 15)
        {
            cout << "Invalid number! Please try again." << endl;
            continue;
        }
        msg.push_back(inp);
    }
    //g(x) = 0x0 + 0x1 + 0x2 + 12x3 + 4x4 + 9x5 + 3x6 + 3x7 + 1x8
    std::vector<unsigned char> gx;
    gx.push_back(0);
    gx.push_back(0);
    gx.push_back(0);
    gx.push_back(12);
    gx.push_back(4);
    gx.push_back(9);
    gx.push_back(3);
    gx.push_back(3);
    gx.push_back(1);
    cout << "Standard g(x) for GF(16) for RS code is ";
    for (int i = 0; i < gx.size(); i++)
    {
        cout << (unsigned)gx[i];
    }
    cout << " (";
    for (int i = 0; i < gx.size(); i++)
    {
        cout << (unsigned)gx[i] << "x^(" << i  << ")" << (i == gx.size() - 1 ? "" : "+");
    }
    cout << ")" << endl;

    cout << "Making CRC..." << endl;
    std::vector<unsigned char> CRCMsg = makeRSCRC(msg, gx);
    cout << "Message with CRC is ";
    for (int i = 0; i < CRCMsg.size(); i++)
        cout << (unsigned)CRCMsg[i];
    cout << " (";
    for (int i = 0; i < CRCMsg.size(); i++)
        cout << (unsigned)CRCMsg[i] << "x^(" << i << ")" << (i == CRCMsg.size() - 1 ? "" : "+");
    cout << ")" << endl;
    
    cout << "Checking CRC validation..." << endl;
    cout << "CRC " << ((checkRSCRC(CRCMsg, gx)==true)? std::string("Valid") : std::string("Invalid")) << endl;
}

std::vector<unsigned char> makeRSCRC(std::vector<unsigned char>& msg, std::vector<unsigned char> gx)
{
    std::vector<unsigned char> shiftedMsg;

    //shift msg by x^8
    for (int i = 0; i < 8; i++)
        shiftedMsg.push_back(0);
    //copy msg
    for (int i = msg.size() - 1; i != -1; i--)
        shiftedMsg.push_back(msg[i]);

    //div
    std::vector<unsigned char> res = divGalua(shiftedMsg, gx);

    //saving crc
    for (int i = 0; i < 8; i++)
    {
        shiftedMsg[i] = res[i];
    }

    return shiftedMsg;
}

bool checkRSCRC(std::vector<unsigned char> msg, std::vector<unsigned char> gx)
{
    //div
    std::vector<unsigned char> res = divGalua(msg, gx);

    //checking
    for (int i = 0; i < res.size(); i++)
    {
        if (res[i] != 0)
            return false;
    }
    return true;

}

unsigned char multGalua(unsigned char a, unsigned char b, unsigned binDegree)
{
    unsigned int result = 0;
    for (int i = 0; i < binDegree; i++)
    {
        if (getBit(b, i))
        {
            result ^= a << i;
        }
    }
    return result % 16;
}

std::vector<unsigned char> divGalua(std::vector<unsigned char> msg, std::vector<unsigned char> gx)
{
    //find non-zero elem
    auto findNZE = [](std::vector<unsigned char> shiftedMsg)
    {
        //int nZelem = -1;
        for (int i = shiftedMsg.size() - 1; i != -1; i--)
        {
            if ((shiftedMsg[i] & 15) != 0)
            {
                // nZelem = i;
                return i;
            }
        }
        return -1;
    };
    std::vector<unsigned char> vichetaemoe;

    int nZelem = findNZE(msg);

    //making vichetaemoe
    for (int i = 0; i < gx.size(); i++)
    {
        vichetaemoe.push_back(multGalua(gx[i], msg[nZelem]));
    }

    int n = nZelem - 8;

    //diving
    while (n >= 0)
    {
        n = nZelem - 8;
        if (n == -1)
            break;
        for (int i = 0; i < 9; i++)
        {
            msg[i + n] ^= vichetaemoe[i];
        }
        nZelem = findNZE(msg);
        if (nZelem == -1)
            break;
        //recalc
        vichetaemoe.clear();
        for (int i = 0; i < gx.size(); i++)
        {
            vichetaemoe.push_back(multGalua(gx[i], msg[nZelem]));
        }
    }
    return msg;
}

bool getBit(unsigned char code, int pointer) //pointer [0 - 7]
{
    unsigned char pointerBit = 0, temp = 0;
    pointerBit = pow(2, pointer);
    temp = code ^ pointerBit;
    if (temp < code)
        return true;
    else
        return false;
}

