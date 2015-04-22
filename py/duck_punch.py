import pytest
import types

def test_single_object_method_association():
    """Show how to associate new members to existing object instances"""
    class SimpleObject:
        def __init__(self):
            pass

    o = SimpleObject()
    # So you can see from the class definition above, SimpleObject 
    # instances don't have a new_method member. Let's just prove that.
    with pytest.raises(AttributeError):
        o.new_method()

    # Now let's associated such a member with the particular instance o
    def just_return(value): return value
    o.new_method = types.MethodType(just_return, 22)

    assert o.new_method() == 22
    # that's it!

    # Let's prove it hasn't changed the class definition
    o2 = SimpleObject()
    with pytest.raises(AttributeError):
        o2.new_method()