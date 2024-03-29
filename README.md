# Shel 3.0
This is a small personal unix-shell implementation project.

It's based on well known <b>bash</b> shell.

## Install

Make sure to check all the dependecies (listed below). So far there is <b>no</b> user-friendly installation module. (Python script is in progress..)

To <b>install</b> and run use the following command:

<code>make run</code>

## Basic control

Shel is aimed to be as user-friendly as possible. It should behave almost exactly the same as <b>bash</b>. Note that Shel still does not support:

```diff
- Scripting
- I/O Redirection
+ Background command execution
+ Tab Autocomplete
+ Command History
+ Arrow input
```

## Builtins

So far there are just couple of builtins, you can check them by running the command:

<code>help</code>

## Supported fonts

Tested fonts:

```diff
+ Monospace
+ Liberation
+ CascadiaCode
```

## Dependencies

The project is aimed to be as <i>extra</i> dependecies free as possible. Most of commonly used linux distributions (btw i use arch) should already be equiped with these dependecies.

<img src="https://img.shields.io/badge/Xterm-372-lightgrey?style=for-the-badge&logo=appveyor"> <img src="https://img.shields.io/badge/Readline-8.1-lightgrey?style=for-the-badge&logo=appveyor"> <img src="https://img.shields.io/badge/GNU make-4.3-lightgrey?style=for-the-badge&logo=appveyor">

### GNU Readline Library

The readline library is commonly used among variety of shells. At first glance it might look lazy not to use linux sys calls (which appear commonly in the program) however, only the <i>input-interaction</i> is provided by the GNU Readline Library.

<hr>

## Gallery <br>

<a href="https://imgur.com/mOaRscX"><img src="https://i.imgur.com/mOaRscX.png" title="source: imgur.com" /></a>
<a href="https://imgur.com/qXH2gEl"><img src="https://i.imgur.com/qXH2gEl.png" title="source: imgur.com" /></a>
<hr>
