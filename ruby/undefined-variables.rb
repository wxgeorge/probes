# Ruby how handles references to undefined variables differently depending on the
# kind of variable requested (function-local, versus instance variable, versus class variable)
#
# a request for an undefined ...
#
#   class variable       results     in an exception
#   instance variables   results     non truthy
#   local variable       results     in an exception
#
# The code below show this behaviour

class Foo
  def initialize
    @bar = "bar"
    @@class_bar = "bar"
  end

  def check_bar
    puts "@bar is \"bar\"!" if @bar == "bar"
  end

  def check_class_bar
    puts "@@class_bar is \"bar\"!" if @@class_bar == "bar"
  end

  def check_foo
    puts "@foo is set!" if @foo
    if @foo
      puts "@foo is truthy!"
    else
      puts "@foo is not truthy!"
    end
  end

  def check_class_foo
    puts "@@class_foo is set!" if @@class_foo
  end
end

def try
  begin
    yield
  rescue => e
    puts ([e.to_s] + e.backtrace[0,3]).join("\n")
  end
end

try { Foo.new.check_bar }
try { Foo.new.check_foo }

try { Foo.new.check_class_bar }
try { Foo.new.check_class_foo }

def some_other_function
  bar = "bar"
  puts "bar = \"bar\"" if bar == "bar"
  puts "foo is set!"   if foo
end

try { some_other_function }
