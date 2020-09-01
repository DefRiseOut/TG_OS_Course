#include <stdio.h>
struct node {
    int value;
    struct node* next;
};
struct List {
    struct node* header;
    int size;
};



void insert_node(struct List *list, int index, int val){
    if(index == 0 || list->size == 0){
        struct node new_node;
        new_node.value = val;
        if(index < list->size) new_node.next = list->header;
        list->header = &new_node;
        list->size++;
    }
    else{
        struct node *now_p = (list->header);
        for(int i = 0; i<list->size-1;i++){
            if(i==index-1) break;
            now_p = now_p->next;
        }
        struct node new_node;
        new_node.value = val;
        if(index < list->size) new_node.next = now_p->next;
        now_p->next = &new_node;
        list->size++;
    } 
}

void print_list(struct List *list){
    struct node *now_p = list->header;
    printf("%d\n",list->header->value);
    printf("%d\n",list->header->next->value);
    for(int i = 0; i < list->size;i++){
        printf("%d%c",(now_p->value),' ');
        now_p = now_p->next;
    }
}

int main(){
    struct List list;
    list.size = 0;
    insert_node(&list, 0, 5);
    insert_node(&list, 1, 6);
    print_list(&list);
}