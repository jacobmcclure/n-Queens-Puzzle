//-------------------------------------------------------------
// Jacob McClure
//
// Queens.c
//
// C program that uses recursion to find all solutions 
// to the n-Queens problem
//-------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

// function prototypes
void placeQueen(int** B, int n, int i, int j);

void removeQueen(int** B, int n, int i, int j);

void printBoard(int** B, int n);

int findSolutions(int** B, int n, int i, char* mode);

// Place a queen on the board:
void placeQueen(int** B, int n, int i, int j){
   B[i][0] = j;
   B[i][j] += 1;
   int i1;
   int j1 = j+1;

   // diagonal right
   for (i1 = i+1; i1 < n+1; i1++){
      if (j1<n+1){
         B[i1][j1] -= 1;
         j1++;
      }
   }
   i1 = i + 1;
   j1 = j;

   // straight down 
   for (i1 = i + 1; i1 < n+1; i1++){  
      B[i1][j1] -= 1;
   }
   i1 = i + 1;
   j1 = j - 1;

   // diagonal left
   for (i1 = i+1; i1 < n+1; i1++){  
      if (j1 > 0){
         B[i1][j1] -= 1;
         j1--;
      }
   }
}

// function def for remove queen
void removeQueen(int** B, int n, int i, int j){
   B[i][0] = 0;
   B[i][j] -= 1;
   int i1;
   int j1 = j+1;

   // diagonal right
   for (i1 = i+1; i1<n+1; i1++){ 
      if (j1<n+1){
         B[i1][j1] += 1;
         j1++;
      }
   }
   i1 = i + 1;
   j1 = j;


   // straight down 
   for (i1 = i + 1; i1<n+1; i1++){ 
      B[i1][j1] += 1;
   }
   i1 = i + 1;
   j1 = j - 1;

   // diagonal left
   for (i1 = i+1; i1<n+1; i1++){ 
      if (j1 > 0){
         B[i1][j1] += 1;
         j1--;
      }
   }
}

// function def for print board
void printBoard(int** B, int n){
   printf("(");
   int c = 1;

   // using c to prevent redundant commas
   for (int i = 1; i<n+1; i++) {
      if(c) { 
         c = 0;
      }
      else {
         printf(", ");
      }
      printf("%d", B[i][0]);
   }
   printf(")\n");
}

// function def for find solutions
int findSolutions(int** B, int n, int i, char* mode){
   int sum = 0;
   if (i>n){ 
      // if we are in verbose mode, print board
      if (strcmp(mode, "verbose") == 0){
         printBoard(B, n);
      }
      return 1;
   }

   // if in normal mode, place, add recursively, remove
   else {
      for (int j=1; j<=n; j++){
         if (B[i][j] == 0){
            placeQueen(B, n, i, j);
            sum += findSolutions(B, n, i+1, mode);
            removeQueen(B, n, i, j);
         }
      }
   }
   return sum;
}

// function def for main
int main(int argc, char* argv[]){
   int** B; // create a reference that points to B pointer 
   int n;
   int i =1;
   char ch;
   int status;
   char* mode; // pointer for mode
   int sum = 0;
   
   // if there are 3 CL args...
   if ((argc == 3)){
      status = sscanf(argv[2], "%d%c", &n, &ch);  // scan contents of value at n
      if (status==1){       
         if ((n<1) || (n>15)){
            printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
            exit(EXIT_FAILURE);
         }
         if ((strcmp(argv[1], "-v") == 0) && (isdigit(*(argv[2])))){ // are we in verbose mode?
            mode = "verbose";
           // n = atoi(argv[2]);
         }
      }
      else { // if there are 3 CL args but we aren't in verbose mode, print usage message
         printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
         exit(EXIT_FAILURE);
      }
   }

   if ((argc == 2)){   // normal mode
      status = sscanf(argv[1], "%d%c", &n, &ch);  // scan contents of value at n
      if (status==1){
         if ((n<1) || (n>15)){
            printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
            exit(EXIT_FAILURE);
         }
      }
      if(status != 1) { // if incorrect input in normal mode format, print usage statement
         printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
         exit(EXIT_FAILURE);
      }
   }

   // if user enters only 1 CLA, print usage statement and exit
   if (argc == 1){
      printf("Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");
      exit(EXIT_FAILURE);
   }
   // allocate 2D array, B, in heap memory
   B = malloc((n+1)*sizeof(int*));
   for (int k=1; k<n+1; k++){ // initialize B to all 0's
      B[k] = calloc((n+1), sizeof(int));
   }

   sum = findSolutions(B, n, i, mode); // set sum equal to findSolutions of CL args
   if (sum == 1){ // if there is 1 queen...
      printf("%d-Queens has %d solution\n", n, sum);
   }
   
   else{ // if there are more than 1 queens...
      printf("%d-Queens has %d solutions\n", n, sum);
   }
   
   for (int k=1; k<n+1; k++){ // initialize B to all 0's
     free(B[k]);
   }
   free(B);
}