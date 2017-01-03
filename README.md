# Implementation of a *minimalistic Pythonish string* class in C++

The project was created for the course [Programming 3](https://sluzby.fmph.uniba.sk/infolist/en/1-AIN-171).
The following methods are *(somehow)* implemented.

```
[
    '__add__',
    '__eq__',
    '__ge__',
    '__getitem__',
    '__gt__',
    '__init__',
    '__iter__',
    '__le__',
    '__len__', # .lenght()
    '__lt__',
    '__mul__',
    '__ne__',
    '__str__',
    'capitalize',
    'center',
    'count',
    'endswith',
    'find',
    'index',
    'isalnum',
    'isalpha',
    'isdigit',
    'islower',
    'isprintable',
    'isspace',
    'isupper',
    'ljust',
    'lower',
    'lstrip',
    'replace',
    'rfind',
    'rindex',
    'rsplit',
    'rstrip',
    'split',
    'startswith',
    'strip',
    'swapcase',
    'title',
    'upper',
    'zfill'
]
```

## Documentation

There are several ways to create the *ZString* object. 
```
ZString s1;  // creates an empty ZString
ZString s2('c');  // ZString contains 1 character
ZString s3("string");  // ZString contains an array of characters

s3.length() == 6;
```

You can do comparison,
```
ZStrin("abc") < ZString("cba");  // true
ZStrin("abc") <= ZString("cba");  // true
ZStrin("abc") >= ZString("cba");  // false
ZStrin("abc") > ZString("cba");  // false
ZStrin("abc") == ZString("cba");  // false
ZStrin("abc") != ZString("cba");  // true
```

concating & multipling *ZString*.
```
ZStrin("abc") + ZStrin("def") == ZStrin("abcdef");
ZStrin("abc") * 3 == ZStrin("abcabcabc");
```

Iterate over *ZString*
```
for(auto c: ZString("abc")) {
    cout << c;
}
// prints: "abc"
```

or print it directly.
```
cout << ZString("abc");
```

Find substrings
```
ZString("abcb").find(ZString("b")) == 1;
ZString("abcb").find(ZString("b"), 2) == 3;  // starts on a specific index
ZString("abcb").rfind(ZString("b")) == 3;  // or find the rightmost occurence
ZString("abcb").rfind(ZString("nope")) == -1;

ZString("abcb").index(Zstring("nope"));  // raises an error
```

count them
```
ZString("abcb").count(ZString('b')) == 2;
```

and replace them.
```
ZString("abcb").replace(ZString('BE')) == ZString("aBEcBE");
```

Do some basic *ZString* manipulation,
```
ZString("one TWO three").capitalize() == ZString("One two three");
ZString("one TWO three").lower() == ZString("one two three");
ZString("one TWO three").upper() == ZString("ONE TWO THREE");
ZString("one TWO three").swapcase() == ZString("ONE two THREE");
ZString("one TWO three").title() == ZString("One Two Three");
ZString("one").center(5, '#') == ZString("#one#");
ZString("one").ljust(5, '#') == ZString("##one");
ZString("one").zfill(5) == ZString("00one");
```

even check some properties.
```
ZString("one123").isalnum() == true;
ZString("one").isalpha() == true;
ZString("123").isdigit() == true;
ZString("one").islower() == true;
ZString("ONE").isupper() == true;
ZString("one").isprintable() == true;
ZString(" \t\n").isspace() == true;
```

And more...
```
ZString(" one123 \t ").strip(" \t") == ZString("one123");  // or .rstrip() .lstrip()
ZString("one123").startswith(ZString("one")) == true;
ZString("one123").endswith(ZString("123")) == true;

vector <ZString> arr = ZString("one two three").split();
arr.size() == 3;
arr[0] == ZString("one");
arr[1] == ZString("two");
arr[2] == ZString("three");
```

## Reference

- https://docs.python.org/3/library/stdtypes.html#str
- https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
- http://stackoverflow.com/questions/33638433/setup-google-test-in-clion
- http://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
- http://stackoverflow.com/questions/8164567/how-to-make-my-custom-type-to-work-with-range-based-for-loops
- http://stackoverflow.com/questions/3623263/reverse-iteration-with-an-unsigned-loop-variable

