# brainc
***THIS PROJECT IS IN AN EARLY STAGE OF DEVELOPMENT. DON'T EXPECT TOO MUCH!***

Brainc is a toolset that allows you to execute brainfuck code efficiently due to its implementation written in pure C. For compilation, the toolset offers to its user only the x86-64 processor architechture; the files compiled are in *ELF64* format.

## Compilation
It's used *GNU Make* tool and any C compiler (either gcc or clang) to compile the source code. You can execute the following instruction in your terminal:
```console
make
```

You will find yourself with a new directory called `build` in the project's root folder in which you find the executable `brainc` which is the compiler itself.

## Usage
The toolset has the following flags:
| Flag     | Description |
| -------- | ----------- |
| `-i` `--interpret` | Interprets the source `.bf` file |
| `-c` `--compile` | Compiles the source `.bf` file down to ELF64 executable |
| `-o` `--output` | Used with `-c` flag. Compiles the source `.bf` file down to ELF64 executable with a specified name |

## Contribution
Make sure to read the [CONTRIBUTING.md](https://github.com/detectivekaktus/brainc/blob/master/CONTRIBUTING.md) file before making pull requests to this repository.
