#include <ruby.h>
#include "rb_oniguruma_ext.h"

/*
 * Document-method: to_index
 *
 * call-seq:
 *    to_index[symbol]      => int or nil
 *
 * Returns the group index for the corresponding named group, or
 * <code>nil</code> if the group does not exist.
 *
 *    m = ORegexp.new( '(?<begin>^.*?)(?<middle>\d)(?<end>.*)' ).match("THX1138")
 *    m.to_index[:begin]    #=> 1
 *    m.to_index[:unknown]  #=> nil
 */
static VALUE
og_oniguruma_match_to_index(VALUE self, VALUE sym)
{
  VALUE named_captures = rb_iv_get(self, "@named_captures");
  
  if (!NIL_P(named_captures))
    return rb_hash_aref(named_captures, sym);
  return Qnil;
}

/*
 * Document-method: []
 *
 * call-seq:
 *    mtch[i]               => obj
 *    mtch[start, length]   => array
 *    mtch[range]           => array
 *    mtch[symbol]          => obj
 *
 * <code>MatchData</code> acts as an array, and may be
 * accessed using the normal array indexing techniques.  <i>mtch</i>[0] is
 * equivalent to the special variable <code>$&</code>, and returns the entire
 * matched string.  <i>mtch</i>[1], <i>mtch</i>[2], and so on return the values
 * of the matched backreferences (portions of the pattern between parentheses).
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m[0]       #=> "HX1138"
 *    m[1, 2]    #=> ["H", "X"]
 *    m[1..3]    #=> ["H", "X", "113"]
 *    m[-3, 2]   #=> ["X", "113"]
 *
 * If a symbol is used as index, the corresponding named group is returned,
 * or <code>nil</code> if such a group does not exist.
 *
 *    m = ORegexp.new( '(?<begin>^.*?)(?<middle>\d)(?<end>.*)' ).match("THX1138")
 *    m[:begin]  #=> "THX"
 *    m[:moddle]  #=> "1"
 *    m[:end]  #=> "138"
 */
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

/*
 * Document-method: begin
 *
 * call-seq:
 *    mtch.begin(n)        => integer
 *    mtch.begin           => integer
 *    mtch.begin(symbol)   => integer
 *
 * Returns the offset of the start of the <em>n</em>th element of the match
 * array in the string.
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m.begin(0)   #=> 1
 *    m.begin(2)   #=> 2
 *
 * If no arguments are given, the index of the
 * first matching character is returned.
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m.begin      #=> 1
 *
 * If the argument is a symbol, then the beginning of the
 * corresponding named group is returned, or <code>nil</code>
 * if the group does not exist.
 *
 *    m = ORegexp.new( '(?<begin>^.*?)(?<middle>\d)(?<end>.*)' ).match("THX1138")
 *    m.begin(:middle) #=> 3
 */
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

/*
 * Document-method: end
 *
 * call-seq:
 *    mtch.end(n)   => integer
 *
 * Returns the offset of the character immediately following the end of the
 * <em>n</em>th element of the match array in the string.
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m.end(0)   #=> 7
 *    m.end(2)   #=> 3
 *
 * If no arguments are given, the index of the
 * last matching character is returned.
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m.last      #=> 7
 *
 * If the argument is a symbol, then the beginning of the
 * corresponding named group is returned, or <code>nil</code>
 * if the group does not exist.
 *
 *    m = ORegexp.new( '(?<begin>^.*?)(?<middle>\d)(?<end>.*)' ).match("THX1138")
 *    m.end(:middle) #=> 4
 */
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

/*
 * Document-method: offset
 *
 * call-seq:
 *    mtch.offset(n)      => array
 *    mtch.offset         => array
 *    mtch.offset(symbol) => array
 *
 * Returns a two-element array containing the beginning and ending offsets of
 * the <em>n</em>th match.
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m.offset(0)   #=> [1, 7]
 *    m.offset(4)   #=> [6, 7]
 *
 * If no arguments are given, the offsets of the entire
 * sequence are returned.
 *
 *    m = ORegexp.new( '(.)(.)(\d+)(\d)' ).match("THX1138.")
 *    m.offset      #=> [1, 7]
 *
 * If the argument is a symbol, then the offsets of the
 * corresponding named group are returned, or <code>nil</code>
 * if the group does not exist.
 *
 *    m = ORegexp.new( '(?<begin>^.*?)(?<middle>\d)(?<end>.*)' ).match("THX1138")
 *    m.end(:middle) #=> [3, 4]
 */
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
og_oniguruma_match_included(VALUE self, VALUE base)
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
  VALUE og_mMatch, iargv[2];
  
  og_mMatch = rb_define_module_under(og_mOniguruma_Extensions, "Match");
  rb_define_singleton_method(og_mMatch, "included", og_oniguruma_match_included, 1);
  
  /* Define the replacements */
  /*               Class      Method                     Handler Function             Args */
  rb_define_method(og_mMatch, "to_index",                og_oniguruma_match_to_index,    1);
  rb_define_method(og_mMatch, "aref_with_oniguruma",     og_oniguruma_match_aref,       -1);
  rb_define_method(og_mMatch, "begin_with_oniguruma",    og_oniguruma_match_begin,      -1);
  rb_define_method(og_mMatch, "end_with_oniguruma",      og_oniguruma_match_end,        -1);
  rb_define_method(og_mMatch, "offset_with_oniguruma",   og_oniguruma_match_offset,     -1);
  
  iargv[0] = og_mMatch;
  iargv[1] = (VALUE)NULL;
  
  rb_funcall2(rb_cMatch, rb_intern("include"), 1, iargv);
}
