#include "rb_oniguruma.h"
#include "rb_oniguruma_oregexp.h"
#include "rb_oniguruma_string_ext.h"

void
Init_oniguruma_string_ext()
{
  /*               Class       Method     Handler Function              Args */
  rb_define_method(rb_cString, "ogsub",   og_oniguruma_string_ogsub,      -1);
  rb_define_method(rb_cString, "ogsub!",  og_oniguruma_string_ogsub_bang, -1);
  rb_define_method(rb_cString, "osub",    og_oniguruma_string_osub,       -1);
  rb_define_method(rb_cString, "osub!",   og_oniguruma_string_osub_bang,  -1);
}

static VALUE
og_oniguruma_string_ogsub(int argc, VALUE *argv, VALUE self)
{
  VALUE args, re, oregexp, oregexp_argv[2];
  
  rb_scan_args(argc, argv, "0*", &args);
  
  /* Get the regular expression and make our initialization argv */
  re = rb_ary_shift(args);
  oregexp_argv[0] = re;
  oregexp_argv[1] = (VALUE)NULL;
  
  args = rb_ary_unshift(args, self);
  
  oregexp = rb_class_new_instance(1, oregexp_argv, og_cOniguruma_ORegexp);
  return rb_funcall3(oregexp, rb_intern("gsub"), RARRAY(args)->len, RARRAY(args)->ptr);
}

static VALUE
og_oniguruma_string_ogsub_bang(int argc, VALUE *argv, VALUE self)
{
  VALUE args, re, oregexp, oregexp_argv[2];
  
  rb_scan_args(argc, argv, "0*", &args);
  
  /* Get the regular expression and make our initialization argv */
  re = rb_ary_shift(args);
  oregexp_argv[0] = re;
  oregexp_argv[1] = (VALUE)NULL;
  
  args = rb_ary_unshift(args, self);
  
  oregexp = rb_class_new_instance(1, oregexp_argv, og_cOniguruma_ORegexp);
  return rb_funcall3(oregexp, rb_intern("gsub"), (int)RARRAY(args)->len, RARRAY(args)->ptr);
}

static VALUE
og_oniguruma_string_osub(int argc, VALUE *argv, VALUE self)
{
  VALUE re, args, oregexp, oregexp_argv[2];
  
  rb_scan_args(argc, argv, "1*", &re, &args);
  
  oregexp_argv[0] = re;
  oregexp_argv[1] = (VALUE)NULL;
  
  args = rb_ary_unshift(args, self);
  
  oregexp = rb_class_new_instance(1, oregexp_argv, og_cOniguruma_ORegexp);
  return rb_funcall3(oregexp, rb_intern("sub"), (int)RARRAY(args)->len, RARRAY(args)->ptr);
}

static VALUE
og_oniguruma_string_osub_bang(int argc, VALUE *argv, VALUE self)
{
  VALUE re, args, oregexp, oregexp_argv[2];
  
  rb_scan_args(argc, argv, "1*", &re, &args);
  
  oregexp_argv[0] = re;
  oregexp_argv[1] = (VALUE)NULL;
  
  args = rb_ary_unshift(args, self);
  
  oregexp = rb_class_new_instance(1, oregexp_argv, og_cOniguruma_ORegexp);
  return rb_funcall3(oregexp, rb_intern("sub!"), (int)RARRAY(args)->len, RARRAY(args)->ptr);
}
