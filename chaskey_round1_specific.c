// no custom
#include <stdio.h>

#define read_csr(reg) ({ unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})


void Round(uint32_t *v){uint32_t a, b, c, d;
	asm volatile ( "add.rol5.xor %[z], %[x], %[y]\n\t"
	        : [z] "=r" (a)
	        : [x] "r" (v[1]), [y] "r" (v[0]));
	asm volatile ( "add.rol16 %[z], %[x], %[y]\n\t"
	        : [z] "=r" (b)
	        : [x] "r" (v[1]), [y] "r" (v[0]));
	asm volatile ( "add %[z], %[x], %[y]\n\t"
	        : [z] "=r" (c)
	        : [x] "r" (v[3]), [y] "r" (v[2]));
	asm volatile ( "add.rol8.xor %[z], %[x], %[y]\n\t"
	        : [z] "=r" (d)
	        : [x] "r" (v[3]), [y] "r" (v[2]));
	asm volatile ( "add.rol7.xor %[z], %[x], %[y]\n\t"
	        : [z] "=r" (v[1])
	        : [x] "r" (a), [y] "r" (c));
	asm volatile ( "add.rol16 %[z], %[x], %[y]\n\t"
	        : [z] "=r" (v[2])
	        : [x] "r" (a), [y] "r" (c));
	asm volatile ( "add.rol13.xor %[z], %[x], %[y]\n\t"
	        : [z] "=r" (v[3])
	        : [x] "r" (d), [y] "r" (b));
	asm volatile ( "add %[z], %[x], %[y]\n\t"
	        : [z] "=r" (v[0])
	        : [x] "r" (b), [y] "r" (d));
        }

int main() {
	uint32_t v[4] = {1, 2, 3, 4};
	int i;
	long cycles1, cycles2;
	
	for (i = 0; i < 4; i++){
		printf("v[%d] = %x\n", i + 1, v[i]);
	}

	//cycles1 = read_csr(instret);
	Round(v);
	//cycles2 = read_csr(instret);

	for (i = 0; i < 4; i++){
		printf("v[%d] = %x\n", i + 1, v[i]);
	}

	//printf("instructions: %ld\n", cycles2 - cycles1);
	
	return 0;
}
