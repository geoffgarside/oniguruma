#ifndef _RB_ONIGURUMA_H_
#define _RB_ONIGURUMA_H_

#include "ruby.h"
#include <oniguruma.h>

RUBY_EXTERN VALUE og_mOniguruma;

void Init_oniguruma();

OnigEncodingType* og_oniguruma_oregexp_extract_encoding(VALUE encoding);
OnigSyntaxType* og_oniguruma_extract_syntax(VALUE syntax);

#endif /* _RB_ONIGURUMA_H_ */
