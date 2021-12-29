# pyxx

Python but with a C/C++ style.

- You can now write x++; (and the -- as well)
- Lines end with a semicolon
- {} for blocks not indentation

The code gets transpiled into regular python by pyxx.

```pyxx main.pyxx``` -> main.py

```python
import random;

computer = random.randint(1, 10);
user = -1;
while user != computer {
  user = int(input("Enter a number: "));
  if user < computer {
    print("Too low");
  } else {
    print("Too high");
  }
}
```
converts into
```python
import random

computer = random.randint(1, 10)
user = -1
while user != computer :
        user = int(input("Enter a number: "))
        if user < computer :
                print("Too low")
        else :
                print("Too high")


```

Why the name pyxx?
Because c++ files can have .cxx instead of .cpp
