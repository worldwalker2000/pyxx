# pyxx

Python but with a C/C++ style.  

**WARNING: Please don't use for real code, this will change and some things are very broken.**  

- You can now write x++; (and the -- as well)
- Lines end with a semicolon
- {} for blocks not indentation
- ! instead of "not"
- || and && instead of "or" and "and"
- "true" and "false" instead of "True" and "False"

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

# Usage
The Makefile uses clang++ and sets the c++ standard to 17.  
```bash make```  
```bash ./pyxx [FILES]```

# Future Plans
- Allow for mulit-line lambda functions
- Syntax highligting for vim, emacs, and vscode
- Maybe.. make python's optional static typing required

# Know issues
- things in quotes double and single
- lambdas
- some strange brace arangments

# FAQ
Why the name pyxx?
Because c++ files can have .cxx instead of .cpp
