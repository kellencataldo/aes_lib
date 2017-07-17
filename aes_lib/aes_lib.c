#include "aes_lib.h"
#include "functions.h"

void aes_ecb_encrypt(unsigned char * plain_text, unsigned char* key, int text_length) {

	for (int i = 0; i < text_length; i += 16) {
		AES_encrypt(plain_text + i, key);
	}
}


void aes_ecb_decrypt(unsigned char * plain_text, unsigned char* key, int text_length) {

	for (int i = 0; i < text_length; i += 16) {
		AES_decrypt(plain_text + i, key);
	}
}

void aes_cbc_encrypt(unsigned char * plain_text, unsigned char* key, int text_length, unsigned char * iv) {
	
	char * xor_vector = iv;

	for (int i = 0; i < text_length; i += 16) {
		AddRoundKey(plain_text+i, xor_vector);
		AES_encrypt(plain_text+i, key);
		xor_vector = plain_text + i;
	}

}

void aes_cbc_decrypt(unsigned char * plain_text, unsigned char* key, int text_length, unsigned char * iv) {

	char * xor_vector = iv;
	char place_holder[AES_SIZE];

	int i = 0;
	for (i; i < text_length; i += 16) {
		memcpy(place_holder, plain_text+i, AES_SIZE);
		AES_decrypt(plain_text + i, key);
		AddRoundKey(plain_text + i, xor_vector);
		memcpy(xor_vector, place_holder, AES_SIZE);
	}

}