#include <ruby.h>
#include "rb_oniguruma_ext.h"

static VALUE
og_oniguruma_match_to_index(VALUE self, VALUE sym)
{
  VALUE named_captures = rb_iv_get(self, "@named_captures");
  
  if (!NIL_P(named_captures))
    return rb_hash_aref(named_captures, sym);
  return Qnil;
}

static VALUE
og_oniguruma_match_aref(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_to_index(self, first);
    if (!NIL_P(k)) {
      nargv[0] = k;
      nargv[1] = (VALUE)NULL;
      
      return rb_funcall3(self, rb_intern("aref_without_oniguruma"), 1, nargv);
    } else
      return Qnil;
  }
  
  return rb_funcall3(self, rb_intern("aref_without_oniguruma"), RARRAY(idx)->len, RARRAY(idx)->ptr);
}

static VALUE
og_oniguruma_match_begin(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_to_index(self, first);
    if (!NIL_P(k)) {
      nargv[0] = k;
      nargv[1] = (VALUE)NULL;
      
      return rb_funcall3(self, rb_intern("begin_without_oniguruma"), 1, nargv);
    } else
      return Qnil;
  } else if (RARRAY(idx)->len == 0) {
    nargv[0] = INT2FIX(0);
    nargv[1] = (VALUE)NULL;
    
    return rb_funcall3(self, rb_intern("begin_without_oniguruma"), 1, nargv);
  }
  
  return rb_funcall3(self, rb_intern("begin_without_oniguruma"), RARRAY(idx)->len, RARRAY(idx)->ptr);
}

static VALUE
og_oniguruma_match_end(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_to_index(self, first);
    if (!NIL_P(k)) {
      nargv[0] = k;
      nargv[1] = (VALUE)NULL;
      
      return rb_funcall3(self, rb_intern("end_without_oniguruma"), 1, nargv);
    } else
      return Qnil;
  } else if (RARRAY(idx)->len == 0) {
    nargv[0] = INT2FIX(0);
    nargv[1] = (VALUE)NULL;
    
    return rb_funcall3(self, rb_intern("end_without_oniguruma"), 1, nargv);
  }
  
  return rb_funcall3(self, rb_intern("end_without_oniguruma"), RARRAY(idx)->len, RARRAY(idx)->ptr);
}

static VALUE
og_oniguruma_match_offset(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_to_index(self, first);
    if (!NIL_P(k)) {
      nargv[0] = k;
      nargv[1] = (VALUE)NULL;
      
      return rb_funcall3(self, rb_intern("offset_without_oniguruma"), 1, nargv);
    } else
      return Qnil;
  } else if (RARRAY(idx)->len == 0) {
    nargv[0] = INT2FIX(0);
    nargv[1] = (VALUE)NULL;
    
    return rb_funcall3(self, rb_intern("offset_without_oniguruma"), 1, nargv);
  }
  
  return rb_funcall3(self, rb_intern("offset_without_oniguruma"), RARRAY(idx)->len, RARRAY(idx)->ptr);
}

#define alias_method_chain(obj, meth, with) do {      \
  rb_define_alias(obj, meth "_without_" with, meth);  \
  rb_define_alias(obj, meth, meth "_with_" with);     \
} while(0)

static VALUE
og_oniguruma_match_included(VALUE base)
{
  // Alias [] to aref, so we can replace it better
  rb_define_alias(base, "aref", "[]");
  
  alias_method_chain(base, "aref",    "oniguruma");
  alias_method_chain(base, "begin",   "oniguruma");
  alias_method_chain(base, "end",     "oniguruma");
  alias_method_chain(base, "offset",  "oniguruma");
  
  return base;
}

void
og_oniguruma_match_ext(VALUE og_mOniguruma_Extensions)
{
  VALUE og_mMatch = 
    rb_define_module_under(og_mOniguruma_Extensions, "Match");
  
  rb_define_singleton_method(og_mMatch, "included", og_oniguruma_match_included, 1);
  
  /* Define the replacements */
  /*               Class      Method                     Handler Function             Args */
  rb_define_method(og_mMatch, "to_index",                og_oniguruma_match_to_index,    1);
  rb_define_method(og_mMatch, "aref_with_oniguruma",     og_oniguruma_match_aref,       -1);
  rb_define_method(og_mMatch, "begin_with_oniguruma",    og_oniguruma_match_begin,      -1);
  rb_define_method(og_mMatch, "end_with_oniguruma",      og_oniguruma_match_end,        -1);
  rb_define_method(og_mMatch, "offset_with_oniguruma",   og_oniguruma_match_offset,     -1);
  
  rb_include_module(rb_cMatch, og_mMatch);
}
