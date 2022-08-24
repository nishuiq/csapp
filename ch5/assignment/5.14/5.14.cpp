#include <iostream>

void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for (i = 0; i < length - 5; i ++) {
        sum = sum + udata[i] * vdata[i] +
            udata[i+1] * vdata[i+1] +
            udata[i+2] * vdata[i+2] +
            udata[i+3] * vdata[i+3] +
            udata[i+4] * vdata[i+4] +
            udata[i+5] * vdata[i+5];
    }
    for (; i < length; i ++) {
        sum = sum + udata[i] * vdata[i];
    }
    *dest = sum;
}

Ref:https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter5/5.14/
  sum                            i
   |                             |
   v                             |
 [add]<------[mul]<-[load]<------+
   |                             |
   v                             |
 [add]<------[mul]<-[load]<------+
   |                             |
   v                             |
 [add]<------[mul]<-[load]<------+
   |                             |
   v                             |
 [add]<------[mul]<-[load]<------+
   |                             |
   v                             |
 [add]<------[mul]<-[load]<------+
   |                             |
   v                             |
 [add]<------[mul]<-[load]<------+
   |                             |
   |                             v
   |                           [add]
   |  <------ key path           |
   |                             |
   v                             v
  sum                            i

A.
    关键路径add 6n/6 = n，不会超过 1

B.
    与A.同理