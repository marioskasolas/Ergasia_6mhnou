#include <stdio.h>
#include <math.h>

int ms_bin(unsigned short int hexadecimal);
int sms_bin(unsigned short int hexadecimal);
int age_converter(unsigned short temp,unsigned short temp2);
int gender_converter(unsigned short int hexadecimal);
int vote_converter(unsigned short int hexadecimal);

int main() {
    unsigned short temp1, temp2;
    int age,gender,vote;
    unsigned short int hexadecimal;

    do {
        printf("enter hexadecimal\n");

        scanf("%x", &hexadecimal);

        /* χρήση συναρτήσεων για απομώνωση των πρώτων 7 bit */
        temp1 = ms_bin(hexadecimal);
        printf("%d ptr1\n", temp1);
        temp2 = sms_bin(hexadecimal);
        printf("%d ptr2\n", temp2);

        age = age_converter(temp2, temp1);
        gender = gender_converter(hexadecimal);
        vote = vote_converter(hexadecimal);

    } while ((age < 18 || age > 99) && (gender < 1 || gender > 3) && (vote < 0 || vote > 6 ));
    printf("age is %d\n",age);
    vote_converter(hexadecimal);
    printf("their gender is %d",gender);
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
           return sum;
       }

       int gender_converter(unsigned short int hexadecimal){
           /* κάνει isolate το τελευταίο bit του δεύτερου 16δικού*/
           unsigned short int temp1,temp2;
           temp1 = (hexadecimal >> 8) & 0x0f;
           temp1 = temp1 & 0x0001;
           if(temp1 == 1){
               temp1 = 2;
           }

           temp2 = (hexadecimal >> 4) & 0x00f;
           temp2 = temp2 >> 3;
           if(temp2 == 1){
               temp2 = 1;
           }

           return temp1 + temp2;
       }

       int vote_converter(unsigned short int hexadecimal){
           unsigned short int temp1,temp2;
           temp1 = hexadecimal & 0x000f;
           int consec = 0;
           int r,index;
           for(int i = 0; i <= 3; i++){
               r = temp1 % 2;
               temp1 = temp1 /2;
               if(r == 1){
                   consec = consec + 1;
                   index = i;
                   if(consec > 1){
                       return -1;
                   }
               }

           }
           printf("%d consec\n",consec);
           temp2 = hexadecimal >> 4 & 0x00f;
           temp2 = temp2 & 0x0111;
           for(int i = 4; i <= 6; i++){
               r = temp2 % 2;
               temp2 = temp2 / 2;
               if(r == 1){
                   consec = consec + 1;
                   index = i;
                   printf("consec %d",consec);
                   if(consec > 1){
                       return -1;
                   }
               }
           }
           printf("%d index is at\n",index);
           return index;
       }
