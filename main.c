#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_CANDIDATES 7

//Äçëþóåéò óõíáñôÞóåùí
int age_converter(char,char);
int gender_converter(char,char);
int vote_converter(char,char);
unsigned short int hex_conv(char c);

void candidates_table(unsigned int cand[NUM_CANDIDATES][3] ,int **,int);
void max_search(unsigned int cand[NUM_CANDIDATES][3]);
void histograms(unsigned int cand[NUM_CANDIDATES][3]);
void age_group_gap(int**,int);
void print_age_of_voters(int age_of_voters[NUM_CANDIDATES][4]);
void list_append(int age,int gender,int vote);
void list_to_table(int**,int);



struct node{
    int age;
    int vote;
    int gender;
    struct node *next;
} *list_head;
typedef struct node node_s;
void bubble_sort1(void);

int main(void){
    unsigned int cand[NUM_CANDIDATES][3];
    int age_of_voters[NUM_CANDIDATES][4] = {0};
    int age,gender,vote,i,n = 0,**ptr,invalid = 0;
    char c[5];
    c[4] = '\0';

    //áíÜèåóç ôéìÞò null óôï head ôçò ëßóôáò
    list_head = NULL;

    //Üíïéãìá áñ÷åßïõ
    FILE * fp;
    fp = fopen("C:/Users/mario/OneDrive/Desktop/votes.dat","r");
    if(fp == NULL) exit(10);

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
            n++; //Áñéèìüò Ýãêõñùí øÞöùí
            list_append(age,gender,vote); //ÄõíáìéêÞ êáôá÷þñçóç ðëçñïöñïñéþí óôçí ëßóôá
        }
        else{
            invalid++;//óýíïëï Üêõñùí øÞöùí
        }
    }while(fgetc(fp) != EOF);

    //ÄõíáìéêÞ äÝóìåõóç ðßíáêá
    ptr = (int**)malloc(n * sizeof(int*));
    if(fp == NULL) exit(10);
    for(i = 0;i < n;i++){
        ptr[i] = (int*)malloc(3 * sizeof(int));
    }

    bubble_sort1();

    node_s *p;
    p = list_head;
    for(i = 0;p != NULL;i++){
        ptr[i][0] = p ->age;
        ptr[i][1] = p ->gender;
        ptr[i][2] = p ->vote;
        p = p -> next;
    }
    for(i = 0;i < n;i++){
        printf("Age is %d , Gender is %d , Vote is %d\n",ptr[i][0],ptr[i][1],ptr[i][2]);
    }


    //êëÞóç óõíáñôÞóåùí ôáîéíüìçóçò , äçìéïõñãåßáò ðßíáêá õðïøçößùí , åýñåóçò max , éóôïãñáììáôþí êáé óõêñßóçò ãéá  max íÝùí êáé max çëéêéùìÝíùí
    //list_to_table(ptr,n);
    candidates_table(cand,ptr,n);
    max_search(cand);
    histograms(cand);
    age_group_gap(ptr,n);

    //áðåëåõèÝñùóç ìíÞìçò
    for(i = 0;i < n ;i++)
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
            else  printf("Candidate number %d got %d votes from allo\n",i,cand[i][j]);
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
                printf("%d|", i);
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
        printf("%d|", i + 1);
        for (j = 0; j < cand[i][0] + cand[i][1] + cand[i][2]; j++) {
            printf("*");
        }
    }
    printf("\n\n");
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

void list_append(int age,int gender, int vote){
    node_s *neos;
    neos = malloc(sizeof(struct node));
    neos -> age = age;
    neos -> vote = vote;
    neos -> gender = gender;
    neos -> next = list_head;
    list_head = neos;
}


/*void list_to_table(int** ptr,int n){
	int i,j;

	node_s *p;
	p = list_head;
		for(i = 0;p != NULL;i++){
			printf("i is: %d\n",i);
			ptr[i][0] = p ->age;
			ptr[i][1] = p ->gender;
			ptr[i][2] = p ->vote;
		}
		for(i = 0;i < n;i++){
			printf("Age is %d :",ptr[i][0]);
			}
}*/

void bubble_sort1(void){
    int swapped,temp1,temp2,temp3;
    node_s *ptr1;
    node_s *lptr = NULL;
    if(list_head == NULL) exit(10);
    do {
        swapped = 0;
        ptr1 = list_head;

        while (ptr1->next != lptr) {
            if (ptr1->vote > ptr1->next->vote) {
                temp1 = ptr1->vote;
                ptr1->vote = ptr1->next->vote;
                ptr1->next->vote = temp1;

                temp2 = ptr1->age;
                ptr1->age = ptr1->next->age;
                ptr1->next->age = temp2;

                temp3 = ptr1->gender;
                ptr1->gender = ptr1->next->gender;
                ptr1->next->gender = temp3;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}