#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_CANDIDATES 7

//Äçëþóåéò óõíáñôÞóåùí
int number_of_hex_series(void);
int age_converter(char,char);
int gender_converter(char,char);
int vote_converter(char,char);
unsigned short int hex_conv(char c);

void candidates_table(unsigned int cand[NUM_CANDIDATES][3] ,int **,int);
void bubble_sort(int**,int);
void max_search(unsigned int cand[NUM_CANDIDATES][3]);
void histograms(unsigned int cand[NUM_CANDIDATES][3]);
void age_group_gap(int**,int);
void print_age_of_voters(int age_of_voters[NUM_CANDIDATES][4]);


int main(void){
    unsigned int cand[NUM_CANDIDATES][3];
    int age_of_voters[NUM_CANDIDATES][4] = {0};
    int age,gender,vote,i,n = 0,pl,**ptr,invalid = 0;
    char c[5];
    c[4] = '\0';

    //Üíïéãìá áñ÷åßïõ
    FILE * fp;
    fp = fopen("C:/Users/mario/OneDrive/Desktop/votes.dat","r");
    if(fp == NULL) exit(10);
    pl = number_of_hex_series();

    //ÄõíáìéêÞ äÝóìåõóç ðßíáêá ßóç ìå ôïõò øçöïöüñïõò
    ptr = (int**)malloc(pl * sizeof(int*));
    if(fp == NULL) exit(10);
    for(i = 0;i < pl;i++){
        ptr[i] = (int*)malloc(3 * sizeof(int));
    }

    //åîáãùãÞ hex êáé áðïêùäéêïðïßçóç ôçò çëéêßáò ôùí øçöïöüñùí ìå ôçí âïçèåßá ôùí óõíáñôÞóåùí age , gender ,vote êáé Ýëåã÷ïò Ýãêõñùí óôïé÷åßùí øçöïöüñùí
    do{
        for(i = 1;i <= 4;i++){
            c[i] = fgetc(fp);
        }
        age = age_converter(c[1],c[2]);
        gender = gender_converter(c[2],c[3]);
        vote = vote_converter(c[3], c[4]);

        //Ýëåã÷ïò Ýãêõñçò øÞöïõ
        if((age >= 18 && age <= 99) && (gender >= 1 && gender <= 3) && ((vote >= 0 && vote <= 6) || vote == -2)){
            //äçìéïõñãåßá ðßíáêá çëéêáêþí ïìÜäùí øÞöùí êÜèå øçöïöüñïõ
            if(vote != -2) {
                if ( age <= 29) {
                    age_of_voters[vote][0]++;
                } else if (age <= 44) {
                    age_of_voters[vote][1]++;
                } else if (age <= 59) {
                    age_of_voters[vote][2]++;
                } else {
                    age_of_voters[vote][3]++;
                }
            }
            //åê÷þñçóç óôïí ðßíáêá ôùí øçöïöüñùí ôá äåäïìÝíá ôïõò åöüóïí åßíáé Ýãêõñá
            ptr[n][0] = age;
            ptr[n][1] = gender;
            ptr[n][2] = vote;
            n++;
        }
        else{
            invalid++;//óýíïëï Üêõñùí øÞöùí
        }
    }while(fgetc(fp) != EOF);


    //êëÞóç óõíáñôÞóåùí ôáîéíüìçóçò , äçìéïõñãåßáò ðßíáêá õðïøçößùí , åýñåóçò max , éóôïãñáììáôþí êáé óõêñßóçò ãéá  max íÝùí êáé max çëéêéùìÝíùí
    bubble_sort(ptr,n); printf("Invalid votes : %d\n\n",invalid);
    candidates_table(cand,ptr,n);
    max_search(cand);
    histograms(cand);
    age_group_gap(ptr,n);

    //áðåëåõèÝñùóç ìíÞìçò
    for(i = 0;i < pl ;i++)
        free(ptr[i]);
    free(ptr);
}




