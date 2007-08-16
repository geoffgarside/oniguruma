#include "rb_oniguruma.h"
#include "rb_oniguruma_oregexp.h"
#include "rb_oniguruma_match.h"

static inline void og_oniguruma_str_mod_check(VALUE s, char *p, long len)
{
  if (RSTRING(s)->ptr != p || RSTRING(s)->len != len)
    rb_raise(rb_eRuntimeError, "string modified");
}

static void og_oniguruma_oregexp_free(void *arg);
static VALUE og_oniguruma_oregexp_alloc(VALUE klass);

void
Init_oniguruma_oregexp()
{
  VALUE og_cOniguruma_ORegexp_Singleton;
  
  og_cOniguruma_ORegexp = rb_define_class_under(og_mOniguruma, "ORegexp", rb_cObject);
  rb_define_alloc_func(og_cOniguruma_ORegexp, og_oniguruma_oregexp_alloc);
  
  /* Now add the methods to the class */
  rb_define_singleton_method(og_cOniguruma_ORegexp, "escape",     og_oniguruma_oregexp_escape,      -1);
  rb_define_singleton_method(og_cOniguruma_ORegexp, "last_match", og_oniguruma_oregexp_last_match,  -1);
  
  /* Define Instance Methods */
  rb_define_method(og_cOniguruma_ORegexp, "initialize", og_oniguruma_oregexp_initialize,            -1);
  rb_define_method(og_cOniguruma_ORegexp, "match",      og_oniguruma_oregexp_match,                 -1);
  rb_define_method(og_cOniguruma_ORegexp, "=~",         og_oniguruma_oregexp_operator_match,         1);
  rb_define_method(og_cOniguruma_ORegexp, "==",         og_oniguruma_oregexp_operator_equality,      1);
  rb_define_method(og_cOniguruma_ORegexp, "===",        og_oniguruma_oregexp_operator_identical,     1);
  rb_define_method(og_cOniguruma_ORegexp, "sub",        og_oniguruma_oregexp_sub,                   -1);
  rb_define_method(og_cOniguruma_ORegexp, "sub!",       og_oniguruma_oregexp_sub_bang,              -1);
  rb_define_method(og_cOniguruma_ORegexp, "gsub",       og_oniguruma_oregexp_gsub,                  -1);
  rb_define_method(og_cOniguruma_ORegexp, "gsub!",      og_oniguruma_oregexp_gsub_bang,             -1);
  rb_define_method(og_cOniguruma_ORegexp, "scan",       og_oniguruma_oregexp_scan,                   1);
  rb_define_method(og_cOniguruma_ORegexp, "casefold?",  og_oniguruma_oregexp_casefold,               0);
  rb_define_method(og_cOniguruma_ORegexp, "kcode",      og_oniguruma_oregexp_kcode,                  0);
  rb_define_method(og_cOniguruma_ORegexp, "options",    og_oniguruma_oregexp_options,                0);
  rb_define_method(og_cOniguruma_ORegexp, "source",     og_oniguruma_oregexp_source,                 0);
  rb_define_method(og_cOniguruma_ORegexp, "inspect",    og_oniguruma_oregexp_inspect,                0);
  rb_define_method(og_cOniguruma_ORegexp, "to_s",       og_oniguruma_oregexp_to_s,                   0);
  
  /* Define Aliases */
  /* Instance method aliases */
  rb_define_alias(og_cOniguruma_ORegexp, "eql?", "==");
  rb_define_alias(og_cOniguruma_ORegexp, "match_all", "scan");
  
  /* Class method aliases */
  og_cOniguruma_ORegexp_Singleton = rb_singleton_class(og_cOniguruma_ORegexp);
  rb_define_alias(og_cOniguruma_ORegexp_Singleton, "compile", "new");
  rb_define_alias(og_cOniguruma_ORegexp_Singleton, "escape", "quote");
}

/* Class Methods */
VALUE
og_oniguruma_oregexp_escape(int argc, VALUE *argv, VALUE self)
{
  return rb_funcall3(rb_cRegexp, rb_intern("escape"), argc, argv);
}

