require File.dirname(__FILE__) + '/spec_helper.rb'

describe Oniguruma::ORegexp, ".escape" do
  it "should respond to :escape" do
    Oniguruma::ORegexp.should respond_to(:escape)
  end
  
  it "should respond to alias :quote" do
    Oniguruma::ORegexp.should respond_to(:quote)
  end
  
  it "should escape expression" do
    res = Oniguruma::ORegexp.escape('\\*?{}.')
    res.should eql('\\\\\*\?\{\}\.')
  end
end

describe Oniguruma::ORegexp, ".last_match" do
  before(:each) do
    Oniguruma::ORegexp.new('c(.)t').match('cat')
  end
  
  it "should return 'cat' at 0" do
    Oniguruma::ORegexp.last_match(0).should eql('cat')
  end
  
  it "should return 'a' at 1" do
    Oniguruma::ORegexp.last_match(1).should eql('a')
  end
  
  it "should not have a match at 2" do
    Oniguruma::ORegexp.last_match(2).should be_nil
  end
end

describe Oniguruma::ORegexp, ".new" do
  it "should respond to :new" do
    Oniguruma::ORegexp.should respond_to(:new)
  end
  
  it "should not raise on valid expression" do
    lambda {
      Oniguruma::ORegexp.new("(3.)(.*)(3.)")
    }.should_not raise_error
  end
  
  it "should respond to alias :compile" do
    Oniguruma::ORegexp.should respond_to(:compile)
  end
  
  it "should not raise on valid expression" do
    lambda {
      Oniguruma::ORegexp.compile("(3.)(.*)(3.)")
    }.should_not raise_error
  end
  
  it "should raise ArgumentError on bad expression" do
    lambda {
      Oniguruma::ORegexp.new("(3.)(.*)(3.))")
    }.should raise_error(ArgumentError)
  end
end

describe Oniguruma::ORegexp, ".new('[a-z][a-z0-9_]+')" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+')
  end
  
  it "should not be nil" do
    @oregexp.should_not be_nil
  end
end

describe Oniguruma::ORegexp, ".new('[a-z][a-z0-9_]+', {})" do  
  def build(options = {})
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      options)
  end
  
  it "should not be nil" do
    build
    @oregexp.should_not be_nil
  end
  
  it "should allow only :options" do
    build(:options => Oniguruma::OPTION_IGNORECASE)
    @oregexp.should_not be_nil
  end
  
  it "should allow only :syntax" do
    build(:syntax => Oniguruma::SYNTAX_JAVA)
    @oregexp.should_not be_nil
  end
  
  it "should allow only :encoding" do
    build(:encoding => Oniguruma::ENCODING_UTF8)
    @oregexp.should_not be_nil
  end
  
  it "should allow :options, :syntax" do
    build(:options => Oniguruma::OPTION_IGNORECASE,
      :syntax => Oniguruma::SYNTAX_JAVA)
    @oregexp.should_not be_nil
  end
  
  it "should allow :options, :encoding" do
    build(:options => Oniguruma::OPTION_IGNORECASE,
      :encoding => Oniguruma::ENCODING_UTF8)
    @oregexp.should_not be_nil
  end
  
  it "should allow :syntax, :encoding" do
    build(:syntax => Oniguruma::SYNTAX_JAVA,
      :encoding => Oniguruma::ENCODING_UTF8)
    @oregexp.should_not be_nil
  end
  
  it "should allow :options, :syntax, :encoding" do
    build(:options => Oniguruma::OPTION_IGNORECASE,
      :encoding => Oniguruma::ENCODING_UTF8,
      :syntax => Oniguruma::SYNTAX_JAVA)
    @oregexp.should_not be_nil
  end
end

describe Oniguruma::ORegexp, ".new('[a-z][a-z0-9_]+', '', '', '')" do
  def build(opt = nil, enc = nil, syn = nil)
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      opt, enc, syn)
  end
  
  it "should not be nil" do
    build('i', 'utf8', 'java')
    @oregexp.should_not be_nil
  end
  
  it "should allow only option" do
    build('i')
    @oregexp.should_not be_nil
  end
  
  it "should allow only syntax" do
    build(nil, 'utf8')
    @oregexp.should_not be_nil
  end
  
  it "should allow only encoding" do
    build(nil, nil, 'java')
    @oregexp.should_not be_nil
  end
  
  it "should allow option, syntax" do
    build('i', 'utf8')
    @oregexp.should_not be_nil
  end
  
  it "should allow option, encoding" do
    build('i', nil, 'java')
    @oregexp.should_not be_nil
  end
  
  it "should allow encoding, syntax" do
    build(nil, 'utf8', 'java')
    @oregexp.should_not be_nil
  end
  
  it "should allow option, encoding, syntax" do
    build('i', 'utf8', 'java')
    @oregexp.should_not be_nil
  end
end