//ÓõíÜñôóç ìåôáôñïðÞò çëéêßáò øçöïöüñïõ
int age_converter(char first_hex, char second_hex){
    //first hex : ðñþôï øçößï äåêáåîáäéêïý , second hex : äåýôåñï øçößï äåêáåîáäéêïý
    unsigned short int first1_hex, second2_hex;
    first1_hex = hex_conv(first_hex);
    second2_hex = hex_conv(second_hex);

    second2_hex = second2_hex >> 1;

    //r : õðüëïéðï ðñÜîçò , sum : óïýìá çëéêßáò
    int r;
    int sum = 0;
    int i;
    for (i = 0; i <= 2; i++) {
        r = second2_hex % 2;
        second2_hex = second2_hex / 2;
        if(r == 1) {
            sum = sum + pow(2, i);
        }
    }


    for (i = 3; i <= 6; i++) {
        r = first1_hex % 2;
        first1_hex = first1_hex / 2;
        if (r == 1) {
            sum = sum + pow(2, i);
        }
    }

    return sum;
}

//ÓõíÜñôçóç ìåôáôñïðÞò öýëëïõ
int gender_converter(char second_hex,char third_hex) {
    //second2_hex : 2ïò äåêáåîáäéêüò , third3_hex : 3ïò äåêáåîáäéêüò
    unsigned short int second2_hex, third3_hex;

    second2_hex = hex_conv(second_hex);
    second2_hex = second2_hex & 0x0001;
    if (second2_hex == 1) {
        second2_hex = 2;
    }
    third3_hex = hex_conv(third_hex);
    third3_hex = third3_hex >> 3;
    if (third3_hex == 1) {
        third3_hex = 1;
    }


    return second2_hex + third3_hex;
}

//ÓõíÜñôçóç ìåôáôñïðÞò øÞöïõ
int vote_converter(char third_hex, char fourth_hex) {
    //fourth4_hex : 4ïò äåêáåîáäéêüò , third3_hex : 3ïò äåêáåîáäéêüò
    unsigned short int fourth4_hex, third3_hex;
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
                if (consec > 1) {
                    index = -1;
                    break;
                }
            }
        }
    }
    if(consec == 0){
        // Ç óõíÜñôçóç åðéóôñÝöåé -2 óå ðåñßðôùóç ðïõ ï øçöïöüñïò äåí Ý÷åé øçößóåé êÜðïéïí õðïøÞöéï
        return -2;
    }
    return index;
}

//ÓõíÜñôçóç ìåôáôñïðÞò ôùí ÷áñáêôÞñùí óå hex
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

