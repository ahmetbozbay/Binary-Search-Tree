#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 

struct node {
    char *value;            
    struct node *p_left;
    struct node *p_right;
};

typedef int (*Check)(const char *, const char *);
	
void insertingdata(char* key, struct node** subRoot, Check match)
{
    int res;
    if( *subRoot == NULL ) {
        *subRoot = (struct node*) malloc( sizeof( struct node ) );
        (*subRoot)->value = malloc( strlen (key) +1 );    
        strcpy ((*subRoot)->value, key);                  
        (*subRoot)->p_left = NULL;
        (*subRoot)->p_right = NULL;
        printf(  "\n inserting and new node for %s" , key);
    } else {
        res = match (key, (*subRoot)->value);
        if( res < 0)
            insertingdata( key, &(*subRoot)->p_left, match);
        else
            insertingdata( key, &(*subRoot)->p_right, match);
    }
}
int matchString(const char *value1, const char *value2)
{
    return (strcmp (value1, value2)); 
}
void inorder(struct node *Root)
{
    if( Root != NULL ) {
        inorder(Root->p_left);
        printf("--   %s   --\n", Root->value);
        inorder(Root->p_right);
    }
}
void menu()
{
	printf("\n\n***************Binary Search Tree***************\n");
    printf("\nPress the letter 'p' to view the In order Tree.\n");
    printf("\nPress the letter 'c' to calculate the cost of Total Access time Tree.\n");
    printf("\nPress the letter 'e' to exit\n");
}
int sum(int freq[], int i, int j);  
int optCost(int freq[], int i, int j) 
{ 
   if (j < i)  
     return 0; 
   if (j == i)     
     return freq[i]; 
   int fsum = sum(freq, i, j); 
   int min = INT_MAX; 
   int r;
   for (r = i; r <= j; ++r) 
   { 
       int cost = optCost(freq, i, r-1) +  
                  optCost(freq, r+1, j); 
       if (cost < min) 
          min = cost; 
   } 
   return min + fsum; 
} 
int optimalSearchTree(int keys[], int freq[], int n) 
{ 
	return optCost(freq, 0, n-1); 
} 
int sum(int freq[], int i, int j) 
{ 
    int s = 0; 
    int k;
    for (k = i; k <=j; k++) 
       s += freq[k]; 
    return s; 
} 
int main()
{
    struct node *p_Root = NULL;
    char *value;
    char option = 'a';
    FILE* fp;
    char  line[255];
    fp = fopen("input.txt" , "r");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char val1[20] ,key[20];
        char *pos;
        if ((pos=strchr(line, '\n')) != NULL)
            *pos = '\0';
        strcpy(val1 , strtok(line,","));
        strcpy(key , strtok(NULL,","));
        insertingdata(key,  &p_Root, (Check)matchString);  
    }
    while( option != 'e' ) {
        menu();
        option = getch();           
        if( option == 'p' ) {
            inorder(p_Root);
        }        
        else if( option == 'c' ) 
		{
		printf("\nStarted to calculate Cost of Optimal Binary Search Tree.\n");
        int keys[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50}; 
		int freq[] = {6,10,15,2,1,28,35,62,4,89,3,7,16,27,50,60,70,83,46,44,49,51,56,54,22,33,100,201,92,94,97,93,64,65,61,19,13,14,26,88,99,205,300,74,77,76,41,42,43,75}; 
    	int n = sizeof(keys)/sizeof(keys[0]); 
    	printf("Cost of Optimal Binary Search Tree is %d ",  
               optimalSearchTree(keys, freq, n)); 
        }
        else if( option == 'e' ) {
            printf("Quitted..\nGood Bye ;)");
            exit(0);
        }
    }
return 0;
}