describe Oniguruma::ORegexp, ".match" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new("(3.)(.*)(3.)")
  end
  
  it "should match '12345634'" do
    @oregexp.match("12345634").should_not be_nil
  end
  
  it "should not match '12145614'" do
    @oregexp.match("12145614").should be_nil
  end
end

describe Oniguruma::ORegexp, ".match (back references)" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('Date:(\d{4})/(\d{2})/(\d{2})')
    @oregexp.match("Date:2007/03/25")
  end
  
  it "should set $~" do
    $~.should_not be_nil
  end
  
  it "should set $1 = 2007" do
    $1.should eql("2007")
  end
  
  it "should set $2 = 03" do
    $2.should eql("03")
  end
  
  it "should set $3 = 25" do
    $3.should eql("25")
  end
end

describe Oniguruma::ORegexp, "=~ (back references)" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('Date:(\d{4})/(\d{2})/(\d{2})')
    @oregexp =~ "Date:2007/03/25"
  end

  it "should set $~" do
    $~.should_not be_nil
  end

  it "should set $1 = 2007" do
    $1.should eql("2007")
  end

  it "should set $2 = 03" do
    $2.should eql("03")
  end

  it "should set $3 = 25" do
    $3.should eql("25")
  end
end

describe Oniguruma::ORegexp, "=~ insensitive" do
  it "should return first match index (OPTION_IGNORECASE)" do
    @oregexp = Oniguruma::ORegexp.new('SIT',
      :options => Oniguruma::OPTION_IGNORECASE)
    
    lambda {
      @oregexp =~ "insensitive"
    }.call.should eql(5)
  end
  
  it "should fail to match (OPTION_NONE)" do
    @oregexp = Oniguruma::ORegexp.new('SIT')
    
    lambda {
      @oregexp =~ "insensitive"
    }.call.should be_nil
  end
  
  it "should match when using i shortcut" do
    @oregexp = Oniguruma::ORegexp.new('SIT', 'i')
    
    lambda {
      @oregexp =~ "insensitive"
    }.call.should eql(5)
  end
end

describe Oniguruma::ORegexp, "==" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('expression')
  end
  
  it "should be equal" do
    @oregexp.should eql(Oniguruma::ORegexp.new('expression'))
  end
  
  it "should not be equal with different pattern" do
    @oregexp.should_not eql(Oniguruma::ORegexp.new('expresLsion'))
  end
  
  it "should not be equal with different options" do
    @options.should_not eql(Oniguruma::ORegexp.new('expression',
                              :options => Oniguruma::OPTION_IGNORECASE))
  end
  
  it "should not be equal with different encoding" do
    @oregexp.should_not eql(Oniguruma::ORegexp.new('expression', 
                              :encoding => Oniguruma::ENCODING_UTF8))
  end
end

describe Oniguruma::ORegexp, "===" do
  it "should operate in case statements" do
    lambda {
      case "HELLO"
      when Oniguruma::ORegexp.new('^[a-z]*$')
        :lower
      when Oniguruma::ORegexp.new('^[A-Z]*$')
        :upper
      else
        :mixed
      end
    }.call.should eql(:upper)
  end
  
  it "should not raise in case statements" do
    lambda { 
      case Time.now
      when /./
        :regexp
      when Oniguruma::ORegexp.new('.')
        :oniguruma
      else
        :unknown
      end
    }.should_not raise_error
  end
end

describe Oniguruma::ORegexp, ".sub" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('pe')
    @string = "penelope"
  end
  
  it "should substitute and return new string" do
    @oregexp = Oniguruma::ORegexp.new('pe')
    @oregexp.sub(@string, '**').should eql("**nelope")
  end
  
  it "should substitute and return new string" do
    @oregexp = Oniguruma::ORegexp.new('pe')
    @oregexp.sub(@string) { |m| '++' }.should eql("++nelope")
  end
  
  it "should substitute and return new string (UTF-8)" do
    @oregexp = Oniguruma::ORegexp.new('кот',
      :encoding => Oniguruma::ENCODING_UTF8)
    @oregexp.sub('кот на leash', 'собака').should eql('собака на leash')
  end
end

describe Oniguruma::ORegexp, ".sub (Named Back-references)" do
  it "should handle named backrefs" do
    o = Oniguruma::ORegexp.new('(?<pre>\w+?)\d+(?<after>\w+)')
    o.sub('abc123def', ' \<after>123\<pre> ').should eql(' def123abc ')
  end
  
  it "should handle duplicated named backrefs" do
    o = Oniguruma::ORegexp.new('(?<pre>\w+?)\d+(?<pre>\w+)')
    o.sub('abc123def', '123\<pre>').should eql('123def')
  end
  
  it "should handle multibyte named backrefs" do
    if Oniguruma::VERSION::ENGINE.to_i == 5
      o = Oniguruma::ORegexp.new('(?<группа>test).+(\k<группа>)',
        :encoding => Oniguruma::ENCODING_UTF8)
      o.sub("should test this damned test", '!\<группа>!').should eql("should !test!")
    else
      pending("Untested in v2 or v4, it can cause hangs")
    end
  end
