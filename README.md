# Interactive Liquid Sorting Game (C)

A terminal-based university programming project. Rearrange colored liquid units between bottles until each non-empty bottle contains only one color.

## Features
- Choose between 2 and 7 bottles, each holding up to 3 units.
- Randomized starting arrangement with one empty bottle.
- Colored terminal output using ANSI escape sequences.
- Checks whether each move is valid and detects completion.
- Quit by entering `q` at a move prompt.
- Uses `struct`, dynamic memory allocation, and separate functions for game logic.

## Build and run
Requires a C compiler and a terminal that supports ANSI colors.

```bash
gcc -std=c11 -Wall -Wextra -o liquid-game game.c
./liquid-game
```

On Windows, with GCC/MinGW, run `liquid-game.exe` after compiling.

## How to play
1. Enter the number of bottles (2–7).
2. Enter the source bottle number, then the destination bottle number.
3. You may move the top unit only if the source is nonempty and the destination has space and is empty or has the same top color.
4. Continue until all nonempty bottles are full and contain a single color.

## Implementation notes
- The game generates a random arrangement; it does **not** guarantee every generated arrangement is solvable.
- Current input handling is basic: malformed input or end-of-file is not handled robustly.

## Context
Created as an individual university assignment. The repository contains the original C source code, not a prebuilt executable.