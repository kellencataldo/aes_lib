#include <stdio.h>
#include <string.h>

#include "aes_lib/aes_lib.h"

int main() {

	//Electronic Code Book (ECB) mode
	unsigned char message[(AES_SIZE * 2) + 1] = { "I LOVE 2 ENCRYPT WORDS WITH AES!" };
	unsigned char key[AES_SIZE+1] = { "YELLOW SUBMARINE" };

	printf("This message will be encrypted using ECB mode: %s\n", message);
	printf("With this key: %s\n", key);
	aes_ecb_encrypt(message, key, 32);
	printf("Here is the encrypted result: %s\n", message);
	aes_ecb_decrypt(message, key, 32);
	printf("Here is the decrypted message: %s\n\n", message);

	
	//Cipher Block Chaining (CBC) mode, Initilization Vector (IV) required
	memcpy(message, "I LOVE 2 ENCRYPT WORDS WITH CBC!", 32);
	memcpy(key, "HERE IS MY KEY!!", 16);
	unsigned char iv[AES_SIZE+1] = { "HERE IS MY IV!!!" };

	printf("This message will be encrypted using CBC mode: %s\n", message);
	printf("With this key: %s and this IV: %s\n", key, iv);
	aes_cbc_encrypt(message, key, 32, iv);
	printf("Here is the encrypted result: %s\n", message);
	aes_cbc_decrypt(message, key, 32, iv);
	printf("Here is the decrypted message: %s\n\n", message);



	return 0;

}
