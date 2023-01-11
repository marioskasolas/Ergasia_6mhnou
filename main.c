#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_CANDIDATES 7

//Δηλώσεις συναρτήσεων
int number_of_hex_series(void);
int age_converter(char,char);
int gender_converter(char,char);
int vote_converter(char,char);
unsigned short int hex_conv(char c);

void candidates_table(unsigned int cand[NUM_CANDIDATES][3] ,int **,int);
void bubble_sort(int**,int);
void max_search(unsigned int cand[NUM_CANDIDATES][3]);
void histograms(unsigned int cand[NUM_CANDIDATES][3]);



int main(void){
    unsigned int cand[NUM_CANDIDATES][3];
    int age_of_voters[NUM_CANDIDATES][4] = {0};
    int age,gender,vote,i,n = 0,pl,**ptr,youth = 0,elder = 0;
    char c[5];
    c[4] = '\0';

    //άνοιγμα αρχείου
    FILE * fp;
    fp = fopen("C:/Users/mario/OneDrive/Desktop/writeup.dat","r");
    if(fp == NULL)
        exit(10);
    pl = number_of_hex_series();

    //Δυναμική δέσμευση πίνακα ίση με τους ψηφοφόρους
    ptr = (int**)malloc(pl * sizeof(int*));
    for(i = 0;i < pl;i++){
        ptr[i] = (int*)malloc(3 * sizeof(int));
    }

    do{
        for(i = 1;i <= 4;i++){
            c[i] = fgetc(fp);
        }
        //οι συναρτήσεις age , gender και vote δέχονται ώς ορίσματα τα ψηφία hex της κωδικοποιημένης μορφής των πληροφορίων και τα μετατρέπουν σε ηλικία γένος και ψήφο του ψηφοφόρου
        age = age_converter(c[1],c[2]);
        gender = gender_converter(c[2],c[3]);
        vote = vote_converter(c[3], c[4]);

        printf("%d vote,%d age,%d gender\n",vote,age,gender);
        //ακολουθεί έλεγχος έγκυρης ψήφου
        if((age >= 18 && age <= 99) && (gender >= 1 && gender <= 3) && ((vote >= 0 && vote <= 6) || vote == -2)){
            printf("This voters vote is valid!\n");
            printf("\n");

            //δημιουργεία πίνακα ηλικακών ομάδων ψήφων κάθε ψηφοφόρου
            if(vote != -2) {
                if ( age <= 29) {
                    age_of_voters[vote][0]++;
                    youth++;
                } else if (age <= 44) {
                    age_of_voters[vote][1]++;
                } else if (age <= 59) {
                    age_of_voters[vote][2]++;
                } else {
                    age_of_voters[vote][3]++;
                    elder++;
                }
            }
            ptr[n][0] = age;
            ptr[n][1] = gender;
            ptr[n][2] = vote;
            n++;
        }
    }while(fgetc(fp) != EOF);


    //κλήση συναρτήσεων ταξινόμησης , δημιουργείας πίνακα υποψηφίων και εύρεσης max
    bubble_sort(ptr,n);
    candidates_table(cand,ptr,n);
    max_search(cand);
    histograms(cand);

    for(i = 0;i < pl ;i++)
        free(ptr[i]);
    free(ptr);
}




// óõíÜñôçóç ðïõ õðïëïãéæåß ìåóþ ôùí ðñþôùí 2 øçöéþí ôïõ äåêáåîáäéêïõ áñéèìïý ôçí çëéêßá ôïõ øçöïöüñïõ
int age_converter(char first_hex, char second_hex){
    //first_hex áíáðáñáóôÜ ôï ðñþôï øçößï ôïõ 16äéêïõ, second_hex áíáðáñáóôÜ ôï äåýôåñï øçößï ôïõ 16äéêïý
    unsigned short int first1_hex, second2_hex;
    first1_hex = hex_conv(first_hex);
    second2_hex = hex_conv(second_hex);

    second2_hex = second2_hex >> 1;


    int r;//remainder ôïõ ÷/2
    int sum = 0;//áðïèçêåýåé ôçí çëéêßá
    int i;
    for (i = 0; i <= 2; i++) {
        r = second2_hex % 2;
        //printf("r1 is %d ",r);
        second2_hex = second2_hex / 2;
        //printf("hex1 is %d",second2_hex);
        if(r == 1) {
            sum = sum + pow(2, i);
            //printf("sum1 is %d\n",sum);
        }
    }


    for (i = 3; i <= 6; i++) {
        r = first1_hex % 2;
        //printf("r2 is %d ",r);
        first1_hex = first1_hex / 2;
        //printf("hex2 is %d ",second2_hex);
        if (r == 1) {
            sum = sum + pow(2, i);
            //printf("sum2 is %d\n",sum);
        }
    }

    return sum;
}

