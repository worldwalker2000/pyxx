# pyxx

Python but with a C/C++ style.  

**WARNING: Please don't use for real code, this will change and some things are very broken.**  

- You can now write x++; (and the -- as well)
- Lines end with a semicolon
- {} for blocks not indentation
- ! instead of "not"
- || and && instead of "or" and "and"
- "true" and "false" instead of "True" and "False"
- Multi-line lambda functions ex. \[\]\(...\) {...}. (Thank you to brendanzab#6008 for the idea to use this instead of the keyword lambda)

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

# Building
## Unix
```$ cmake .```  
```$ make```  
## Windows
Open in Visual Studio, go to open then CMake, select CMakeLists.txt, then Ctrl-F5 or use the GUI.  

Sorry Makefile chads, had to switch to cmake for windows users. make was throwing a fit on windows.

# Usage
```$ ./pyxx [FILES]```

# Future Plans
- Syntax highligting for vim, emacs, and vscode
- Maybe.. make python's optional static typing required

# Know issues
- None right now, feel free to make an issue if you find one as I am sure that their are some

# FAQ
Why the name pyxx?
Because c++ files can have .cxx instead of .cpp
