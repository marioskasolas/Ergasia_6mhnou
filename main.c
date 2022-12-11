#include <stdio.h>
#include <math.h>

int ms_bin(unsigned short int hexadecimal);
int sms_bin(unsigned short int hexadecimal);
int age_converter(unsigned short temp,unsigned short temp2);

int main() {
    unsigned short temp1, temp2;
    int age;
    unsigned short int hexadecimal;

    do {
        printf("enter hexadecimal\n");

        scanf("%x", &hexadecimal);

        /* χρήση συναρτήσεων για απομώνωση των πρώτων 7 bit */
        temp1 = ms_bin(hexadecimal);
        printf("%d ptr1\n", temp1);
        temp2 = sms_bin(hexadecimal);
        printf("%d ptr2\n", temp2);
        age_converter(temp2, temp1);
        age = age_converter(temp2, temp1);

    } while (age < 18 && age > 99);
    printf("age is %d\n",age);
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

       /* συνάρτηση που μετατρέπει τον δεκαξαδικό σε ηλικία μορφής ακεραίου */
       int age_converter(unsigned short f3b,unsigned short temp2){
           int r;
           int sum = 0;
           for(int i = 0; i <= 2; i++){
               r = f3b % 2;
               f3b = f3b / 2;
               if(r == 1){
                   sum = sum + pow(2,i);
               }
           }

           for(int i = 3; i <= 6; i++){
               r = temp2 % 2;
               temp2 = temp2 / 2;
               if(r == 1){
                   sum = sum + pow(2,i);
               }
           }
           printf("sum is %d\n",sum);
           return sum;
       }