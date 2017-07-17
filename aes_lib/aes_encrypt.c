#include "aes_lib.h"
#include "functions.h"

void SubBytes(unsigned char * plain_text) {
	for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = s_box[plain_text[i]];
	}
}

void ShiftRows(unsigned char * plain_text) {
	unsigned char temp_block[AES_SIZE];

	for (int i = 0; i < AES_SIZE; i += 4) {
		//incrementing by 5 causes the diagonal shift effect
		temp_block[i] = plain_text[i];
		temp_block[i + 1] = plain_text[(i + 5) % AES_SIZE];
		temp_block[i + 2] = plain_text[(i + 10) % AES_SIZE];
		temp_block[i + 3] = plain_text[(i + 15) % AES_SIZE];
	}

	for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = temp_block[i];
	}
}
void MixColumns(unsigned char *plain_text) {

	unsigned char temp_block[AES_SIZE];

	for (int i = 0; i < AES_SIZE; i += 4) {

		temp_block[i] = gmul(plain_text[i], (unsigned char)2) ^ gmul(plain_text[i + 1], (unsigned char)3) ^ plain_text[i + 2] ^ plain_text[i + 3];
		temp_block[i + 1] = plain_text[i] ^ gmul(plain_text[i + 1], (unsigned char) 2) ^ gmul(plain_text[i + 2], (unsigned char) 3) ^ plain_text[i + 3];
		temp_block[i + 2] = plain_text[i] ^ plain_text[i + 1] ^ gmul(plain_text[i + 2], (unsigned char) 2) ^ gmul(plain_text[i + 3], (unsigned char) 3);
		temp_block[i + 3] = gmul(plain_text[i], (unsigned char) 3) ^ plain_text[i + 1] ^ plain_text[i + 2] ^ gmul(plain_text[i + 3], (unsigned char) 2);
	}

	for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = temp_block[i];
	}
}


void AES_encrypt(unsigned char * plain_text, unsigned char * key) {

	//https://en.wikipedia.org/wiki/Advanced_Encryption_Standard#High-level_description_of_the_algorithm

	unsigned char expandedKey[AES_SIZE * (NUM_ROUNDS + 1)]; 
	KeyExpansion(key, expandedKey);
	AddRoundKey(plain_text, key);

	for (int i = 0; i < NUM_ROUNDS - 1; i++) {
		SubBytes(plain_text);
		ShiftRows(plain_text);
		MixColumns(plain_text);
		AddRoundKey(plain_text, expandedKey + (AES_SIZE * (i + 1)));
	}

	SubBytes(plain_text);
	ShiftRows(plain_text);
	AddRoundKey(plain_text, expandedKey + (AES_SIZE * NUM_ROUNDS));
}
