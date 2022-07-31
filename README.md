# Shel 3.0
This is a small personal unix-shell implementation project.

It's based on well known <b>bash</b> shell.

## Install

Make sure to check all the dependecies (listed below). So far there is user-friendly installation module. (Python script is in progress..)

To <b>install</b> and run use the following command:

<code>make run</code>

## Basic control

Shel is aimed to be as user-friendly as possible. It should behave almost exactly the same as <b>bash</b>. Note that Shel still does not support:

```diff
- Scripting
- I/O Redirection
+ Tab Autocomplete
+ Command History
+ Arrow input
```

## Builtins

So far there are just couple of builtins, you can check them by running the command:

<code>help</code>

## Dependencies

The project is aimed to be as <i>extra</i> dependecies free as possible. Most of commonly used linux distributions (btw i use arch) should already be equiped with these dependecies.

<img src="https://img.shields.io/badge/Xterm-372-lightgrey?style=for-the-badge&logo=appveyor"> <img src="https://img.shields.io/badge/Readline-8.1-lightgrey?style=for-the-badge&logo=appveyor"> <img src="https://img.shields.io/badge/GNU make-4.3-lightgrey?style=for-the-badge&logo=appveyor">