VALUE
og_oniguruma_oregexp_last_match(int argc, VALUE *argv, VALUE self)
{
  VALUE index, array;
  rb_scan_args(argc, argv, "01", &index);
  
  if (index == Qnil) {
    return rb_cv_get(og_cOniguruma_ORegexp, "@@last_match");
  } else {
    array = rb_cv_get(og_cOniguruma_ORegexp, "@@last_match");
    return rb_ary_entry(array, FIX2INT(index));
  }
}

/* Constructor and Instance Methods */
static void
og_oniguruma_oregexp_free(void *arg)
{
  og_ORegexp *oregexp = (og_ORegexp*)arg;
  onig_free(oregexp->reg);
  free(oregexp);
}

static VALUE
og_oniguruma_oregexp_alloc(VALUE klass)
{
  og_ORegexp *oregexp = malloc( sizeof( og_ORegexp ) );
  oregexp->reg = NULL;
  return Data_Wrap_Struct(klass, 0, og_oniguruma_oregexp_free, oregexp);
}

static int
og_oniguruma_oregexp_compile(VALUE self, VALUE regex)
{
  int result, pat_end;
  UChar *pattern;
  OnigOptionType options;
  OnigSyntaxType *syntax;
  OnigEncodingType *encoding;
  OnigErrorInfo error_info;
  og_ORegexp *oregexp;
  char error_string[ONIG_MAX_ERROR_MESSAGE_LEN];
  
  encoding = og_oniguruma_extract_encoding(rb_iv_get(self, "@encoding"));
  syntax   = og_oniguruma_extract_syntax(rb_iv_get(self, "@syntax"));
  options  = (OnigOptionType)NUM2INT(rb_iv_get(self, "@options"));
  
  Data_Get_Struct(self, og_ORegexp, oregexp);
  
  pattern = (UChar*)StringValuePtr(regex);
  pat_end = RSTRING(regex)->len;
  
  result = onig_new(&(oregexp->reg),  /* Regexp Object */
    pattern, pattern + pat_end,
    options, encoding, syntax,
    &error_info);
  
  if (result != ONIG_NORMAL) {
    onig_error_code_to_str(error_string, result, &error_info);
    rb_raise(rb_eArgError, "Oniguruma Error: %s", error_string);
  }
  
  return Qnil;
}

static void
og_oniguruma_oregexp_options_parse(VALUE self, VALUE hash)
{
  VALUE options, encoding, syntax;
  
  encoding = rb_hash_aref(hash, ID2SYM(rb_intern("encoding")));
  options  = rb_hash_aref(hash, ID2SYM(rb_intern("options")));
  syntax   = rb_hash_aref(hash, ID2SYM(rb_intern("syntax")));
  
  if (NIL_P(encoding))
    encoding = rb_const_get(og_mOniguruma, rb_intern("ENCODING_ASCII"));
  
  if (NIL_P(options))
    options = rb_const_get(og_mOniguruma, rb_intern("OPTION_DEFAULT"));
  
  if (NIL_P(syntax))
    syntax = rb_const_get(og_mOniguruma, rb_intern("SYNTAX_DEFAULT"));
  
  rb_iv_set(self, "@encoding", encoding);
  rb_iv_set(self, "@options", options);
  rb_iv_set(self, "@syntax", syntax);
}

static VALUE
og_oniguruma_oregexp_initialize_real(VALUE self, VALUE re, VALUE options)
{
  rb_iv_set(self, "@pattern", StringValue(re)); /* Take a copy */
  og_oniguruma_oregexp_options_parse(self, options);
  og_oniguruma_oregexp_compile(self, rb_iv_get(self, "@pattern"));
  
  return self;
}

/* TODO: Modify to handle => r = ORegexp.new('cat', 'i', 'utf8', 'java')
   In this case `hash` might be a string. Would need to change method
   to -1 format and parse.
*/

static void
og_oniguruma_oregexp_upper(char *str)
{
  while (*str != '\0')
  {
    if ('a' < *str && *str < 'z')
      *str -= 32;
    str++;
  }
}