//ÓõíÜñôçóç ðïõ ôáîéíïìåß ìå bubble sort
void bubble_sort(int** ptr,int n){
    int i,j,temp1,temp2,temp3;
    for(i = 1;i < n; i++){
        for(j = n; j >= i; j--){
            if(ptr[j-1][2] > ptr[j][2]){
                temp3 = ptr[j-1][2];
                ptr[j-1][2] = ptr[j][2];
                ptr[j][2] = temp3;

                temp2 = ptr[j-1][1];
                ptr[j-1][1] = ptr[j][1];
                ptr[j][1] = temp2;

                temp1 = ptr[j-1][0];
                ptr[j-1][0] = ptr[j][0];
                ptr[j][0] = temp1;
            }
        }
    }
    printf("Voters information :\n\n");
    for(i = 0;i < n;i++){
        printf("Voter number %d : \n",i);
        for(j = 0;j < 3;j++){
            if(j == 0){
                printf("age : %d\n",ptr[i][j]);
            }
            if(j == 1){
                printf("gender : %d\n",ptr[i][j]);
            }
            if(j == 2)
                printf("vote : %d\n",ptr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//ÓõíÜñôçóç äçìéïõñãåßáò ðßíáêá õðïøçößùí ìå âÜóç ôçí çëéêßá
void candidates_table(unsigned int cand[6][3],int** ptr,int n) {
    int i,j;
    printf("Candidates information based on gender voters :");

    //ìçäåíéóìüò ðßíáêá
    for(i = 0; i < 7; i++){
        for( j = 0; j < 3; j++){
            cand[i][j] = 0;
        }
    }

    for (i = 0; i < n; i++){
        cand[ptr[i][2]] [ptr[i][1]]++;
    }

    for(j = 0; j < 3;j++){
        for( i = 0; i < 7;i++){
            if(j == 0) printf("Candidate number %d got %d votes from men\n",i,cand[i][j]);
            else if(j == 1) printf("Candidate number %d got %d votes from women\n",i,cand[i][j]);
            else if(j = 2) printf("Candidate number %d got %d votes from allo\n",i,cand[i][j]);
        }
        printf("\n");
    }
}

//ÓõíÜñôçóç åýñåóçò max
void max_search(unsigned int cand[NUM_CANDIDATES][3]){
    unsigned int max,index[3],gmax,gindex;
    int i,j;
    printf("\n");
    for( j = 0;j < 3;j++){
        for(i = 0; i < 7;i++){
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
    printf("Candidate with most votes in total : Candidate number %d\n",gindex + 1);
    for(i = 0;i < 3;i++){
        if(i == 0){
            printf("Candidate with most votes from men : Candidate number %d\n",index[i] + 1);
        }
        else if(i == 1){
            printf("Canditate with most votes from women : Candidate number %d\n",index[i] + 1);
        }
        else{
            printf("Canditate with most votes from Allo : Candidate number %d\n",index[i] + 1);
        }
    }
    printf("\n");
}

//ÓõíÜñôçóç ðïõ äçìéïõñãåß ôá éóôïãñÜììáôá
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
    printf("\n\n");
}

//ÓõíÜñôçóç ðïõ õðïëïãßæåé êáé åðéóôñÝöåé ðüóåò óåéñÝò áðï hex õðÜñ÷ïõí óôï êþäéêá ìåôñüíôáò ôá '\n' êáé ðñïóèÝôïíôáò 1
int number_of_hex_series(void){
    int sum = 0,i;
    char c;
    FILE * fp;
    fp = fopen("C:/Users/mario/OneDrive/Desktop/votes.dat","r");
    for(i = 0;(c = fgetc(fp)) != EOF; i++ ){
        if(c == '\n') sum++;
    }

    //printf("sum is %d\n",sum + 1);
    return sum + 1;
}

//ÓõíÜñôçóç ðïõ âñßóêåé ðïéüí øÞöéóåé ðåñéóóüôåñï ç íåïëáßá êáé ðïéïí ïé ðéï ìåãÜëïé
void age_group_gap(int**ptr,int n){
    //maxn ðßíáêáò ìå øÞöïõò êÜèå õðïøÞöéïõ íåïëÝáò , maxo ðßíáêáò ìå øÞöïõò êÜèå õðïøÞöéïõ ìåãáëÞò çëéêßáò
    //maxne ôï index ìå ôïí õðïøÞöéï ìå ðåñéóóüôåñåò øÞöïõò áðï ôçí íåïëÝá êáé áíôßóôïé÷á ôï maxol  ãéá ôïõò ìåáãëýôåñïõò
    int maxn[7] = {0},maxo[7] = {0},maxne = -1,maxol = -1,i,j;
    for(i = 0; i < n; i++){
        if(ptr[i][0] <= 30){
            maxn[ptr[i][2]]++;
        }
        if(ptr[i][0] >= 60){
            if(ptr[i][2] != -2){
                maxo[ptr[i][2]]++;
            }
        }
    }

    for(i = 0;i < 7;i++){
        if(maxn[i] > maxne){
            maxne = i;
        }
        if(maxo[i] > maxol){
            maxol = i;
        }
    }
    printf("Candidate with most votes from young voters : %d\n",maxne);
    printf("Candidate with most votes from elder voters : %d\n",maxol);
}