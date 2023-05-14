#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include "SHA256.h"
#include <cstring>


/*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Georgi Iliev
* @idnumber 8MI0600255
* @compiler gcc
*
* <Header file providing hashing using the SHA-256 algorithm>
*
*/

char SHA256::hash[HASH_LENGTH + 1];

// Function for calculating powers of the 2
static int pow2(int a) {
    return 1 << a;
}

// Function adding two arrays of length MSA_WORD_BITS and returning pointer to the result
char* SHA256::addArr(const char arr1[], const char arr2[], const int deleteFlag) {
    char* newBits = new char[MSA_WORD_BITS], leftover = '0';
    for(int i = MSA_WORD_BITS - 1; i >= 0; i--) {
        if(arr1[i] == '1') {
            if(arr2[i] == '1') {
                if(leftover == '1') {
                    newBits[i] = '1';
                    leftover = '1';
                }
                else {
                    newBits[i] = '0';
                    leftover = '1';
                }
            }
            else {
                if(leftover == '1') {
                    newBits[i] = '0';
                    leftover = '1';
                }
                else {
                    newBits[i] = '1';
                    leftover = '0';
                }
            }
        }
        else {
            if(arr2[i] == '1') {
                if(leftover == '1') {
                    newBits[i] = '0';
                    leftover = '1';
                }
                else {
                    newBits[i] = '1';
                    leftover = '0';
                }
            }
            else {
                if(leftover == '1') {
                    newBits[i] = '1';
                    leftover = '0';
                }
                else {
                    newBits[i] = '0';
                    leftover = '0';
                }
            }
        }
    }
    switch(deleteFlag) {
        case 1:
            delete[] arr1;
            break;
        case 2:
            delete[] arr2;
            break;
        case 3:
            delete[] arr1;
            delete[] arr2;
            break;
        default:
            break;
    }
    return newBits;
}

// Function returning bitwise and of two arrays with length MSA_WORD_BITS
char* SHA256::andArr(const char arr1[], const char arr2[], const int deleteFlag) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = 0; i < MSA_WORD_BITS; i++) {
        newBits[i] = arr1[i] == '1' && arr2[i] == '1' ? '1' : '0';
    }
    switch(deleteFlag) {
        case 1:
            delete[] arr1;
            break;
        case 2:
            delete[] arr2;
            break;
        case 3:
            delete[] arr1;
            delete[] arr2;
            break;
        default:
            break;
    }
    return newBits;
}

// Function returning bitwise not of an array with length MSA_WORD_BITS
char* SHA256::notArr(const char arr[]) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = 0; i < MSA_WORD_BITS; i++) {
        newBits[i] = arr[i] == '0' ? '1' : '0';
    }
    return newBits;
}

// Function returning bitwise exclusive or of an array with length MSA_WORD_BITS
char* SHA256::xorArr(const char arr1[], const char arr2[]) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = 0; i < MSA_WORD_BITS; i++) {
        if(arr1[i] == '0') {
            if(arr2[i] == '0') {
                newBits[i] = '0';
            }
            else {
                newBits[i] = '1';
            }
        }
        else {
            if(arr2[i] == '0') {
                newBits[i] = '1';
            }
            else {
                newBits[i] = '0';
            }
        }
    }
    delete[] arr1;
    delete[] arr2;
    return newBits;
}

// Function returning pointer to array of length MSA_WORD_BITS that is right shift n-times from start of the bits array
char* SHA256::rightShift(const char bits[], const int start, const int times) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = 0; i < times; i++) {
        newBits[i] = '0';
    }
    for(int i = times; i < MSA_WORD_BITS; i++) {
        newBits[i] = bits[start + i - times];
    }
    return newBits;
}

// Function returning pointer to array of length MSA_WORD_BITS that is right rotate n-times from start of the bits array
char* SHA256::rightRotate(const char bits[], const int start, const int times) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = 0, end = start + MSA_WORD_BITS; i < times; i++) {
        newBits[i] = bits[end - times + i];
    }
    for(int i = times; i < MSA_WORD_BITS; i++) {
        newBits[i] = bits[start + i - times];
    }
    return newBits;
}

// Function converting integer number to big-endian binary representation in char array with length of MSA_WORD_BITS
char* SHA256::intToBinaryChar(unsigned int value) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = MSA_WORD_BITS - 1; i >= 0; i--) {
        newBits[i] = (char) ((value % 2) + '0');
        value /= 2;
    }
    return newBits;
}

// Function extracting word by index from the message schedule array and returning it with pointer in char array form
char* SHA256::extractWord(const char messageSchedule[], int ind) {
    char* newBits = new char[MSA_WORD_BITS];
    for(int i = 0; i < MSA_WORD_BITS; i++) {
        newBits[i] = messageSchedule[(ind * MSA_WORD_BITS) + i];
    }
    return newBits;
}

