#define og_DefineConstantNames VALUE og_mOniguruma, og_cOniguruma_ORegexp
#define og_ObtainConstants do {                                               \
  og_mOniguruma = rb_const_get(rb_cObject, rb_intern("Oniguruma"));           \
  og_cOniguruma_ORegexp = rb_const_get(og_mOniguruma, rb_intern("ORegexp"));  \
} while(0);
