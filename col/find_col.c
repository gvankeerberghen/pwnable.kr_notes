#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void left_pad(char *str) {
  int len = strlen(str);
  if (len < 10) {
    int pad_len = 10 - len;
    char *padded_str = malloc(11);
    memset(padded_str, '0', pad_len);
    padded_str[pad_len] = '\0';
    strcat(padded_str, str);
    strcpy(str, padded_str);
    free(padded_str);
  }
}

void right_pad(char *str) {
  int len = strlen(str);
  if (len < 10) {
    int pad_len = 10 - len;
    char *padded_str = malloc(pad_len + 1);
    memset(padded_str, '0', pad_len);
    padded_str[pad_len] = '\0';
    strcat(str, padded_str);
    free(padded_str);
  }
}

unsigned long hashcode = 0x21DD09EC; //  
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
  int i;
  // Tested up to 20392106000000000000
  for (i=99998;i<100000;i++){
    char *test = malloc(21);
    sprintf(test, "%d", i);
    right_pad(test);
    strcat(test,"0000000000");
    printf("Testing %s\n", test);
    if(strlen(test) != 20){
      printf("\tpasscode length should be 20 bytes\n");
    } else {
      printf("Hashcode in lu %lu\n", hashcode);
      printf("check_password in lu %lu\n", check_password( test ));
      if(hashcode == check_password( test )){
        printf("Success with %s", test);
        break;
      }
    }
    free(test);
  }
  return 0;
}