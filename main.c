#include <stdio.h>
#include <math.h>

int age_converter(unsigned short int);
int gender_converter(unsigned short int hexadecimal);
int vote_converter(unsigned short int hexadecimal);

int main() {
    unsigned short temp1, temp2;
    int age, gender, vote, number_of_voters;
    unsigned short int hexadecimal;
    do {

        scanf("%x", &hexadecimal);
        /* χρήση συναρτήσεων για μετατροπή ηλικίας , φύλλου και ψήφου (οι απομωνώσεις των υπόλοιπων μπιτ γίνονται μέσα σε καθεμία απο αυτές αντίστοιχα)*/
        age = age_converter(hexadecimal);
        gender = gender_converter(hexadecimal);
        vote = vote_converter(hexadecimal);


    } while ((age < 18 || age > 99) || (gender < 1 || gender > 3) || (vote < 1 || vote > 6)); //συνθήκη τερματισμού ελέγχου εγκυρότητας
    printf("Given age is %d\n", age);
    printf("Given gender is %d", gender);

}

    // συνάρτηση που μετατρέπει τον δεκαξαδικό σε ηλικία μορφής ακεραίου
    int age_converter(unsigned short int hexadecimal){
        unsigned short int prwta_4,deftera_3;

        prwta_4 = (hexadecimal >> 12);
        deftera_3 = (hexadecimal >> 8) & 0x0f;
        deftera_3 = (deftera_3 >> 1);


        //η deftera_3 μεταφέρει τα 3 επομενα των πρώτων 4 bit ενώ η  prwta_4 τα πρώτα 4

        int r;//remainder του χ/2
        int sum = 0;//αποθηκεύει την ηλικία
        for (int i = 0; i <= 2; i++) {
            r = deftera_3 % 2;
            deftera_3 = deftera_3 / 2;
            if (r == 1) {
                sum = sum + pow(2, i);
            }
        }

        for (int i = 3; i <= 6; i++) {
            r = prwta_4 % 2;
            prwta_4 = prwta_4 / 2;
            if (r == 1) {
                sum = sum + pow(2, i);
            }
        }
        return sum;
    }

    // συνάρτηση που μετατρέπει τα bit που αντιπροσωπέυουν τον φύλο στον αντισοίχο αριθμό
    int gender_converter(unsigned short int hexadecimal) {
        /* κάνει isolate το τελευταίο bit του δεύτερου 16δικού*/
        unsigned short int temp1, temp2;
        temp1 = (hexadecimal >> 8) & 0x0f;
        temp1 = temp1 & 0x0001;
        if (temp1 == 1) {
            temp1 = 2;
        }

        temp2 = (hexadecimal >> 4) & 0x00f;
        temp2 = temp2 >> 3;
        if (temp2 == 1) {
            temp2 = 1;
        }

        return temp1 + temp2;
    }

    int vote_converter(unsigned short int hexadecimal) {
        unsigned short int temp1, temp2;
        temp1 = hexadecimal & 0x000f;
        int consec = 0;
        int r, index;
        for (int i = 0; i <= 3; i++) {
            r = temp1 % 2;
            temp1 = temp1 / 2;
            if (r == 1) {
                consec = consec + 1;
                index = i;
                if (consec > 1) {
                    index = -1;
                    break;
                }
            }

        }
        if (index != -1) {
            temp2 = hexadecimal >> 4 & 0x00f;
            temp2 = temp2 & 0x0111;
            for (int i = 4; i <= 6; i++) {
                r = temp2 % 2;
                temp2 = temp2 / 2;
                if (r == 1) {
                    consec = consec + 1;
                    index = i;
                    printf("consec %d\n", consec);
                    if (consec > 1) {
                        index = -1;
                        break;
                    }
                }
            }
        }
        printf("%d index is at\n", index);
        return index;
    }