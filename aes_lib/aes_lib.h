#define AES_SIZE 16 //16 bytes == 128 bits
#define NUM_ROUNDS 10

//private functions, one block at a time
void AES_decrypt(unsigned char * plain_text, unsigned char * key);
void AES_encrypt(unsigned char * plain_text, unsigned char * key);

//public functions
void aes_ecb_encrypt(unsigned char * plain_text, unsigned char* key, int text_length);
void aes_ecb_decrypt(unsigned char * plain_text, unsigned char* key, int text_length);
void aes_cbc_encrypt(unsigned char * plain_text, unsigned char* key, int text_length, unsigned char * iv);
void aes_cbc_decrypt(unsigned char * plain_text, unsigned char* key, int text_length, unsigned char * iv);