VALUE
og_oniguruma_oregexp_initialize(int argc, VALUE *argv, VALUE self)
{
  int i;
  long opts;
  char *byte;
  VALUE re, args, options, shortcuts,
    cut, opt, enc, syn;
  
  rb_scan_args(argc, argv, "1*", &re, &args);
  
  if (TYPE(rb_ary_entry(args, 0)) == T_STRING) {
    options = rb_hash_new();
    shortcuts = rb_const_get(og_mOniguruma, rb_intern("OPT_SHORTCUTS"));
    
    opt = rb_ary_shift(args);
    enc = rb_ary_shift(args);
    syn = rb_ary_shift(args);
    
    opts = 0;
    for (i = 0, byte = RSTRING(opt)->ptr; i < RSTRING(opt)->len; i++, byte++)
    {
      cut = rb_hash_aref(shortcuts, rb_str_new(byte, 1));
      if (!NIL_P(cut))
        opts = opts | FIX2INT(cut);
    }
    
    rb_hash_aset(options, ID2SYM(rb_intern("options")), INT2FIX(opts));
    
    byte = (char *) malloc( sizeof(char) * (RSTRING(enc)->len + 10));
    snprintf(byte, RSTRING(enc)->len + 10, "ENCODING_%s", RSTRING(enc)->ptr);
    og_oniguruma_oregexp_upper(byte);
    
    if (!NIL_P(enc) && rb_const_defined(og_mOniguruma, rb_intern(byte)))
      rb_hash_aset(options, ID2SYM(rb_intern("encoding")), rb_const_get(og_mOniguruma, rb_intern(byte)));
    
    free(byte);
    
    byte = (char *) malloc( sizeof(char) * (RSTRING(syn)->len + 8));
    snprintf(byte, RSTRING(syn)->len + 10, "SYNTAX_%s", RSTRING(syn)->ptr);
    og_oniguruma_oregexp_upper(byte);
    
    if (!NIL_P(syn) && rb_const_defined(og_mOniguruma, rb_intern(byte)))
      rb_hash_aset(options, ID2SYM(rb_intern("syntax")), rb_const_get(og_mOniguruma, rb_intern(byte)));
    
    free(byte);
  } else {
    if (!NIL_P(rb_ary_entry(args, 0)))
      options = rb_ary_shift(args);
    else
      options = rb_hash_new();
  }
  
  return og_oniguruma_oregexp_initialize_real(self, re, options);
}

static VALUE
og_oniguruma_oregexp_get_match(VALUE self, OnigRegion *region, VALUE string)
{
  VALUE match;
  og_CallbackPacket packet;
  og_ORegexp *oregexp;
  
  Data_Get_Struct(self, og_ORegexp, oregexp);
  
  match = og_oniguruma_oregexp_match_initialize(region, string);
  
  rb_cv_set(og_cOniguruma_ORegexp, "@@last_match", match);
  
  packet.region = region;
  
  if (onig_number_of_names(oregexp->reg) > 0) {
    packet.hash = rb_hash_new();
    onig_foreach_name(oregexp->reg, og_oniguruma_name_callback, &packet);
    rb_iv_set(match, "@named_captures", packet.hash);
  }
  
  return match;
}

VALUE
og_oniguruma_oregexp_match(int argc, VALUE *argv, VALUE self)
{
  int result;
  OnigRegion *region;
  og_ORegexp *oregexp;
  
  char error_string[ONIG_MAX_ERROR_MESSAGE_LEN];
  
  VALUE string, begin, end, match;
  
  rb_scan_args(argc, argv, "12", &string, &begin, &end);
  
  if (NIL_P(begin))
    begin = INT2FIX(0);
  
  if (NIL_P(end))
    end = INT2FIX(RSTRING(string)->len);
  
  Data_Get_Struct(self, og_ORegexp, oregexp);
  
  region = onig_region_new();
  result = onig_search(oregexp->reg,
    RSTRING(string)->ptr, RSTRING(string)->ptr + RSTRING(string)->len,
    RSTRING(string)->ptr + FIX2INT(begin), RSTRING(string)->ptr + FIX2INT(end),
    region, ONIG_OPTION_NONE);
  
  rb_backref_set(Qnil);
  if (result > 0) {
    match = og_oniguruma_oregexp_get_match(self, region, string);
    
    onig_region_free(region, 1);
    rb_backref_set(match);
    rb_match_busy(match);

    return match;    
  } else if (result == ONIG_MISMATCH) {
    onig_region_free(region, 1);
    return Qnil;
  } else {
    onig_region_free(region, 1);
    
    onig_error_code_to_str(error_string, result);
    rb_raise(rb_eArgError, "Oniguruma Error: %s", error_string);
  }
}

