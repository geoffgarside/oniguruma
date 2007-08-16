#include <ruby.h>
#include "rb_oniguruma_core_ext.h"

static VALUE
og_oniguruma_match_data_to_index(VALUE self, VALUE sym)
{
  VALUE named_captures = rb_iv_get(self, "@named_captures");
  
  if (!NIL_P(named_captures))
    return rb_hash_aref(named_captures, sym);
  return Qnil;
}

static VALUE
og_oniguruma_match_data_aref(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_data_to_index(self, first);
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
og_oniguruma_match_data_begin(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_data_to_index(self, first);
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
og_oniguruma_match_data_end(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_data_to_index(self, first);
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
og_oniguruma_match_data_offset(int argc, VALUE *argv, VALUE self)
{
  VALUE idx, first, k, nargv[2];
  
  rb_scan_args(argc, argv, "0*", &idx);
  
  first = rb_ary_entry(idx, 0);
  if (SYMBOL_P(first)) {
    k = og_oniguruma_match_data_to_index(self, first);
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

void
Init_oniguruma_match_data_ext()
{
  /* Alias Existing Methods */
  /*              Class      New Name                   Original Name */
  rb_define_alias(rb_cMatch, "aref_without_oniguruma",    "[]");
  rb_define_alias(rb_cMatch, "begin_without_oniguruma",   "begin");
  rb_define_alias(rb_cMatch, "end_without_oniguruma",     "end");
  rb_define_alias(rb_cMatch, "offset_without_oniguruma",  "offset");
  
  /* Define the replacements */
  /*               Class      Method      Handler Function                  Args */
  rb_define_method(rb_cMatch, "to_index", og_oniguruma_match_data_to_index,    1);
  rb_define_method(rb_cMatch, "[]",       og_oniguruma_match_data_aref,       -1);
  rb_define_method(rb_cMatch, "begin",    og_oniguruma_match_data_begin,      -1);
  rb_define_method(rb_cMatch, "end",      og_oniguruma_match_data_end,        -1);
  rb_define_method(rb_cMatch, "offset",   og_oniguruma_match_data_offset,     -1);
}
