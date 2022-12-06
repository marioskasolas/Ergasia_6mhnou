#include <stdio.h>
int ms_bin(unsigned short int hexadecimal);
int sms_bin(unsigned short int hexadecimal);

int main() {
    /* ορισμός πινάκων για την αποθήκευση των bit*/
    int msb1;
    int msb2;
    unsigned short temp1,temp2;

    /* εισαγωγή hexadecimal */
    unsigned short int hexadecimal;
    printf("enter hexadecimal\n");
    scanf("%x", &hexadecimal);

    /* χρήση συναρτήσεων για απομώνωση των πρώτων 7 bit */
    temp1 = ms_bin(hexadecimal);
    printf("%d ptr1\n",temp1);
    temp2 = sms_bin(hexadecimal);
    printf("%d ptr2\n",temp2);


}

        /* συνάρτηση που χωρίζει τα πρώτα 4 most significant bits */
        int ms_bin(unsigned short int hexadecimal){
       int i;
       unsigned short int ptr1;
       ptr1 = (hexadecimal >> 12);
       return  ptr1;

       }

       /* συνάρτηση που χωρίζει τα δεύτερα  most significant bits δηλαδή τα 4 επομένα των πρώτων 4ρών*/
       int sms_bin(unsigned short int hexadecimal){
           unsigned short int ptr2;

           ptr2 = (hexadecimal >> 8) & 0x0f;
           ptr2 = (ptr2 >>1 );
           return ptr2;
       }

