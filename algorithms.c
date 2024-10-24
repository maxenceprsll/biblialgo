#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void array_create(struct array *self) {
  self->data=NULL;
  self->size=0;
}

void array_create_from(struct array *self, const int *other, size_t size) {
  self->size=size;
  self->data=malloc(size);
  for(size_t i=0;i<size;i++){
    self->data[i]=other[i];
  }
}

void array_destroy(struct array *self) {
  free(self->data);
    self->data=NULL;
  self->size=0;
}

bool array_empty(const struct array *self) {
  return self->data==NULL;
}

size_t array_size(const struct array *self) {
  return self->size;
}

//////////////////////////////////
void array_print(const struct array *self){
  printf("[");
  for(size_t i=0;i<self->size;i++){
    printf(" %d ",self->data[i]);
  }
  printf("]");
}
//////////////////////////////////

bool array_equals(const struct array *self, const int *content, size_t size) {
  if(self->size!=size){
    return false;
  }
  for(size_t i=0;i<size;i++){
    if(self->data[i]!=content[i]){
      return false;
    }
  }
  return true;
}


void array_push_back(struct array *self, int value) {
  int *data=calloc(self->size+1,sizeof(int));
  for(size_t i=0;i<self->size;i++){
    data[i]=self->data[i];
  }
  data[self->size]=value;
  free(self->data);
  self->data=data;
  self->size++;
}

void array_pop_back(struct array *self) {
  if(self->size<2){
    array_destroy(self);
  }else{
    self->size--;
  }
}

void array_insert(struct array *self, int value, size_t index) {
  array_push_back(self,0);
  for(size_t i=self->size-1;i>index;--i){
    self->data[i]=self->data[i-1];
  }
  self->data[index]=value;
}

void array_remove(struct array *self, size_t index) {
  for(size_t i=index;i<self->size-1;i++){
    self->data[i]=self->data[i+1];
  }
  array_pop_back(self);
}

int array_get(const struct array *self, size_t index) {
  if(index<self->size){
    return self->data[index];
  }
  return 0;
}

void array_set(struct array *self, size_t index, int value) {
  if(index>=0&&index<self->size){
    self->data[index]=value;
  }
}

size_t array_search(const struct array *self, int value) {
  for(size_t i=0;i<self->size;i++){
    if(self->data[i]==value){
      return i;
    }
  }
  return self->size;
}


size_t array_search_sorted(const struct array *self, int value) {
  for(size_t i=0;i<self->size;i++){
    if(self->data[i]>value){
      return self->size;
    } else if(self->data[i]==value){
      return i;
    }
  }
  return self->size;
}

bool array_is_sorted(const struct array *self) {
  for(size_t i=0;i+1<self->size;i++){
    if(self->data[i]>self->data[i+1]){
      return false;
    }
  }
  return true;
}

void array_swap(struct array *self,size_t i,size_t j){
  int tmp=self->data[i];
  self->data[i]=self->data[j];
  self->data[j]=tmp;
}

ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
  ptrdiff_t pivot_index=i;
  const int pivot=self->data[pivot_index];
  array_swap(self,pivot_index,j);
  ptrdiff_t l=i;
  for(ptrdiff_t k=i;k<j;++k){
    if(self->data[k]<pivot){
      array_swap(self,k,l);
      ++l;
    }
  }
  array_swap(self,l,j);
  return l;
}

void array_quick_sort_partial(struct array *self,ptrdiff_t i,ptrdiff_t j){
  if(i<j){
    ptrdiff_t p=array_partition(self,i,j);
    array_quick_sort_partial(self,i,p-1);
    array_quick_sort_partial(self,p+1,j);
  }
}
void array_quick_sort(struct array *self) {
  array_quick_sort_partial(self,0,self->size-1);
}

void array_heap_sort(struct array *self) {
}

bool powerOfTwo(int n)
    {
      if(n==0){
        return false;
      }
      while(n!=1)
      {
        n/=2;
        if(n%2!=0&&n!=1){
          return false; 
        }
      }
      return true;
    }

bool array_is_heap_partial(const struct array *self,size_t i){
  if (self->size==0||i>=(self->size-1)/2){
    return true;
  }
  if(!powerOfTwo(self->size)){
    return false;
  }
  if (self->data[i]>=self->data[2*i+1]&&self->data[i]>=self->data[2*i+2]&&array_is_heap_partial(self,2*i+1)&&array_is_heap_partial(self,2*i+2)){
      return true;
  }
  return false;
}

bool array_is_heap(const struct array *self) {
  return array_is_heap_partial(self,0);
}

void array_heap_add(struct array *self, int value) {
  size_t i=self->size;
  array_push_back(self,value);
  while(i>0){
    size_t j=(i-1)/2;
    if(self->data[i]<self->data[j]){
      break;
    }
    array_swap(self,i,j);
    i=j;
  }
}

int array_heap_top(const struct array *self) {
  if(self->size>0){
    return self->data[0];
  }
  return 0;
}

void array_heap_remove_top(struct array *self) {
  array_swap(self,0,self->size-1);
  size_t i=0;
  while(i<(self->size-1)/2){
    size_t lt=2*i+1;
    size_t rt=2*i+2;
    if(self->data[i]>self->data[lt]&&self->data[i]>self->data[rt]){
      break;
    }
    size_t j=(self->data[lt]>self->data[rt])?lt:rt;
    array_swap(self,i,j);
    i=j;
  }
  array_pop_back(self);
}

/*
 * list
 */



void list_create(struct list *self) {
}

void list_create_from(struct list *self, const int *other, size_t size) {
}

void list_destroy(struct list *self) {
}

bool list_empty(const struct list *self) {
  return true;
}

size_t list_size(const struct list *self) {
  return -1;
}

bool list_equals(const struct list *self, const int *data, size_t size) {
  return false;
}

void list_push_front(struct list *self, int value) {
}

void list_pop_front(struct list *self) {
}

void list_push_back(struct list *self, int value) {
}

void list_pop_back(struct list *self) {
}


void list_insert(struct list *self, int value, size_t index) {
}


void list_remove(struct list *self, size_t index) {
}

int list_get(const struct list *self, size_t index) {
  return 42;
}

void list_set(struct list *self, size_t index, int value) {
}

size_t list_search(const struct list *self, int value) {
  return -1;
}

bool list_is_sorted(const struct list *self) {
  return false;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
}

void list_merge(struct list *self, struct list *in1, struct list *in2) {
}

void list_merge_sort(struct list *self) {
}


/*
 * tree
 */

void tree_create(struct tree *self) {
}


void tree_destroy(struct tree *self) {
}


bool tree_contains(const struct tree *self, int value) {
  return false;
}


bool tree_insert(struct tree *self, int value) {
  return false;
}


bool tree_remove(struct tree *self, int value) {
  return false;
}

bool tree_empty(const struct tree *self) {
  return true;
}


size_t tree_size(const struct tree *self) {
  return -1;
}


size_t tree_height(const struct tree *self) {
  return -1;
}


void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {
}

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
}
