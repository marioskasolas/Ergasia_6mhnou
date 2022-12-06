#include <stdio.h>

int ms_bin(unsigned short int hexadecimal);
int case_s(unsigned short int ptr);
int sms_bin(unsigned short int hexadecimal);

int main() {

    /* εισαγωγή hexadecimal */
    unsigned short int msb1,msb2;
    unsigned short int hexadecimal;
    printf("enter hexadecimal\n");
    scanf("%x", &hexadecimal);

    /* χρήση συναρτήσεων για μετατροπή απο hexa σε binary */
    msb1 = ms_bin(hexadecimal);
    printf("%x ptr1\n",msb1);
    msb2 = sms_bin(hexadecimal);
    printf("%x ptr2\n",msb2);

    /* υπολογισμός ηλικίας μεσώ των  7msb */
    int tran1;
    tran1 = (int)msb1 * 1000;
    printf("%d tran1",tran1);



}
       /* συνάρτηση για μετατροπή δεκαεξαδικού σε binary */
        int case_s(unsigned short int ptr) {
             int temp;
            switch(ptr) {
                case 0:
                    temp = 0b0000;
                    break;
                case 1:
                    temp = 0b0001;
                    break;
                case 2:
                    temp = 0b0010;
                    break;
                case 3:
                    temp = 0b0011;
                    break;
                case 4:
                    temp = 0b0100;
                    break;
                case 5:
                    temp = 0b0101;
                    break;
                case 6:
                    temp = 0b0110;
                    break;
                case 7:
                    temp = 0b0111;
                    break;
                case 8:
                    temp = 0b1000;
                    break;
                case 9:
                    temp = 0b1001;
                    break;
                case 0xA:
                    temp = 0b1010;
                    break;
                case 0xB:
                    temp = 0b1011;
                    break;
                case 0xc:
                    temp = 0b1100;
                    break;
                case 0xD:
                    temp = 0b1101;
                    break;
                case 0xe:
                    temp = 0b1110;
                    break;
                case 0xf:
                    temp = 0b1111;
                    break;
            }
            return temp;
        }




        /* συνάρτηση που χωρίζει τα πρώτα 4 most significant bits */
       int ms_bin(unsigned short int hexadecimal){
       int i;
       unsigned short int ptr1;

       ptr1 = (hexadecimal >> 12);
       ptr1 = case_s(ptr1);
       return  ptr1;

       }

       /* συνάρτηση που χωρίζει τα δεύτερα  most significant bits δηλαδή τα 4 επομένα των πρώτων 4ρών*/
       int sms_bin(unsigned short int hexadecimal){
           unsigned short int ptr2;

           ptr2 = (hexadecimal >> 8) & 0x0f;
           /*ptr2 = case_s(ptr2);*/
           ptr2 = (ptr2 >>1 );
           return ptr2;
       }