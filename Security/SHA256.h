#pragma once

// Constants for setting the length of arrays representing bit sequences
const int CHAR_BITS  = 8;
const int MAX_MESSAGE_LENGTH = CHAR_BITS * 2000;
const int CHUNK_SIZE = 512;
const int MESSAGE_SCHEDULE_ARRAY_BITS = 2048;
const int MSA_WORD_BITS = 32;
const int HASH_LENGTH = 64;

// Values for hash variables h0 to h7: first 32 bits of the fractional parts of the square roots of the first 8 primes
const unsigned int INITIAL_HASH_VALUES[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

// Rounding constants: 32 bits of the fractional parts of the cube roots of the first 64 primes
const unsigned int ROUNDING_CONSTANTS[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

class SHA256 {
private:
    static char hash[];
    static char *addArr(const char arr1[], const char arr2[], int deleteFlag);
    static char* andArr(const char arr1[], const char arr2[], int deleteFlag);
    static char *notArr(const char arr[]);
    static char* xorArr(const char arr1[], const char arr2[]);
    static char* rightShift(const char bits[], int start, int times);
    static char* rightRotate(const char bits[], int start, int times);
    static char* intToBinaryChar(unsigned int value);
    static char *extractWord(const char messageSchedule[], int ind);
    static char* copyCharArr(const char arr1[], int length);
    static void moveArr(char arr1[], const char arr2[], int length);
    static void fillMessageBlock(const char text[], char messageBlock[], int &length);
    static void hashVarsToChar(char *h[8]);
    static void fillMessageScheduleArray2(
            const char text[], const char *messageBlock, int messageBlockLength, char messageSchedule[MESSAGE_SCHEDULE_ARRAY_BITS],
            char* &h0, char* &h1, char* &h2, char* &h3, char* &h4, char* &h5, char* &h6, char* &h7
    );
public:
    const static char* getHash();
    static char* calculate(const char text[]);
    static bool compare(const char password[], const char hashedPassword[]);
};

static int pow2(int a);