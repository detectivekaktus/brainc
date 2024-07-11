# brainc
***THIS PROJECT IS IN AN EARLY STAGE OF DEVELOPMENT. DON'T EXPECT TOO MUCH!***

Brainc is a brainfuck programming language Just-In-Time (JIT) compiler written in pure C with no dependencies other than the C standard library. This project is made for learning purposes.

Brainfuck is an esoteric programming language which consists of only 8 instructions which makes it one of the easiest to implement programming languages in the backend part (interpreters, compilers and virtual machine) but at the same time it makes it difficult to write any good working program.

## Compilation
It's used *GNU Make* tool and any C compiler (either gcc or clang) to compile the source code. You can execute the following instruction in your terminal:
```console
make
```

You will find yourself with a new directory called `build` in the project's root folder in which you find the executable `brainc` which is the compiler itself.

## Contribution
Make sure to read the [CONTRIBUTING.md](https://github.com/detectivekaktus/brainc/blob/master/CONTRIBUTING.md) file before making pull requests to this repository.