static VALUE
og_oniguruma_oregexp_do_replacement(VALUE self, VALUE buffer, VALUE str, VALUE replacement, OnigRegion *region)
{
  const UChar *subj; long subj_len;
  og_ORegexp *oregexp;
  
  int position = 0, digits, group, named_group_pos,
    named_group_begin, named_group_end,
    code_point_len, previous_code_point_len;
  OnigCodePoint code_point;
  OnigEncoding encoding;
  
  subj = RSTRING(str)->ptr; subj_len = RSTRING(str)->len;
  Data_Get_Struct(self, og_ORegexp, oregexp);
  
  encoding = onig_get_encoding(oregexp->reg);
  
  while (position < RSTRING(replacement)->len)
  {
    og_oniguruma_oregexp_get_code_point(code_point, code_point_len, encoding, replacement, position);
    
    if (code_point_len == 0) {
      rb_warn("Anomally: length of char '%d' is 0", code_point);
      code_point_len = 1;
    }
    
    position += code_point_len;
    
    if (code_point != 0x5c) { /* 0x5c is a backslash \ */
      rb_str_buf_cat(buffer, RSTRING(replacement)->ptr + position - code_point_len, code_point_len);
      continue;
    }
    
    if (position >= RSTRING(replacement)->len) {
      rb_str_buf_cat(buffer, RSTRING(replacement)->ptr + (position - code_point_len), code_point_len);
      break;
    }
    
    digits = group = 0;
    while(1) /* n + 1/2 times loop. break out manually. */
    {
      if (position >= RSTRING(replacement)->len) break;
      
      og_oniguruma_oregexp_get_code_point(code_point, code_point_len, encoding, replacement, position);
      
      if (!ONIGENC_IS_CODE_DIGIT(encoding, code_point)) break;
      
      group = group * 10 + (code_point - '0');
      position += code_point_len;
      digits++;
      
      if (digits >= 2) break; /* limit 99 groups */
    }
    
    if (digits == 0) {
      previous_code_point_len = code_point_len;
      og_oniguruma_oregexp_get_code_point(code_point, code_point_len, encoding, replacement, position);
      
      switch (code_point)
      {
        case '\\': // \ literal, just cat and keep going
          rb_str_buf_cat(buffer, RSTRING(replacement)->ptr + position, code_point_len);
          position += code_point_len;
          break;
        
        case '&': // matched substring
          rb_str_buf_cat(buffer, subj + region->beg[0], region->end[0] - region->beg[0]);
          position += code_point_len;
          break;
        
        case '`': // prematch
          rb_str_buf_cat(buffer, subj, region->beg[0]);
          position += code_point_len;
          break;
        
        case '\'': // postmatch
          rb_str_buf_cat(buffer, subj + region->end[0], subj_len - region->end[0]);
          position += code_point_len;
          break;
          
        case '+': // last matched
          position += code_point_len;
          
          for(group = region->num_regs - 1; group > 0; group--)
          {
            if (region->beg[group] != -1) {
              rb_str_buf_cat(buffer, subj + region->beg[group],
                region->end[group] - region->beg[group]);
              break;
            }
          }
          
          break;
          
        case '<': // named group reference
          named_group_end = named_group_begin = named_group_pos = position + code_point_len;
          
          while (named_group_pos < subj_len)
          {
            og_oniguruma_oregexp_get_code_point(code_point, code_point_len, encoding, replacement, named_group_pos);
            named_group_pos += code_point_len;
            
            if (code_point == '>') break;
            
            if (ONIGENC_IS_CODE_WORD(encoding, code_point))
              named_group_end += code_point_len;
            else break;
          }
          
          if (code_point != '>' || named_group_end == named_group_begin) { // place backslash and '<'
            rb_str_buf_cat(buffer, RSTRING(replacement)->ptr+(position-previous_code_point_len),
              previous_code_point_len+code_point_len);
            position += code_point_len;
          } else { // lookup for group and subst for that value
            group = onig_name_to_backref_number(oregexp->reg, 
              RSTRING(replacement)->ptr + named_group_begin,
              RSTRING(replacement)->ptr + named_group_end, region);
            
            if (group >= 0)
              rb_str_buf_cat(buffer, subj + region->beg[group], 
                region->end[group] - region->beg[group]);
            position = named_group_pos;
          }
          break;

        default:
          rb_str_buf_cat(buffer, RSTRING(replacement)->ptr + (position - previous_code_point_len),
            previous_code_point_len + code_point_len);
          position += code_point_len;
          break;
      } /* switch (code_point) */
    } else {
      if (group < region->num_regs && region->beg[group] >= 0)
        rb_str_buf_cat(buffer, subj + region->beg[group],
          region->end[group] - region->beg[group]);
    } /* if (digits == 0) */
  } /* while (position < RSTRING(replacement)->len) */
  
  return Qnil;
}