end

describe Oniguruma::ORegexp, ".sub!" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('pe')
    @string = "penelope"
  end
  
  it "should substitute and return string" do
    @oregexp.sub!(@string, '**')
    @string.should eql("**nelope")
  end
  
  it "should substitute and return string (block)" do
    @oregexp = Oniguruma::ORegexp.new('pe')
    @oregexp.sub!(@string) { |m| '++' }
    @string.should eql("++nelope")
  end
end

describe Oniguruma::ORegexp, ".gsub" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('\(\?#(\w+?)\)')
    @string = 'My favorite fruits are (?#fruit1), (?#fruit2), and (?#fruit3)'
  end
  
  it "should substitute all and return new string" do
    @oregexp.gsub(@string, '*').should eql("My favorite fruits are *, *, and *")
  end
  
  it "should substitute and return new string (block)" do
    fruits = { "fruit1" => "apples", "fruit2" => "bananas", "fruit3" => "grapes" }
    @oregexp.gsub(@string) { |m| fruits[m[1]] }.should eql("My favorite fruits are apples, bananas, and grapes")
  end
end

describe Oniguruma::ORegexp, ".gsub!" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('\(\?#(\w+?)\)')
    @string = 'My favorite fruits are (?#fruit1), (?#fruit2), and (?#fruit3)'
  end
  
  it "should substitute all and return string" do
    @oregexp.gsub!(@string, '*')
    @string.should eql("My favorite fruits are *, *, and *")
  end
  
  it "should substitute all and return string (block)" do
    fruits = { "fruit1" => "apples", "fruit2" => "bananas", "fruit3" => "grapes" }
    @oregexp.gsub!(@string) { |m| fruits[m[1]] }
    @string.should eql("My favorite fruits are apples, bananas, and grapes")
  end
end

describe Oniguruma::ORegexp, ".scan" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('\w+')
    @string  = 'cruel world'
  end
  
  it "should scan and return matches" do
    result = @oregexp.scan(@string).collect { |m| m.to_s }
    result.should eql(["cruel", "world"])
  end
  
  it "should scan and yield matches to block" do
    result = ''
    @oregexp.scan(@string) { |m| result << "<<#{m}>>" }
    result.should eql("<<cruel>><<world>>")
  end
end

describe Oniguruma::ORegexp, ".casefold?" do
  it "should be true" do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      :options => Oniguruma::OPTION_IGNORECASE)
    @oregexp.should be_casefold
  end
  
  it "should be false" do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+')
    @oregexp.should_not be_casefold
  end
end

describe Oniguruma::ORegexp, ".kcode" do
  it "should return Oniguruma::ENCODING_ASCII" do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+')
    @oregexp.kcode.should eql(Oniguruma::ENCODING_ASCII)
  end
  
  it "should return Oniguruma::ENCODING_UTF8" do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      :encoding => Oniguruma::ENCODING_UTF8)
    @oregexp.kcode.should eql(Oniguruma::ENCODING_UTF8)
  end
end

describe Oniguruma::ORegexp, ".options" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      :options => Oniguruma::OPTION_IGNORECASE | Oniguruma::OPTION_EXTEND)
  end
  
  it "should be a Fixnum" do
    @oregexp.options.should be_an_instance_of(Fixnum)
  end
  
  it "should mask Oniguruma::OPTION_IGNORECASE" do
    res = @oregexp.options & Oniguruma::OPTION_IGNORECASE
    res.should > 0
  end
  
  it "should mask Oniguruma::OPTION_EXTEND" do
    res = @oregexp.options & Oniguruma::OPTION_EXTEND
    res.should > 0
  end
  
  it "should not mask Oniguruma::OPTION_MULTILINE" do
    res = @oregexp.options & Oniguruma::OPTION_MULTILINE
    res.should == 0
  end
end

describe Oniguruma::ORegexp, ".source" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+')
  end
  
  it "should return '[a-z][a-z0-9_]+'" do
    @oregexp.source.should eql('[a-z][a-z0-9_]+')
  end
end

describe Oniguruma::ORegexp, ".to_s" do
  it do
    o = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+')
    o.to_s.should eql("(?-imx:[a-z][a-z0-9_]+)")
  end
  
  it do
    o = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      :options => Oniguruma::OPTION_IGNORECASE)
    o.to_s.should eql("(?i-mx:[a-z][a-z0-9_]+)")
  end
end

describe Oniguruma::ORegexp, ".inspect" do
  it do
    o = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+')
    o.inspect.should eql("/[a-z][a-z0-9_]+/")
  end
  
  it do
    o = Oniguruma::ORegexp.new('[a-z][a-z0-9_]+',
      :options => Oniguruma::OPTION_IGNORECASE)
    o.inspect.should eql("/[a-z][a-z0-9_]+/i")
  end
end