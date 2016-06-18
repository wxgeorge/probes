# Goal is to write the following:
#
# class Person
#   include CheckedAttributes
#
#   attr_checked :age do |v|
#     v >= 18
#   end
#
#   attr_checked :gender do |v|
#     ![:male, :female].include?(v)
#   end
# end
#
# me = Person.new
# me.age = 39 # ok
# me.age = 12 # exception
#
#
# Source:
# (The Boss' Challenge, Chapter 6, Metaprogramming Ruby)

# Here's my first cut

module CheckedAttributesV1
  def attr_checked attr_name, &checker
    self.class_eval do

      setter = "#{attr_name.to_s}=".to_sym
      getter = attr_name
      instance_var_name = "@#{attr_name.to_s}"

      define_method setter do |value|
        raise "#{value} is not valid for #{attr_name}" if !checker.call(value)
        self.instance_variable_set instance_var_name, value
      end

      define_method getter do
        self.instance_variable_get instance_var_name, value
      end

    end
  end
end

class Person
  extend CheckedAttributesV1

  attr_checked :age do |v|
    v >= 18
  end

  attr_checked :gender do |v|
    ![:male, :female].include?(v)
  end
end

# it seems to work
begin
  me = Person.new
  me.age = 39 # ok
  me.age = 12 # exception
rescue => e
  puts "Error! #{e.to_s}"
end

begin
  me = Person.new
  me.gender = :non_binary
  me.gender = :male
rescue => e
  puts "Error! #{e.to_s}"
end

# Of course we've extended CheckedAttributesV1
# rather than including it as the problem requested

# I think I remember that there is a hook that runs when a module
# is included. It looks like this:

module ASneakyModule
  def self.included including_class
    puts "ASneakyModule being included!"
    puts "I'm being included by #{including_class}"
  end
end

class SomeClass
  include ASnekayModule
end

# (outputs the puts above)

# The reason this is sneaky is once we have a handle on the
# class through include, we can make it extend our earlier module
# ala

module CheckedAttributes
  def self.included including_class
    including_class.class_eval do
      extend CheckedAttributesV1
    end
  end
end

# et Voila!

class Person2
  include CheckedAttributes

  attr_checked :age do |v|
    v >= 18
  end
end

p2 = Person2.new
p2.age = 39 # ok
p2.age = 12 # exception!

# this surely differs from the books solution.