static VALUE
og_oniguruma_oregexp_do_substitution(og_SubstitutionArgs *args)
{
  int tainted_replacement = 0;
  VALUE str, replacement, block;
  og_ORegexp *oregexp;
  
  long begin = 0, end = 0, last_end = 0, multibyte_diff = 0;
  
  UChar *subj; int subj_len;
  VALUE buffer, block_match, block_result;
  OnigEncoding encoding;
  
  /* Parse the arguments */
  if (rb_block_given_p()) {
    rb_scan_args(args->argc, args->argv, "1&", &str, &block);
  } else {
    rb_scan_args(args->argc, args->argv, "2", &str, &replacement);
    Check_Type(replacement, T_STRING);
    if (OBJ_TAINTED(replacement))
      tainted_replacement = 1;
  }
  
  Data_Get_Struct(args->self, og_ORegexp, oregexp);
  subj = RSTRING(str)->ptr; subj_len = RSTRING(str)->len;
  
  begin = onig_search(oregexp->reg,
    subj, subj + subj_len,
    subj, subj + subj_len,
    args->region, ONIG_OPTION_NONE);
  
  if (begin < 0) {
    if (args->update_self)
      return Qnil;
    return rb_str_dup(str);
  }
  
  buffer = rb_str_buf_new(subj_len);
  encoding = onig_get_encoding(oregexp->reg);
  
  do {
    last_end = end;
    begin = args->region->beg[0];
    end   = args->region->end[0];
    
    rb_str_buf_cat(buffer, subj + last_end, begin - last_end);
    
    if (rb_block_given_p()) {
      /* yielding to a block */
      block_match = og_oniguruma_oregexp_get_match(args->self, args->region, str);
      
      rb_backref_set(block_match);
      rb_match_busy(block_match);
      
      block_result = rb_yield(block_match);
      
      og_oniguruma_str_mod_check(str, subj, subj_len);
      replacement = rb_obj_as_string(block_result);
      rb_str_append(buffer, replacement);
    } else 
      og_oniguruma_oregexp_do_replacement(args->self, buffer, str, replacement, args->region);
    
    if (!args->global) break;
    
    /* Finish this match so we can do the next one */
    if (begin == end) {
      if( subj_len <= end )
        break;
      
      multibyte_diff = enc_len(encoding, subj + end);
      rb_str_buf_cat(buffer, subj + end, multibyte_diff);
      end += multibyte_diff;
    }
    
    begin = onig_search(oregexp->reg,
      subj,       subj + subj_len,
      subj + end, subj + subj_len,
      args->region, ONIG_OPTION_NONE);
  } while (begin >= 0);
  
  rb_str_buf_cat(buffer, subj + end, subj_len - end);
  
  if (tainted_replacement)
    OBJ_INFECT(buffer, replacement);
  OBJ_INFECT(buffer, str);
  
  if (args->update_self) {
    rb_funcall(str, rb_intern("replace"), 1, buffer);
    return str;
  }
  
  return buffer;
}