// Function for copying character array
char* SHA256::copyCharArr(const char arr1[], int length) {
    char* newBits = new char[length];
    for(int i = 0; i < length; i++) {
        newBits[i] = arr1[i];
    }
    return newBits;
}

// Function for moving values of one character array to another, being with the same length
void SHA256::moveArr(char arr1[], const char arr2[], int length) {
    for(int i = 0; i < length; i++) {
        arr1[i] = arr2[i];
    }
}

// Function implementing the first part of the SHA-256 algorithm
void SHA256::fillMessageBlock(const char text[], char messageBlock[], int &length) {
    length = 0;
    // Encoding the input to binary
    for(int i = 0; text[i] != '\0'; i++) {
        unsigned int charDec = (int) text[i];
        int temp = ((i + 1) * CHAR_BITS) - 1;
        do {
            messageBlock[temp] = (char) ((charDec % 2) + '0');
            charDec /= 2;
            temp--;
            length++;
        } while(charDec != 0);
        while(temp >= (i * CHAR_BITS)) {
            messageBlock[temp] = '0';
            temp--;
            length++;
        }
    }
    int charsBinaryCount = length;
    // Appending 1 to the end
    messageBlock[length++] = '1';

    // Filling with zeros until the length of the array is multiple of 512, i.e. the CHUNK_SIZE
    while((length + 64) % CHUNK_SIZE != 0) {
        messageBlock[length++] = '0';
    }
    // Appending the length of the input in binary in big-endian
    for(int i = 0; i < 64; i++) {
        messageBlock[length++] = '0';
    }
    for(int tempInd = length - 1; charsBinaryCount != 0; charsBinaryCount /= 2, tempInd--) {
        messageBlock[tempInd] = (char) ((charsBinaryCount % 2) + '0');
    }
}

// Function converting the hash variables, containing the result, to char array string
void SHA256::hashVarsToChar(char* h[8]) {
    for(int i = 0, ind = 0; i < MSA_WORD_BITS / 4; i++) {
        for(int j = 0; j < MSA_WORD_BITS; j += 4) {
            int number =
                    ((h[i][j] - '0') * pow2(3)) + ((h[i][j + 1] - '0') * pow2(2)) + ((h[i][j + 2] - '0') * pow2(1)) +
                    (h[i][j + 3] - '0');
            if(number < 10) {
                hash[ind++] = (char) (number + '0');
            }
            else {
                hash[ind++] = (char) (number - 10 + 'a');
            }
        }
    }
}

