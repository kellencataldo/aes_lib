#include "aes_lib.h"
#include "functions.h"

void ReverseSubBytes(unsigned char * state) {
	for (int i = 0; i < AES_SIZE; i++) {
		state[i] = inv_s[state[i]];
	}
}

void ReverseShiftRows(unsigned char * plain_text) {
	unsigned char temp_block[AES_SIZE];

	for (int i = 0; i < AES_SIZE; i += 4) {
		//incrementing by 5 causes the diagonal shift effect
		temp_block[i] = plain_text[i];
		temp_block[(i + 5) % AES_SIZE] = plain_text[i+1];
		temp_block[(i + 10) % AES_SIZE] = plain_text[i+2];
		temp_block[(i + 15) % AES_SIZE] = plain_text[i+3];
	}

	for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = temp_block[i];
	}
}

void ReverseMixColumns(unsigned char *plain_text) {

	unsigned char temp_block[AES_SIZE];

	for (int i = 0; i < AES_SIZE; i += 4) { 
	//inverse multiplication > 9,11,13,14
		temp_block[i] = gmul(plain_text[i], (unsigned char) 14) ^ gmul(plain_text[i + 1], (unsigned char)11) ^ 
			gmul(plain_text[i + 2], (unsigned char)13) ^ gmul(plain_text[i + 3], (unsigned char)9);

		temp_block[i + 1] = gmul(plain_text[i], (unsigned char) 9) ^ gmul(plain_text[i + 1], (unsigned char)14) ^ 
			gmul(plain_text[i + 2], (unsigned char)11) ^ gmul(plain_text[i + 3], (unsigned char)13);

		temp_block[i + 2] = gmul(plain_text[i], (unsigned char)13) ^ gmul(plain_text[i + 1], (unsigned char)9) ^ 
			gmul(plain_text[i + 2], (unsigned char)14) ^ gmul(plain_text[i + 3], (unsigned char)11);

		temp_block[i + 3] = gmul(plain_text[i], (unsigned char)11) ^ gmul(plain_text[i + 1], (unsigned char)13) ^ 
			gmul(plain_text[i + 2], (unsigned char)9) ^ gmul(plain_text[i + 3], (unsigned char)14);
	}

 for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = temp_block[i];
	}
}


void AES_decrypt(unsigned char * plain_text, unsigned char * key) {

	unsigned char expandedKey[AES_SIZE * (NUM_ROUNDS + 1)];

	KeyExpansion(key, expandedKey);

	AddRoundKey(plain_text, expandedKey + (AES_SIZE * NUM_ROUNDS ));

	ReverseShiftRows(plain_text);
	ReverseSubBytes(plain_text);

	for (int i = NUM_ROUNDS -1; i >= 1; i--) {
		AddRoundKey(plain_text, expandedKey + (AES_SIZE * i));
		ReverseMixColumns(plain_text);
		ReverseShiftRows(plain_text);
		ReverseSubBytes(plain_text);
	}
	AddRoundKey(plain_text, expandedKey);
}