// óõíÜñôçóç ðïõ ìåôáôñÝðåé ôá bit ðïõ áíôéðñïóùðÝõïõí ôïí öýëï óôïí áíôéóïß÷ï áñéèìü
int gender_converter(char second_hex,char third_hex) {
    //printf("second hex digit: %c, third hex digit: %c\n",second_hex,third_hex);
    unsigned short int second2_hex, third3_hex;

    //êÜíåé isolate ôï ôåëåõôáßï ìðéô ôïõ äåýôåñïõ øçößïõ ôïõ äåêáåîáäéêïý
    second2_hex = hex_conv(second_hex);
    second2_hex = second2_hex & 0x0001;
    if (second2_hex == 1) {
        second2_hex = 2;
    }


    //êÜíåé isolate ôï ðñþôï ìðéô ôïõ 3ïý øçößïõ ôïõ äåêáåîáäéêïý
    third3_hex = hex_conv(third_hex);
    third3_hex = third3_hex >> 3;
    //printf("third3 is : %x\n",third3_hex);
    if (third3_hex == 1) {
        third3_hex = 1;
    }


    return second2_hex + third3_hex;
}

int vote_converter(char third_hex, char fourth_hex) {
    unsigned short int fourth4_hex, third3_hex;//temp1 = fourth , temp2 = third
    fourth4_hex = hex_conv(fourth_hex);
    int consec = 0;
    int r,i, index;
    for( i = 0; i <= 3; i++) {
        r = fourth4_hex % 2;
        fourth4_hex = fourth4_hex / 2;
        if (r == 1) {
            consec = consec + 1;
            index = i;
            if (consec > 1) {
                index = -1;
                break;
            }
        }

    }
    third3_hex = hex_conv(third_hex);
    if (index != -1) {
        third3_hex = third3_hex & 0x0111;
        for ( i = 4; i <= 6; i++) {
            r = third3_hex % 2;
            third3_hex = third3_hex / 2;
            if (r == 1) {
                consec = consec + 1;
                index = i;
                //printf("consec %d\n", consec);
                if (consec > 1) {
                    index = -1;
                    break;
                }
            }
        }
    }
    if(consec == 0){//σε περίπτωση που ο ψηφοφόρος δεν ψηφίσει τπτ
        return -2;
    }
    return index;
}


unsigned short int hex_conv(char c) {
    unsigned short int hex;
    switch (c) {
        case '0':
            hex = 0x0;
            break;
        case '1':
            hex = 0x1;
            break;
        case '2':
            hex = 0x2;
            break;
        case '3':
            hex = 0x3;
            break;
        case '4':
            hex = 0x4;
            break;
        case '5':
            hex = 0x5;
            break;
        case '6':
            hex = 0x6;
            break;
        case '7':
            hex = 0x7;
            break;
        case '8':
            hex = 0x8;
            break;
        case '9':
            hex = 0x9;
            break;
        case 'A' | 'a':
            hex = 0xA;
            break;
        case 'B' | 'b':
            hex = 0xB;
            break;
        case 'C' | 'c':
            hex = 0xC;
            break;
        case 'D' | 'd':
            hex = 0xD;
            break;
        case 'E' | 'e':
            hex = 0xE;
            break;
        case 'F' | 'f':
            hex = 0xF;
            break;
    }

    return hex;
}

