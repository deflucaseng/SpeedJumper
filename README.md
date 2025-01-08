# SpeedJumper
### Developed by Lucas Eng


# About

This language/subsequent compiler is written as a follow on for the BaseJumper language I had developed whose compiler was based on Python. You could consider this a 
refactoring of sorts, now written in C++ which is far more performant than python. Generally speaking the project has remained similar in structure, though in future
iterations there are certainly many inefficiencies which could be removed, as far as certain conversions. This iteration is also generally much cleaner and more efficient
with far more safety checks than the previous python iteration. 


# Syntax

The syntax is intentionally meant to be very human readable (even more than python), so every line reads almost like a sentence. 

## Variable Assignment

```
x isnow 3
y isnow x
```
It uses the **isnow** keyword in order to assign variables.

## Evaluated Assignment

You can additionally use assignment statements which perform basic math or boolean operations. 
*These come in three varieties.*


### Numeric Evaluated Assignment

This language supports addition, subtraction, multiplication, and floor division

```
x isnow y plus 3
f isnow 7 minus 2
z isnow 3 times 5
k isnow b divided 8
```


### Boolean Comparative Assignment

This language supports and, or, nor, xnor, nand, and xnor
The case used for true and false do not matter here. 

```
a isnow true or false
b isnow F and k
c isnow false nor false
d isnow x xnor True
e isnow q nand o
f isnow r xnor g
```

### Numeric Comparative Assignment

This compares two numbers, and stores a boolean value depending on the comparison of the two numbers
This supports equal to and not equal to

```
y isnow f is equal to 3
z isnow g is not equal to 7
```

### Conditional Jump

One of the key aspects of this language which is the **jump** functionality utilizes a syntax which 
requires a variable, and thus this language does not directly support infinite looping (Though I suppose
you could if you wanted)


```
x isnow True
jump to 3 if x
```

This code would jump to the third line of written code. 

### Printing

Displaying involves using the display keyword followed by whatever variable name or value you would like to print

```
display 3
display true
display x
```

### Ending
At the end of the code block simply write end

```
end
```


### Important Notes


All files must be of the .eng format (lol)
Conditional jump to line n will jump to the nth line of WRITTEN code not the nth line of the text file. 

