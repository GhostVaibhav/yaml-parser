# ypars

A simple YAML parser written in C++

## Productions for parsing

1. $[PROG] \Rightarrow [STMT]^*$
2. $[STMT] \Rightarrow [KEY] : [VALUE]$
3. $[KEY] \Rightarrow $ Key(`string`)
4. $[VALUE] \Rightarrow $ Value(`string`, `int`, `bool`, `float`, `null`), $[[STMT]^+]$

## Building the project

You can clone the repo using the `--recursive` flag to clone all the submodules.

```sh
git clone https://github.com/GhostVaibhav/yaml-parser.git --recursive
```

For building, you can simply use CMake. Following commands only provided for reference.

```sh
cmake ..
```

```sh
cmake --build .
```
