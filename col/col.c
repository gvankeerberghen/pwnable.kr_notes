#include <stdio.h>
#include <string.h>
unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p){
	int* ip = (int*)p;
	int i;
	int res=0;
	for(i=0; i<5; i++){
    printf("\tres %lu\n", res);
    printf("\ti %lu\n", i);
    printf("\tip[i] %d\n", ip[i]);
		res += ip[i];
	}
	return res;
}

int main(int argc, char* argv[]){
	if(argc<2){
		printf("usage : %s [passcode]\n", argv[0]);
		return 0;
	}
  printf("Received '%s' of length %d\n",argv[1],strlen(argv[1]));
  printf("Received '%x' of length %d\n",argv[1],strlen(argv[1]));
	if(strlen(argv[1]) != 20){
		printf("passcode length should be 20 bytes\n");
    printf("Received '%s' of length %d\n",argv[1],strlen(argv[1]));
    printf("Received '%x' of length %d\n",argv[1],strlen(argv[1]));
		return 0;
	}

	if(hashcode == check_password( argv[1] )){
		// system("/bin/cat flag");
    printf("Success");
		return 0;
	}
	else
		printf("wrong passcode.\n");
	return 0;
}