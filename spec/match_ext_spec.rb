require File.dirname(__FILE__) + '/spec_helper.rb'

describe MatchData, ".offset" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('1+2+')
    @string  = "11221122"
  end
  
  it "should equal 0, 4" do
    @oregexp.match(@string).offset.should eql([0,4])
  end
  
  it "should equal 1, 4" do
    @oregexp.match(@string, 1).offset.should eql([1,4])
  end
  
  it "should equal 4,8" do
    @oregexp.match(@string, 2).offset.should eql([4,8])
  end
  
  # def test_match
  #    reg  = Oniguruma::ORegexp.new( '1+2+')
  #    s  = "11221122"
  #    assert_equal( [0,4], reg.match( s ).offset )
  #    assert_equal( [1,4], reg.match( s, 1 ).offset )
  #    assert_equal( [4,8], reg.match( s, 2).offset )
  #    
  #    reg  = Oniguruma::ORegexp.new( '(?<=2)1+2+')
  #    assert_equal( [4,8], reg.match( s, 4 ).offset )
  #    assert_equal( nil, reg.match( s[4..-1] ) )
  # end
end

describe MatchData, ".offset (with look-behind)" do
  before(:each) do
    @oregexp = Oniguruma::ORegexp.new('(?<=2)1+2+')
    @string  = "11221122"
  end
  
  it "should equal 4,8" do
    @oregexp.match(@string, 4).offset.should eql([4,8])
  end
  
  it "should be nil" do
    @oregexp.match(@string[4..-1]).should be_nil
  end
end
