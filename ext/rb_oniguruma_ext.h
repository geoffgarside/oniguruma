#ifndef _RB_ONIGURUMA_EXT_H_
#define _RB_ONIGURUMA_EXT_H_

#include <ruby.h>
#include "rb_oniguruma.h"

#define og_DefineConstantNames VALUE og_mOniguruma, og_cOniguruma_ORegexp
#define og_ObtainConstants do {                                                 \
  og_mOniguruma = rb_const_get(rb_cObject, rb_intern(OG_M_ONIGURUMA));          \
  og_cOniguruma_ORegexp = rb_const_get(og_mOniguruma, rb_intern(OG_C_OREGEXP)); \
} while(0);

#endif /* _RB_ONIGURUMA_EXT_H_ */
