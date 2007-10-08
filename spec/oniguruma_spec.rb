require File.dirname(__FILE__) + '/spec_helper.rb'

class Module
  alias :has_constant? :const_defined?
end

describe Oniguruma, "::VERSION" do
  it "should have STRING" do
    Oniguruma::VERSION.should have_constant("STRING")
  end
  
  it "should have ENGINE" do
    Oniguruma::VERSION.should have_constant("ENGINE")
  end
end

describe Oniguruma, "::VERSION::STRING" do
  before(:each) do
    @version = Oniguruma::VERSION::STRING
  end
  
  it "should not be nil" do
    @version.should_not be_nil
  end
  
  it "should be x.y.z" do
    @version.should match(/([0-9]+\.){2}[0-9]+/)
  end
end

describe Oniguruma, "::VERSION::ENGINE" do
  before(:each) do
    @engine = Oniguruma::VERSION::ENGINE
  end
  
  it "should not be nil" do
    @engine.should_not be_nil
  end

  it "should be x.y.z" do
    @engine.should match(/([0-9]+\.){2}[0-9]+/)
  end
end

describe Oniguruma, "constants" do
  it "should have 'ENCODING_UNDEF'" do
    Oniguruma.should have_constant("ENCODING_UNDEF")
  end
  it "should have 'ENCODING_ASCII'" do
    Oniguruma.should have_constant("ENCODING_ASCII")
  end
  it "should have 'ENCODING_ISO_8859_1'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_1")
  end
  it "should have 'ENCODING_ISO_8859_2'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_2")
  end
  it "should have 'ENCODING_ISO_8859_3'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_3")
  end
  it "should have 'ENCODING_ISO_8859_4'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_4")
  end
  it "should have 'ENCODING_ISO_8859_5'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_5")
  end
  it "should have 'ENCODING_ISO_8859_6'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_6")
  end
  it "should have 'ENCODING_ISO_8859_7'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_7")
  end
  it "should have 'ENCODING_ISO_8859_8'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_8")
  end
  it "should have 'ENCODING_ISO_8859_9'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_9")
  end
  it "should have 'ENCODING_ISO_8859_10'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_10")
  end
  it "should have 'ENCODING_ISO_8859_11'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_11")
  end
  it "should have 'ENCODING_ISO_8859_13'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_13")
  end
  it "should have 'ENCODING_ISO_8859_14'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_14")
  end
  it "should have 'ENCODING_ISO_8859_15'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_15")
  end
  it "should have 'ENCODING_ISO_8859_16'" do
    Oniguruma.should have_constant("ENCODING_ISO_8859_16")
  end
  it "should have 'ENCODING_UTF8'" do
    Oniguruma.should have_constant("ENCODING_UTF8")
  end
  it "should have 'ENCODING_EUC_JP'" do
    Oniguruma.should have_constant("ENCODING_EUC_JP")
  end
  it "should have 'ENCODING_EUC_TW'" do
    Oniguruma.should have_constant("ENCODING_EUC_TW")
  end
  it "should have 'ENCODING_EUC_KR'" do
    Oniguruma.should have_constant("ENCODING_EUC_KR")
  end
  it "should have 'ENCODING_EUC_CN'" do
    Oniguruma.should have_constant("ENCODING_EUC_CN")
  end
  it "should have 'ENCODING_SJIS'" do
    Oniguruma.should have_constant("ENCODING_SJIS")
  end
  it "should have 'ENCODING_KOI8'" do
    if Oniguruma::VERSION::ENGINE.to_i < 4
      Oniguruma.should have_constant("ENCODING_KOI8")
    else
      pending("Not available in Oniguruma v4 or higher")
    end
  end
  it "should have 'ENCODING_KOI8_R'" do
    Oniguruma.should have_constant("ENCODING_KOI8_R")
  end
  it "should have 'ENCODING_BIG5'" do
    Oniguruma.should have_constant("ENCODING_BIG5")
  end
  it "should have 'ENCODING_UTF16_BE'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("ENCODING_UTF16_BE")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  it "should have 'ENCODING_UTF16_BE'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("ENCODING_UTF16_LE")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  it "should have 'ENCODING_UTF16_BE'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("ENCODING_UTF32_BE")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  it "should have 'ENCODING_UTF16_BE'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("ENCODING_UTF32_LE")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  it "should have 'ENCODING_UTF16_BE'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("ENCODING_GB18030")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  
  it "should have 'ENCODING_CP1251'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 5
      Oniguruma.should have_constant("ENCODING_CP1251")
    else
      pending("Requires Oniguruma v5 or higher")
    end
  end
  
  it "should have 'SYNTAX_DEFAULT'" do
    Oniguruma.should have_constant("SYNTAX_DEFAULT")
  end
  it "should have 'SYNTAX_POSIX_BASIC'" do
    Oniguruma.should have_constant("SYNTAX_POSIX_BASIC")
  end
  it "should have 'SYNTAX_POSIX_EXTENDED'" do
    Oniguruma.should have_constant("SYNTAX_POSIX_EXTENDED")
  end
  it "should have 'SYNTAX_EMACS'" do
    Oniguruma.should have_constant("SYNTAX_EMACS")
  end
  it "should have 'SYNTAX_GREP'" do
    Oniguruma.should have_constant("SYNTAX_GREP")
  end
  it "should have 'SYNTAX_GNU_REGEX'" do
    Oniguruma.should have_constant("SYNTAX_GNU_REGEX")
  end
  it "should have 'SYNTAX_JAVA'" do
    Oniguruma.should have_constant("SYNTAX_JAVA")
  end
  it "should have 'SYNTAX_PERL'" do
    Oniguruma.should have_constant("SYNTAX_PERL")
  end
  it "should have 'SYNTAX_RUBY'" do
    Oniguruma.should have_constant("SYNTAX_RUBY")
  end
  it "should have 'SYNTAX_PERL_NG'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("SYNTAX_PERL_NG")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  it "should have 'SYNTAX_ASIS'" do
    if Oniguruma::VERSION::ENGINE.to_i >= 4
      Oniguruma.should have_constant("SYNTAX_ASIS")
    else
      pending("Requires Oniguruma v4 or higher")
    end
  end
  
  it "should have 'OPTION_DEFAULT'" do
    Oniguruma.should have_constant("OPTION_DEFAULT")
  end
  it "should have 'OPTION_NONE'" do
    Oniguruma.should have_constant("OPTION_NONE")
  end
  it "should have 'OPTION_IGNORECASE'" do
    Oniguruma.should have_constant("OPTION_IGNORECASE")
  end
  it "should have 'OPTION_EXTEND'" do
    Oniguruma.should have_constant("OPTION_EXTEND")
  end
  it "should have 'OPTION_MULTILINE'" do
    Oniguruma.should have_constant("OPTION_MULTILINE")
  end
  it "should have 'OPTION_SINGLELINE'" do
    Oniguruma.should have_constant("OPTION_SINGLELINE")
  end
  it "should have 'OPTION_FIND_LONGEST'" do
    Oniguruma.should have_constant("OPTION_FIND_LONGEST")
  end
  it "should have 'OPTION_FIND_NOT_EMPTY'" do
    Oniguruma.should have_constant("OPTION_FIND_NOT_EMPTY")
  end
  it "should have 'OPTION_NEGATE_SINGLELINE'" do
    Oniguruma.should have_constant("OPTION_NEGATE_SINGLELINE")
  end
  it "should have 'OPTION_DONT_CAPTURE_GROUP'" do
    Oniguruma.should have_constant("OPTION_DONT_CAPTURE_GROUP")
  end
  it "should have 'OPTION_CAPTURE_GROUP'" do
    Oniguruma.should have_constant("OPTION_CAPTURE_GROUP")
  end
  it "should have 'OPTION_NOTBOL'" do
    Oniguruma.should have_constant("OPTION_NOTBOL")
  end
  it "should have 'OPTION_NOTEOL'" do
    Oniguruma.should have_constant("OPTION_NOTEOL")
  end
  it "should have 'OPTION_POSIX_REGION'" do
    Oniguruma.should have_constant("OPTION_POSIX_REGION")
  end
  it "should have 'OPTION_MAXBIT'" do
    Oniguruma.should have_constant("OPTION_MAXBIT")
  end
end

describe Oniguruma, "::OPT_SHORTCUTS" do
  it "should be a hash" do
    Oniguruma::OPT_SHORTCUTS.should be_an_instance_of(Hash)
  end
  
  it "should have key 'i'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("i")
  end
  it "should have key 'x'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("x")
  end
  it "should have key 'm'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("m")
  end
  it "should have key 's'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("s")
  end
  it "should have key 'l'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("l")
  end
  it "should have key 'E'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("E")
  end
  it "should have key 'S'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("S")
  end
  it "should have key 'G'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("G")
  end
  it "should have key 'g'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("g")
  end
  it "should have key 'B'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("B")
  end
  it "should have key 'E'" do
    Oniguruma::OPT_SHORTCUTS.should have_key("E")
  end
end
