#ifndef _RB_ONIGURUMA_MATCH_H_
#define _RB_ONIGURUMA_MATCH_H_

#include <ruby.h>
#include <oniguruma.h>  /* for struct re_registers and OnigRegion */

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
VALUE og_oniguruma_oregexp_match_initialize();

/* Oniguruma foreach callback */
int og_oniguruma_name_callback(UChar *name, UChar *name_end, 
  int ngroup_num, int *group_nums, regex_t *reg, void *magic);

#endif /* _RB_ONIGURUMA_MATCH_H_ */
