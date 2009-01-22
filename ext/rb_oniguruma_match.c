#include "rb_oniguruma_match.h"

static VALUE
og_oniguruma_oregexp_match_alloc()
{
  NEWOBJ(match, struct RMatch);
  OBJSETUP(match, rb_cMatch, T_MATCH);
  
  match->str = 0;
  match->regs = 0;
  match->regs = ALLOC(struct re_registers);
  MEMZERO(match->regs, struct re_registers, 1);
  
  return (VALUE)match;
}

VALUE
og_oniguruma_match_initialize(OnigRegion *region, VALUE string)
{
  int i;
  VALUE match = og_oniguruma_oregexp_match_alloc();
  
  RMATCH(match)->str = rb_str_new4(string);
  
  RMATCH(match)->regs->num_regs = region->num_regs;
  RMATCH(match)->regs->allocated = region->num_regs;
  
  RMATCH(match)->regs->beg = ALLOC_N(int, region->num_regs);
  RMATCH(match)->regs->end = ALLOC_N(int, region->num_regs);
  
  for (i = 0; i < region->num_regs; i++) {
    RMATCH(match)->regs->beg[i] = region->beg[i];
    RMATCH(match)->regs->end[i] = region->end[i];
  }
  
  return match;
}

int
og_oniguruma_name_callback(OG_CALLBACK_UCHAR *name, OG_CALLBACK_UCHAR *name_end,
  int ngroup_num, int *group_nums, regex_t *reg, void *magic)
{
  int i;
  VALUE hash;
  og_CallbackPacket * arg = (og_CallbackPacket*)magic;
  
  hash = arg->hash;

  for (i = 0; i < ngroup_num; i++)
    rb_hash_aset(hash, ID2SYM(rb_intern((char*)name)), INT2FIX(group_nums[i]));
    
  return 0;
}
