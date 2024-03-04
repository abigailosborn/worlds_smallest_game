#include <stdio.h>

//I don't know what I'm doing :(

// Optionally, you could typedef this so that you don't have to keep writing "struct" in front of it
struct _ArrayList{
    // You also should have a `capacity` field, so you know when you have to reallocate
    int size;
    // Pointer to pointer? Hmm... It should only be a single pointer
    void ** data;
};
// It's fine to return a pointer to the object
// you're initializing, but ask yourself if that
// is necessary. If possible, try to avoid using
// pointers! They are an evil menace.
struct _ArrayList *ArrayList_Create(){

}
int getSize(struct _ArrayList *list){
    return list->size;
}

void clearArrayList(struct ArrayList *list){
    list->size = 0;
    // Depending on how you're storing your
    // data, you may need to also individually
    // free each element of your data. If you
    // just store your data directly in the
    // array, rather than storing pointers,
    // then you can just free the array (unless
    // those elements are holding live pointers
    // themselves. In that case, you'll still
    // have to free those pointers.
    free(list->data);
    // What?
    list-> = NULL;
}

void *Arraylist_get(struct _ArrayList *list, int index){
    // What?
    return list*data[index];
}


