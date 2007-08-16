#ifndef _RB_ONIGURUMA_MATCH_H_
#define _RB_ONIGURUMA_MATCH_H_

#include "ruby.h"
#include <oniguruma.h>  /* for struct re_registers */

/* Cannot include re.h due to typedef conflicts */
struct RMatch {
    struct RBasic basic;
    VALUE str;
    struct re_registers *regs;
};

#define RMATCH(obj)  (R_CAST(RMatch)(obj))

void rb_match_busy _((VALUE));

typedef struct og_callback_packet {
    VALUE hash;
    OnigRegion * region;
} og_CallbackPacket;

/* Our Match methods */
static VALUE og_oniguruma_oregexp_match_alloc();
static VALUE og_oniguruma_oregexp_match_initialize();

/* Oniguruma foreach callback */
static int og_oniguruma_name_callback(const UChar *name, const UChar *name_end, 
  int ngroup_num, int *group_nums, regex_t *reg, struct callback_packet *arg);

#endif /* _RB_ONIGURUMA_MATCH_H_ */
