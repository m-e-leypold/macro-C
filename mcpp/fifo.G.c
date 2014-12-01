#include <assert.h>

int _size_  (_T_* f){
  return f->size;
}

void _init_ (_T_* f){
  f->size = 0;
  f->next = 0;
}

void _enqueue_ (_T_* f, _eT_ element){
  f->size = (f->size + 1);
  assert(f->size<=_SIZE_);
  f->elements[f->next] = element;
  f->next = (f->next+1) % _SIZE_;
}

_eT_ _dequeue_ (_T_* f){
  assert(f->size>0);
  int index = ((f->next)-(f->size)) % _SIZE_;
  f->size--;
  return f->elements[index];
}