static VALUE
og_oniguruma_oregexp_do_cleanup(OnigRegion *region)
{
  onig_region_free(region, 1);
  return Qnil;
}

static VALUE
og_oniguruma_oregexp_do_substitution_safe(VALUE self,
  int argc, VALUE *argv, int global, int update_self)
{
  OnigRegion *region = onig_region_new();
  og_SubstitutionArgs fargs;
  
  og_SubstitutionArgs_set(&fargs, self, argc, argv, global, update_self, region);
  return rb_ensure(og_oniguruma_oregexp_do_substitution, (VALUE)&fargs,
    og_oniguruma_oregexp_do_cleanup, (VALUE)region);
}

VALUE
og_oniguruma_oregexp_gsub(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_oregexp_do_substitution_safe(self, argc, argv, 1, 0);
}

VALUE
og_oniguruma_oregexp_gsub_bang(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_oregexp_do_substitution_safe(self, argc, argv, 1, 1);
}

VALUE
og_oniguruma_oregexp_sub(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_oregexp_do_substitution_safe(self, argc, argv, 0, 0);
}

VALUE
og_oniguruma_oregexp_sub_bang(int argc, VALUE *argv, VALUE self)
{
  return og_oniguruma_oregexp_do_substitution_safe(self, argc, argv, 0, 1);
}

static VALUE
og_oniguruma_oregexp_do_scan(og_ScanArgs *args)
{ 
  VALUE str, match, matches;
  OnigEncoding encoding;
  og_ORegexp *oregexp;
  long begin = 0, end = 0, multibyte_diff = 0;
  
  Data_Get_Struct(args->self, og_ORegexp, oregexp);
  
  str = StringValue(args->str);
  
  begin = onig_search(oregexp->reg,
    RSTRING(str)->ptr, RSTRING(str)->ptr + RSTRING(str)->len,
    RSTRING(str)->ptr, RSTRING(str)->ptr + RSTRING(str)->len,
    args->region, ONIG_OPTION_NONE);
    
  if (begin < 0)
    return Qnil;
  
  matches = rb_ary_new();
  encoding = onig_get_encoding(oregexp->reg);
  
  do {
    match = og_oniguruma_oregexp_get_match(args->self, args->region, str);
    end = args->region->end[0];
    rb_ary_push(matches, match);
    
    if (rb_block_given_p())
      rb_yield(match);
    
    if (end == begin) {
      if( RSTRING(str)->len <= end )
        break;
      multibyte_diff = enc_len(encoding, RSTRING(str)->ptr + end);
      end += multibyte_diff;
    }
    
    begin = onig_search(oregexp->reg,
      RSTRING(str)->ptr,       RSTRING(str)->ptr + RSTRING(str)->len,
      RSTRING(str)->ptr + end, RSTRING(str)->ptr + RSTRING(str)->len,
      args->region, ONIG_OPTION_NONE);
  } while (begin >= 0);
  
  return matches;
}

VALUE
og_oniguruma_oregexp_scan(VALUE self, VALUE str)
{
  OnigRegion *region = onig_region_new();
  og_ScanArgs fargs;
  
  og_ScanArgs_set(&fargs, self, str, region);
  return rb_ensure(og_oniguruma_oregexp_do_scan, (VALUE)&fargs,
    og_oniguruma_oregexp_do_cleanup, (VALUE)region);
}

VALUE
og_oniguruma_oregexp_casefold(VALUE self)
{
  int options, ignore_case;
  
  options = FIX2INT(rb_iv_get(self, "@options"));
  ignore_case = FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_IGNORECASE")));
  
  if ((options & ignore_case) > 0)
    return Qtrue;
  return Qfalse;
}

