#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 40
//struct for node
struct node {
    char *value;            // all void* types replaced by char*
    struct node *p_left;
    struct node *p_right;
};

//use typedef to make calling the Check function easier
typedef int (*Check)(const char *, const char *);

//insertingdatas elements into the tree
void insertingdata(char* key, struct node** subRoot, Check match)
{
    int res;
    int tobt;
    if( *subRoot == NULL ) {
        *subRoot = (struct node*) malloc( sizeof( struct node ) );
        (*subRoot)->value = malloc( strlen (key) +1 );     // memory for key
        strcpy ((*subRoot)->value, key);                   // copy the key
        (*subRoot)->p_left = NULL;
        (*subRoot)->p_right = NULL;
        //printf(  "\nnew node for %s" , key);
    } else {
    	tobt=+1;
        res = match (key, (*subRoot)->value);
        if( tobt%2 == 0)
            insertingdata( key, &(*subRoot)->p_left, match);
        else if ( tobt%2 == 1)
            insertingdata( key, &(*subRoot)->p_right, match);
    }
}

//Checks value of the new node against the previous node
int matchString(const char *value1, const char *value2)
{
    return (strcmp (value1, value2));     // string comparison instead of pointer comparison
}
//recursive function to print out the tree inorder
void inorder(struct node *Root)
{
    if( Root != NULL ) {
        inorder(Root->p_left);
        printf("-- %s -- \n", Root->value);     // string type
        inorder(Root->p_right);
    }
}
void search(char* key, struct node* subRoot, Check match)  // no need for **
{
    int res;
    if( subRoot != NULL ) {
        res = match(key, subRoot->value);
        if( res < 0)
            search( key, subRoot->p_left, match);
        else if( res > 0)
            search( key, subRoot->p_right, match);
        else
            printf("\n'%s' found!\n", key);     // string type
    }
    else printf("\nNot in tree\n");
    return;
}
char *input( void )
{
    static char line[MAXLEN+1];       // where to place key    
    printf("Please enter a string : ");
    fgets( line, sizeof line, stdin );
    return ( strtok(line, "\n" ));    // remove trailing newline
}
//displays menu for user
void menu()
{	printf("***************Binary Tree***************\n");
    printf("Press the letter 'p' to view the In order Tree.\n");
    printf("Press the letter 's' to search element of tree.\n");
    printf("Press the letter 'e' to exit\n");
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
        char *pst;
        if ((pst=strchr(line, '\n')) != NULL)
            *pst = '\0';
        strcpy(val1 , strtok(line,","));
        strcpy(key , strtok(NULL,","));
        insertingdata(key,  &p_Root, (Check)matchString);  
    }
    while( option != 'q' ) {
        //displays menu for program
        menu();
        //gets the char input to drive menu
        option = getch();           // instead of two getchar() calls
        if( option == 'p' ) {
            inorder(p_Root);
        }
        else if( option == 'e' ) {
            printf("Quitted..\nGood Bye ;)");
            exit(0);
        }
        else if( option == 's' ) {
            value = input();
            search(value, p_Root, (Check)matchString);     // no need for **
        }
	}
	return 0;
}		
