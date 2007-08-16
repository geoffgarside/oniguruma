#ifndef _RB_ONIGURUMA_H_
#define _RB_ONIGURUMA_H_

#include <ruby.h>
#include <oniguruma.h>

RUBY_EXTERN VALUE og_mOniguruma;

void Init_oniguruma();
void Init_oniguruma_string_ext();
void Init_oniguruma_match_data_ext();

OnigEncodingType* og_oniguruma_extract_encoding(VALUE encoding);
OnigSyntaxType* og_oniguruma_extract_syntax(VALUE syntax);

#endif /* _RB_ONIGURUMA_H_ */
