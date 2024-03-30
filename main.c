#include <stdio.h>
#include <stdlib.h>

///P2_1190270_Nour Naji_SectionNo.2”
struct node;
typedef struct node * ptr ; /// pointer of node
typedef ptr stack ;
struct node
{
    char *input;
    ptr next ;
};
///declare the d,temp as pointer of node.
ptr temp ,d;
stack s3;
///--------------------------------------------------
/// function to creat stack
stack creatStack()
{
    ///declaration for a linked List implementation of the stack
    ///Reserve a place in memory/*dynamic memory allocation by
    ///using malloc and it  allocates memory as requested size of bytes*/
    stack s = (stack)malloc(sizeof(struct node));
    if (s == NULL)
    {
        printf("There is no place in the memory..!!");
        return NULL ;  ///the Stack s  ==  NULL when the memory is full..
    }
    else
    {
        s->next = NULL ;///Header indicates to NULL
        return s ;
    }
}
///--------------------------------------------------
/// test whether a stack is empty
int is_empty(stack s)
{
    return(s->next == NULL); ///let the next of the stack s be NULL.
}
///--------------------------------------------------
char *Top(stack s)
{
    if (is_empty(s)) /// if stack is empty
    {
        printf("stack is empty..!!");
    }
    else
    {
        ///return top ..
        return s->next->input;
    }
}
///--------------------------------------------------
void push(stack s,char *new_stack)
{

    ///Reserve a place in memory
     temp = (ptr)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        printf("out of space..!! \n");
    }
    else
    {
        ///Adding new node to the stack
        temp->input =new_stack;
        temp->next = s->next;  ///let the pointer of the next temp be same the pointer of the stack s
        s->next= temp;        ///let the next of the stack s be the temp.
    }
}
///----------------------------------------------------
void undo(stack s)
{
    ///Delete the top from the stack
    s3=creatStack();
    if (is_empty(s)) /// if stack is empty
    {
        printf("stach is empty..\n");
    }
    else
    {
        temp = s->next ;          ///let the temp be the next of the stack s.
        s->next =s->next->next;  ///let the next of stack point to the next of next of stack s.
        push(s3,temp->input);   ///Move the item from the top to stack s3.
        free(temp);            ///Delete the top /*mean free the allocated memory of this ptr*/

    }
}
///--------------------------------------------------
void Delete_top(stack s)
{
    if (!is_empty(s))         /// if stack s is not empty
    {
        d = s->next;         ///let the d be the next of the stack s.
        s->next = d->next;  ///let the next of stack point be the next of d .
    }
    else
    {
        /// if stack s is empty print stach is empty.
        printf("stach is empty..\n");
    }
}
///--------------------------------------------------
void redo(stack s )
{
    push(s, Top(s3));  ///Move the item from the top stack s3 to s2
}
///-------------------------------------------------
void print_List(stack s)
{
    stack s2=creatStack();///creat new Stack Transferring the elements from the first to the second stacks and printing them from the bottom to top
    char *ch;
    while(!is_empty(s)) /// if stack s is not empty
    {
        push(s2,Top(s)); ///Move the item from the top stack s to s2
        Delete_top(s);   /// deleat the top

    }
    while(!is_empty(s2)) /// if stack s2 is not empty
    {
        push(s,Top(s2));///Move the item from the top stack s to s2
        ch= Top(s2);
        printf("%s \n", ch);
        Delete_top(s2);

    }
}

///--------------------------------------------------
void save(stack s,char *new_stack )
{
    FILE *out;  /// creat output file
    out = fopen("output.txt","w");
    stack s2=creatStack();///creat new Stack
    char *ch;
    while(!is_empty(s))
    {
        push(s2,Top(s)); ///Move the item from the top stack s to s2
        Delete_top(s);

    }
    while(!is_empty(s2))
    {
        push(s,Top(s2));///Move the item from the top stack s2 to s
        ch= Top(s2);
        fprintf(out,"%s \n", ch); /// print to output file
        Delete_top(s2);

    }

    fclose(out); ///close output file
}
///--------------------------------------------------
int main()
{
    printf("================================================================= \n");
    printf("                      STACK OPERATION                             \n");
    printf("                        1.undo(remove)                            \n");
    printf("                        2.redo (add)                              \n");
    printf("                        3.print                                   \n");
    printf("                        4.save                                    \n");
    printf("                        5.quit                                    \n");
    printf("================================================================= \n");

    /// creat Stack
    stack s = creatStack();
    char *inp;
    printf("MyCommand > ");
    ///Reserve a place in memory
    inp = (char*)malloc((100)*sizeof(char));
    gets(inp); ///reads a line  and stores it into the string
    push(s,inp); /// //added line
    while(strcmp(inp,"quit") !=0)  ///Since the user did not enter quit
    {

        printf("MyCommand > ");
        ///Reserve a place in memory
        inp = (char*)malloc((100)*sizeof(char));
        gets(inp);
        push(s,inp);


        if(strcmp(inp,"undo")==0) ///if the user  enter undo
        {
            printf("result > \n");
            Delete_top(s);
            undo(s);
            print_List(s);

        }
        else if(strcmp(inp,"redo")==0) ///if the user  enter redo
        {
            printf("result > \n");
            Delete_top(s);
            redo(s);
            print_List(s);
        }
        else if(strcmp(inp,"print")==0) ///if the user  enter print
        {
            printf("result > \n");
            Delete_top(s);
            print_List(s);
        }
        else if(strcmp(inp,"save")==0) ///if the user  enter save
        {
            printf("result > \n");
            Delete_top(s);
            save(s,inp);
        }
        else if(strcmp(inp,"quit")==0) ///if the user  enter quit
        {
            printf("result > Good Bye!");
            Delete_top(s);
            save(s,inp);
            exit(0); ///Exit the program
        }
    }

    return 0;
}
