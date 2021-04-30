#include <stdio.h>
#include <stdlib.h>

////////////// Creating single Node ///////////////////
struct node {
    int data;
    struct node *link;

};

int main (){
    struct node *head = NULL;
    head = (struct node*)malloc(sizeof(struct node));

    head->data = 45;
    head->link = NULL;
    

    printf("%d", head->data);
    
}

////////////// Creating Multiple Node ///////////////////

struct node{
    int value;
    struct node* next;
};

typedef struct node node_t;

void printlist(node_t *head){
    node_t *temporary = head;
    
    while(temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
};

int main(){
    node_t n1, n2, n3;
    node_t *head;
    
    n1.value = 45;
    n2.value = 8;
    n3.value = 32;
    
    // link them up
    head = &n3;
    n3.next = &n2;
    n2.next = &n1;
    n1.next = NULL; // so we know when to stop
    
    printlist(head);
}

////////////// Inserting Node ///////////////////

struct node {
    int data;
    struct node *link;
};

void add_at_end(struct node *head, int data){
    struct node *ptr, *temp;
    ptr = head;
    temp = (struct node*)malloc(sizeof(struct node));

    temp->data = data;
    temp->link = NULL;

    while(ptr->link != NULL){
        ptr = ptr->link;
    }
    ptr->link = temp;
}

struct node *add_beg(struct node *head, int d){
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = d;
    ptr->link = NULL;

    ptr->link = head;
    head = ptr;
    return head;
}

int main(){
    struct node *head = malloc(sizeof(struct node));
    head->data = 45;
    head->link = NULL;

    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = 98;
    ptr->link = NULL;

    head->link = ptr;
    int data = 3;

    head = add_beg(head, data);
    ptr = head;
    add_at_end(head, 67);
    while(ptr != NULL){
        printf("%d - ", ptr->data);
        ptr = ptr->link;
    }

}