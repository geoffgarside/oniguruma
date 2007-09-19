require File.dirname(__FILE__) + '/spec_helper.rb'

describe String, "Oniguruma extension" do
  before(:each) do
    @string = 'hello'
  end
  
  def do_sub(meth)
    @string.send(meth, '[aeiou]', '*')
  end
  
  def do_sub_block(meth, &block)
    @string.send(meth, '.', &block)
  end
  
  it "should sub and return h*llo" do
    do_sub(:osub).should eql('h*llo')
    @string.should_not eql('h*llo')
  end
  
  it "should sub with block and return '104 ello'" do
    do_sub_block(:osub) {|s| s[0].to_s + ' ' }.should eql('104 ello')
    @string.should_not eql('104 ello')
  end
  
  it "should sub! and equal h*llo" do
    do_sub(:osub!)
    @string.should eql('h*llo')
  end
  
  it "should sub! with block and equal '104 ello'" do
    do_sub_block(:osub!) {|s| s[0].to_s + ' ' }
    @string.should_not eql('104 ello')
  end
  
  it "should gsub and return h*ll*" do
    do_sub(:ogsub).should eql('h*ll*')
    @string.should_not eql('h*ll*')
  end
  
  it "should gsub! and equal h*ll*" do
    do_sub(:ogsub!)
    @string.should eql('h*ll*')
  end
end