// Function implementing the second part of the SHA-256 algorithm
void SHA256::fillMessageScheduleArray2(
        const char text[], const char* messageBlock, int messageBlockLength,
        char messageSchedule[MESSAGE_SCHEDULE_ARRAY_BITS],
        char*&h0, char*&h1, char*&h2, char*&h3, char*&h4, char*&h5, char*&h6, char*&h7
) {
    for(int i = 0; i < messageBlockLength / CHUNK_SIZE; i++) {
        for(int j = 0; j < CHUNK_SIZE; j++) {
            messageSchedule[j] = messageBlock[(i * CHUNK_SIZE) + j];
        }
        for(int j = CHUNK_SIZE; j < MESSAGE_SCHEDULE_ARRAY_BITS; j++) {
            messageSchedule[j] = '0';
        }
        for(int j = 16; j < 64; j++) {
            char* sigma0 = xorArr(
                    xorArr(
                            rightRotate(messageSchedule, (j - 15) * MSA_WORD_BITS, 7),
                            rightRotate(messageSchedule, (j - 15) * MSA_WORD_BITS, 18)
                    ),
                    rightShift(messageSchedule, (j - 15) * MSA_WORD_BITS, 3)
            );

            char* sigma1 = xorArr(
                    xorArr(
                            rightRotate(messageSchedule, (j - 2) * MSA_WORD_BITS, 17),
                            rightRotate(messageSchedule, (j - 2) * MSA_WORD_BITS, 19)
                    ),
                    rightShift(messageSchedule, (j - 2) * MSA_WORD_BITS, 10)
            );

            char* wA = new char[MSA_WORD_BITS];
            char* wB = new char[MSA_WORD_BITS];
            for(int k = 0; k < MSA_WORD_BITS; k++) {
                wA[k] = messageSchedule[((j - 16) * MSA_WORD_BITS) + k];
                wB[k] = messageSchedule[((j - 7) * MSA_WORD_BITS) + k];
            }

            char* result = addArr(addArr(addArr(wA, sigma0, 0), wB, 1), sigma1, 1);

            for(int k = 0; k < MSA_WORD_BITS; k++) {
                messageSchedule[(j * MSA_WORD_BITS) + k] = result[k];
            }

            delete[] sigma0;
            delete[] sigma1;
            delete[] wA;
            delete[] wB;
            delete[] result;
        }
        char* a = copyCharArr(h0, MSA_WORD_BITS), * b = copyCharArr(h1, MSA_WORD_BITS),
                * c = copyCharArr(h2, MSA_WORD_BITS), * d = copyCharArr(h3, MSA_WORD_BITS),
                * e = copyCharArr(h4, MSA_WORD_BITS), * f = copyCharArr(h5, MSA_WORD_BITS),
                * g = copyCharArr(h6, MSA_WORD_BITS), * h = copyCharArr(h7, MSA_WORD_BITS);
        for(int q = 0; q < MESSAGE_SCHEDULE_ARRAY_BITS / MSA_WORD_BITS; q++) {
            char* sum0 = xorArr(xorArr(rightRotate(a, 0, 2), rightRotate(a, 0, 13)), rightRotate(a, 0, 22));
            char* sum1 = xorArr(xorArr(rightRotate(e, 0, 6), rightRotate(e, 0, 11)), rightRotate(e, 0, 25));
            char* majority = xorArr(xorArr(andArr(a, b, 0), andArr(a, c, 0)), andArr(b, c, 0));
            char* choice = xorArr(andArr(e, f, 0), andArr(notArr(e), g, 1));
            char* temp1 = addArr(
                    addArr(
                            addArr(
                                    addArr(h, sum1, 0),
                                    choice,
                                    1
                            ),
                            intToBinaryChar(ROUNDING_CONSTANTS[q]),
                            3
                    ),
                    extractWord(messageSchedule, q),
                    3
            );
            char* temp2 = addArr(sum0, majority, 0);

            moveArr(h, g, MSA_WORD_BITS);
            moveArr(g, f, MSA_WORD_BITS);
            moveArr(f, e, MSA_WORD_BITS);
            delete[] e;
            e = addArr(d, temp1, 0);
            moveArr(d, c, MSA_WORD_BITS);
            moveArr(c, b, MSA_WORD_BITS);
            moveArr(b, a, MSA_WORD_BITS);
            delete[] a;
            a = addArr(temp1, temp2, 0);

            delete[] sum0;
            delete[] sum1;
            delete[] majority;
            delete[] choice;
            delete[] temp1;
            delete[] temp2;
        }
        h0 = addArr(h0, a, 1);
        h1 = addArr(h1, b, 1);
        h2 = addArr(h2, c, 1);
        h3 = addArr(h3, d, 1);
        h4 = addArr(h4, e, 1);
        h5 = addArr(h5, f, 1);
        h6 = addArr(h6, g, 1);
        h7 = addArr(h7, h, 1);

        delete[] a;
        delete[] b;
        delete[] c;
        delete[] d;
        delete[] e;
        delete[] f;
        delete[] g;
        delete[] h;
    }
}

// Function returning a ready hash in char array string
char* SHA256::calculate(const char text[]) {
    int messageBlockLength;
    char* messageBlock = new char[MAX_MESSAGE_LENGTH];

    fillMessageBlock(text, messageBlock, messageBlockLength);
    char messageSchedule[MESSAGE_SCHEDULE_ARRAY_BITS];
    char* h0 = intToBinaryChar(INITIAL_HASH_VALUES[0]), * h1 = intToBinaryChar(INITIAL_HASH_VALUES[1]),
            * h2 = intToBinaryChar(INITIAL_HASH_VALUES[2]), * h3 = intToBinaryChar(INITIAL_HASH_VALUES[3]),
            * h4 = intToBinaryChar(INITIAL_HASH_VALUES[4]), * h5 = intToBinaryChar(INITIAL_HASH_VALUES[5]),
            * h6 = intToBinaryChar(INITIAL_HASH_VALUES[6]), * h7 = intToBinaryChar(INITIAL_HASH_VALUES[7]);

    fillMessageScheduleArray2(text, messageBlock, messageBlockLength, messageSchedule, h0, h1, h2, h3, h4, h5, h6, h7);

    char* hashVarPointers[8] = {h0, h1, h2, h3, h4, h5, h6, h7};
    hashVarsToChar(hashVarPointers);
    hash[HASH_LENGTH] = '\0';

    delete[] h0;
    delete[] h1;
    delete[] h2;
    delete[] h3;
    delete[] h4;
    delete[] h5;
    delete[] h6;
    delete[] h7;
    delete[] messageBlock;
//
    return hash;
}

bool SHA256::compare(const char* password, const char* hashedPassword) {
    calculate(password);
    return strcmp(hash, hashedPassword) == 0;
}

const char* SHA256::getHash() {
    return hash;
}

#pragma clang diagnostic pop