#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int age_converter(char,char);
int gender_converter(char,char);
int vote_converter(char,char);
unsigned short int hex_conv(char c);

int main() {
    int age,gender,vote,valid_votes,i,**p,j;
    char c[5],c1;
    c[5] = '\0';

    //ανοίγμα αρχείου ψηφοφόρων
    FILE * fp;
    fp = fopen("C:/Users/mario/OneDrive/Desktop/writeup.dat","r");


    do{
        for(i = 1;i <= 4;i++){
            c[i] = fgetc(fp);
        }
        //χρήση συνάρτησης η οποία λαμβάνει ως ορίσματα τα πρώτα 2 ψηφία του δεκαεξαδικού και τα μετατρέπει σε ηλικία
        age = age_converter(c[1],c[2]);

        //χρήση συνάρτησης για μετατροπή του γένους απο το 8ό και το 9ό μπιτ
        gender = gender_converter(c[2],c[3]);

        //χρήση συνάρτησης η οποια λαμβάνει ώς όρισμα το τρίτο και τέταρτο ψηφίο ενος δεκαεξαδικού και το μετατρέπει στην ψήφο του ψηφοφόρου
        vote = vote_converter(c[3], c[4]);
        printf("%d vote,%d age,%d gender\n",vote,age,gender);

        if((age >= 18 && age <= 99) && (gender >= 1 && gender <= 3) && (vote >= 1 && vote <= 6)){
            printf("This voters vote is valid!\n");
            valid_votes++;

        }
    }while(c1 = fgetc(fp) != EOF);

    //δήλωση πίνακα πληροφορίων ψηφοφόρων
    p = calloc(3,sizeof(int*));
    for(j = 0; j < 3; j++){
        p[j] = calloc(valid_votes, sizeof(int));
    }
}


// συνάρτηση που υπολογιζεί μεσώ των πρώτων 2 ψηφιών του δεκαεξαδικου αριθμού την ηλικία του ψηφοφόρου
    int age_converter(char first_hex, char second_hex){
        //first_hex αναπαραστά το πρώτο ψηφίο του 16δικου, second_hex αναπαραστά το δεύτερο ψηφίο του 16δικού
       unsigned short int first1_hex, second2_hex;
       first1_hex = hex_conv(first_hex);
       second2_hex = hex_conv(second_hex);

       second2_hex = second2_hex >> 1;


        int r;//remainder του χ/2
        int sum = 0;//αποθηκεύει την ηλικία
        for (int i = 0; i <= 2; i++) {
            r = second2_hex % 2;
            second2_hex = second_hex / 2;
            if (r == 1) {
                sum = sum + pow(2, i);
            }
        }

        for (int i = 3; i <= 6; i++) {
            r = first1_hex % 2;
            first1_hex = first1_hex / 2;
            if (r == 1) {
                sum = sum + pow(2, i);
            }
        }
        return sum;
    }

    // συνάρτηση που μετατρέπει τα bit που αντιπροσωπέυουν τον φύλο στον αντισοίχο αριθμό
    int gender_converter(char second_hex,char third_hex) {
        //printf("second hex digit: %c, third hex digit: %c\n",second_hex,third_hex);
        unsigned short int second2_hex, third3_hex;

        //κάνει isolate το τελευταίο μπιτ του δεύτερου ψηφίου του δεκαεξαδικού
        second2_hex = hex_conv(second_hex);
        second2_hex = second2_hex & 0x0001;
        if (second2_hex == 1) {
            second2_hex = 2;
        }


        //κάνει isolate το πρώτο μπιτ του 3ού ψηφίου του δεκαεξαδικού
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
        int r, index;
        for (int i = 0; i <= 3; i++) {
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
            for (int i = 4; i <= 6; i++) {
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