VALUE
og_oniguruma_oregexp_operator_equality(VALUE self, VALUE rhs)
{
  VALUE pattern, encoding, rhs_pattern, rhs_encoding;
  
  /* TODO: test type, make sure its an Oniguruma::ORegexp object */
  
  encoding = rb_iv_get(self, "@encoding");
  pattern = rb_iv_get(self, "@pattern");
  
  rhs_encoding = rb_iv_get(rhs, "@encoding");
  rhs_pattern = rb_iv_get(rhs, "@pattern");
  
  if (rb_str_cmp(pattern, rhs_pattern) == 0    &&
    FIX2INT(encoding) == FIX2INT(rhs_encoding) &&
    og_oniguruma_oregexp_casefold(self) == og_oniguruma_oregexp_casefold(rhs))
      return Qtrue;
  return Qfalse;
}

VALUE
og_oniguruma_oregexp_operator_identical(VALUE self, VALUE str)
{
  VALUE match, args[2];
  
  if (TYPE(str) != T_STRING) {
    str = rb_check_string_type(str);
    if (NIL_P(str))
      return Qfalse;
  }
  
  args[0] = StringValue(str);
  args[1] = (VALUE)NULL;
  
  match = og_oniguruma_oregexp_match(1, args, self);
  
  if (NIL_P(match))
    return Qfalse;
  return Qtrue;
}

VALUE
og_oniguruma_oregexp_operator_match(VALUE self, VALUE str)
{
  VALUE match, args[2];
  
  args[0] = str;
  args[1] = (VALUE)NULL;
  
  match = og_oniguruma_oregexp_match(1, args, self);
  
  if(NIL_P(match))
    return Qnil;
  return INT2FIX(RMATCH(match)->regs->beg[0]);
}

VALUE
og_oniguruma_oregexp_kcode(VALUE self)
{
  return rb_iv_get(self, "@encoding");
}

VALUE
og_oniguruma_oregexp_options(VALUE self)
{
  return rb_iv_get(self, "@options");
}

VALUE
og_oniguruma_oregexp_source(VALUE self)
{
  VALUE pattern = rb_iv_get(self, "@pattern");
  OBJ_FREEZE(pattern);
  return pattern;
}

VALUE
og_oniguruma_oregexp_to_s(VALUE self)
{
  int options;
  VALUE str;
  
  options = FIX2INT(og_oniguruma_oregexp_options(self));
  str = rb_str_new2("(?");
  
  if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_IGNORECASE")))) > 0)
    rb_str_cat(str, "i", 1);

  if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_MULTILINE")))) > 0)
    rb_str_cat(str, "m", 1);

  if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_EXTEND")))) > 0)
    rb_str_cat(str, "x", 1);
  
  if (rb_str_cmp(str, rb_str_new2("(?imx")) != 0) {
    rb_str_cat(str, "-", 1);
    
    if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_IGNORECASE")))) == 0)
      rb_str_cat(str, "i", 1);

    if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_MULTILINE")))) == 0)
      rb_str_cat(str, "m", 1);

    if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_EXTEND")))) == 0)
      rb_str_cat(str, "x", 1);
  }
  
  rb_str_cat(str, ")", 1);
  
  return rb_str_concat(str, rb_iv_get(self, "@pattern"));
}

VALUE
og_oniguruma_oregexp_inspect(VALUE self)
{
  int options;
  VALUE str;
  
  options = FIX2INT(og_oniguruma_oregexp_options(self));
  str = rb_str_new2("/");
  rb_str_concat(str, rb_iv_get(self, "@pattern"));
  rb_str_cat(str, "/", 1);
  
  if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_IGNORECASE")))) > 0)
    rb_str_cat(str, "i", 1);

  if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_MULTILINE")))) > 0)
    rb_str_cat(str, "m", 1);

  if ((options & FIX2INT(rb_const_get(og_mOniguruma, rb_intern("OPTION_EXTEND")))) > 0)
    rb_str_cat(str, "x", 1);
  
  return str;
}
