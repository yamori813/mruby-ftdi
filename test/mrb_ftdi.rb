##
## Ftdi Test
##

assert("Ftdi#hello") do
  t = Ftdi.new "hello"
  assert_equal("hello", t.hello)
end

assert("Ftdi#bye") do
  t = Ftdi.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Ftdi.hi") do
  assert_equal("hi!!", Ftdi.hi)
end
