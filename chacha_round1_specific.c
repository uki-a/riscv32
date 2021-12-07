// app-specific
#include <stdio.h>

#define read_csr(reg) ({ unsigned long __tmp;\
asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
__tmp;})


void Round(uint32_t *v){
        v[0] += v[1];  
        asm volatile ("xor.rol16 %[z], %[x], %[y]\n\t" 
                                                : [z] "=r" (v[3]) 
                                                : [x] "r" (v[3]), [y] "r" (v[0])); 
	  	v[2] += v[3]; 
        asm volatile ("xor.rol12 %[z], %[x], %[y]\n\t" 
                                                : [z] "=r" (v[1]) 
                                                : [x] "r" (v[1]), [y] "r" (v[2])); 
  		v[0] += v[1]; 
        asm volatile ("xor.rol8 %[z], %[x], %[y]\n\t" 
                                                : [z] "=r" (v[3]) 
                                                : [x] "r" (v[3]), [y] "r" (v[0])); 
  		v[2] += v[3]; 
        asm volatile ("xor.rol7 %[z], %[x], %[y]\n\t" 
                                                : [z] "=r" (v[1]) 
                                                : [x] "r" (v[1]), [y] "r" (v[2])); 
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
