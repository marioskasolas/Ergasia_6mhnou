#include <stdio.h>

int bin(unsigned short int hexadecimal);

int main() {
    /* εισαγωγή hexadecimal */
    unsigned short int hexadecimal;
    printf("enter hexadecimal\n");
    scanf("%x", &hexadecimal);
    printf("you entered %x\n", hexadecimal);
    printf("%x\n", hexadecimal);
    bin(hexadecimal);

}


    int bin(unsigned short int hexadecimal){
       int i;
       unsigned short int ptr1,ptr2,ptr3,ptr4;

       ptr1 = (hexadecimal >> 12) ;
       printf("%x ptr1\n",ptr1);


       ptr2 = (hexadecimal >> 8);
       ptr2 = (ptr2 << 4) & 0xf;
       printf("%x ptr2\n",ptr2);

       ptr3 = (hexadecimal >> 4);
       ptr3 = (ptr3 << 8) & 0xf00;
       printf("%x ptr3\n",ptr3);

       ptr4 = (hexadecimal >> 12);
       ptr4 = (ptr4 << 12) & 0xffff ;
       printf("%x ptr4\n",ptr4);
}
