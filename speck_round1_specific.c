// speck specific
#include <stdio.h>
#define read_csr(reg) ({ unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})

void Round(uint32_t *v, uint32_t k){
	asm volatile ("ror8.add %[z], %[x], %[y]\n\t" 
                                                : [z] "=r" (v[0]) 
                                                : [x] "r" (v[0]), [y] "r" (v[1])); 
	v[0] = v[0] ^ k;
	asm volatile ("rol3.xor %[z], %[x], %[y]\n\t" 
                                                : [z] "=r" (v[1]) 
                                                : [x] "r" (v[1]), [y] "r" (v[0])); 
}

int main() {
	uint32_t v[4] = {1, 2};
	uint32_t k = 10;
	int i;
	long cycles1, cycles2;
	
// 	for (i = 0; i < 4; i++){
// 		printf("v[%d] = %x\n", i + 1, v[i]);
// 	}

	//cycles1 = read_csr(instret);
	Round(v, k);
	//cycles2 = read_csr(instret);

// 	for (i = 0; i < 4; i++){
// 		printf("v[%d] = %x\n", i + 1, v[i]);
// 	}

	//printf("instructions: %ld\n", cycles2 - cycles1);
	
	return 0;
}
