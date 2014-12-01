struct _(T){
  int size;
  int next;
  _eT_  elements[_SIZE_];
};
typedef struct _T_ _T_;

#define FIFO_INIT {0,0}

void _(init)   (_T_* f);
_eT_ _(dequeue)(_T_* f);
void _(enqueue)(_T_* f, _eT_ element);
int _(size)  (_T_* f);
