#include <stdio.h>

//I don't know what I'm doing :(

struct _ArrayList{
    int size;
    void ** data;
};
struct _ArrayList *ArrayList_Create(){

}
int getSize(struct _ArrayList *list){
    return list->size;
}
void clearArrayList(struct ArrayList *list){
    list->size = 0;
    free(list->data);
    list-> = NULL;
}