void bubble_sort(int** ptr,int n){
    int i,j,temp1,temp2,temp3;
    for(i = 1;i <= n; i++){
        for(j = n; j >= i; j--){
            if(ptr[j-1][3] > ptr[j][3]){
                temp3 = ptr[j-1][3];
                ptr[j-1][3] = ptr[j][3];
                ptr[j][3] = temp3;

                temp2 = ptr[j-1][2];
                ptr[j-1][2] = ptr[j][2];
                ptr[j][2] = temp2;

                temp1 = ptr[j-1][1];
                ptr[j-1][1] = ptr[j][1];
                ptr[j][1] = temp1;
            }
        }
    }
}

void candidates_table(unsigned int cand[6][3],int** ptr,int n) {
    printf("in function\n");
    int i,j;

    //μηδενισμός πίνακα
    for(i = 0; i <= 6; i++){
        for( j = 0; j < 3; j++){
            cand[i][j] = 0;
        }
    }

    for (i = 0; i < n; i++){
        cand[ptr[i][2]] [ptr[i][1]]++;
    }

    for(i = 0; i<= 6;i++){
        for( j = 0; j < 3;j++){
            printf("cand[%d][%d] = %d |",i,j,cand[i][j]);
        }
        printf("\n");
    }
}

void max_search(unsigned int cand[NUM_CANDIDATES][3]){
    unsigned int max,index[3],gmax,gindex;
    int i,j;
    printf("\n");
    for( j = 0;j < 3;j++){
        for(i = 0; i < 7;i++){
            //printf("cand[%d][%d] = %d\n",i,j,cand[i][j]);
            if(i == 0){
                max = cand[i][j];
                index[j] = i;
            }
            else if(cand[i][j] > max){
                max = cand[i][j];
                index[j] = i;
            }
        }
    }
    for(i = 0;i < 7;i++){
        if(i == 0){
            gmax = cand[i][0] + cand[i][1]+ cand[i][2];
            gindex = i;
        }
        else{
            if((cand[i][0] + cand[i][1]+ cand[i][2]) > gmax){
                gmax =  cand[i][0] + cand[i][1]+ cand[i][2];
                gindex = i;
            }
        }
    }
    printf("Candites with most votes in total : %d\n",gindex + 1);
    for(i = 0;i < 3;i++){
        if(i == 0){
            printf("Candidate with most votes from men : %d\n",index[i] + 1);
        }
        else if(i == 1){
            printf("Canditate with most votes from women : %d\n",index[i] + 1);
        }
        else{
            printf("Canditate with most votes from Allo: %d\n",index[i] + 1);
        }
    }
    printf("\n");
}

void histograms(unsigned int cand[NUM_CANDIDATES][3]){
    int i,j,k;
    printf("Histogram based on gender : \n");
    for(j = 0;j < 3;j++) {
        if (j == 0) {
            printf("Men :\n");
            for (i = 0; i < 6; i++) {
                printf("%d. ", i);
                for (k = 0; k < cand[i][j]; k++) {
                    printf("*");
                }
                printf("\n");
            }
        } else if (j == 1) {
            printf("Women :\n");
            for (i = 0; i < 6; i++) {
                printf("%d. ", i);
                for (k = 0; k < cand[i][j]; k++) {
                    printf("*");
                }
                printf("\n");
            }
        } else if (j == 2) {
            printf("Allo :\n");
            for (i = 0; i < 6; i++) {
                printf("%d. ", i);
                for (k = 0; k < cand[i][j]; k++) {
                    printf("*");
                }
                printf("\n");
            }
        }
    }
        printf("\n\n");
        printf("Histogram based on total votes : ");
        for (i = 0; i < 6; i++) {
            printf("\n");
            printf("%d. ", i + 1);
            for (j = 0; j < cand[i][0] + cand[i][1] + cand[i][2]; j++) {
                printf("*");
            }
        }
    }


int number_of_hex_series(void){
    int sum = 0,i;
    char c;
    FILE * fp;
    fp = fopen("C:/Users/mario/OneDrive/Desktop/writeup.dat","r");
    for(i = 0;(c = fgetc(fp)) != EOF; i++ ){
       if(c == '\n') sum++;
    }

    printf("sum is %d\n",sum + 1);
    return sum + 1;
}