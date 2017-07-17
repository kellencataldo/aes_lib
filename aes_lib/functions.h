#pragma once
unsigned char gmul(unsigned char a, unsigned char b);

extern unsigned char s_box[256];
extern unsigned char inv_s[256];
extern unsigned char rcon[AES_SIZE];

void KeyExpansion(unsigned char* inputKey, unsigned char* expandedKeys);
void AddRoundKey(unsigned char * state, unsigned char * roundKey);