#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "threefish.h"

#define CLOCK(x) (x >> 8 | (x ^ (x >> 7) ^ (x >> 6) ^ (x >> 2)) << 24)
void rnd(unsigned char *b, int len) {
	static uint32_t s = 0xFEEDFACE;
	for(int i=0; i<len; i++, s=CLOCK(s)) b[i] = (unsigned char)s;
}

int main() {
	unsigned char check[] = {
		0x55,0xfd,0x4f,0xc6,0x7c,0x00,0x84,0x79,
		0x4a,0x54,0xc3,0x8d,0xc7,0x94,0x0e,0x6a,
		0x62,0xf6,0x99,0x04,0x5b,0x99,0xa3,0x64,
		0x38,0xdd,0x5a,0x6e,0xb5,0x3e,0x8f,0x89,
		0x89,0xce,0xe9,0xd2,0xe3,0x3e,0x9a,0xfd,
		0x3d,0x16,0x50,0x73,0x93,0x8b,0xe8,0x16,
		0x24,0x7c,0xb3,0x8f,0xba,0xb2,0xa4,0x4d,
		0x19,0xfa,0x90,0x72,0xfb,0x81,0xe2,0xfc,
		0x71,0xf3,0x91,0x63,0x4f,0x3c,0x6d,0xdb,
		0x3e,0x12,0x58,0x18,0x03,0x57,0x3f,0x01,
		0x37,0xc2,0x77,0x79,0x71,0xbc,0x5c,0xdf,
		0xaf,0x13,0xd0,0x14,0xb5,0x89,0xf7,0x0e,
		0x90,0x09,0x6d,0xe3,0xf6,0x19,0x1a,0x8f,
		0xfa,0x1c,0xad,0x2f,0xfa,0xbd,0x25,0x4b,
		0xc4,0xdc,0x0f,0x28,0xc2,0x64,0xc6,0xe2,
		0x78,0x88,0x5f,0xc6,0x3a,0xbf,0x4d,0x68 };

	unsigned char c[32], p[32], k[32], t[16];

	for(int i=0; i<4; i++) {
		rnd(p,32); rnd(k,32); rnd(t,16);
		threefish(c, p, k, t);
		printf("%s\n", !memcmp(c, check + 32*i, 32) ? "PASS" : "FAIL");
	}

	return 0;
}
