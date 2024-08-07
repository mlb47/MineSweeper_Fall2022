# Project 2 - Minesweeper
[![Points badge](../../blob/badges/.github/badges/points.svg)](../../actions)

## Project Outcomes:
Develop a C++ program that uses:
* Dynamic memory
* Multi-dimensional arrays
* Recursion

## Background Information:
### Project Overview:
Minesweeper, like most video games, is a wellknown time killer, and people have
spent **tons** of time playing it. Up until Windows 8, Minesweeper came
pre-installed on all Windows devices. It can still be downloaded from the
Windows App Store, or it can be played online, at links such as
http://minesweeperonline.com/#beginner.

Your task for this project will be to create a playable version of Minesweeper.
Our version will be displayed using a table and some basic Unicode characters,
see [example below](#sample-board-display).

A list of Unicode characters can be found on Wikipedia at
https://en.wikipedia.org/wiki/List_of_Unicode_characters. 2691 and 25A2 are the
values used in the project.

### How is minesweeper Played
The goal of Minesweeper is to clear a minefield of its mines. If you are not at
all familiar with the game, please fiddle around with it a bit to gain full
understanding http://minesweeperonline.com/. Generally there are 4 cell types
that will require unique actions when clicked.

1. You will use left-click to "check" and right-click to "flag" a cell.
1. If you accidentally check a location that has a mine, the mine explodes and
   the game is over.
1. If you check a location that does not have a mine, and none of its 8
   adjacent locations have mines either, that cell should display `▢`, to
   indicate that the location has been cleared of mines.
   1. In addition, all adjacent locations that are not mines will be
      automatically cleared. This action should **recursively** apply to its
      neighbors and so on until the entire region is cleared.\ ![Minesweeper
      search expansion](static/expand-search.gif)
1. If you check a location that has 1 mine in the 8 cells that surround it, it
   should display 1.
    1. If 2 mines exist in the cells surrounding the location you checked, you
       should display 2, and so on.
1. If you believe that a cell will have a mine, you can flag the cell. This
   does not make the mine explode but makes it clear that a mine is expected to
   exist there.
1. To win, you must have all cells without mine cleared. The rest of cells
   are either flagged of left alone.

Once all cells except the mines have been checked, the minefield is considered
"cleared" and you win.

### Project Requirements:
Your application must function as described below:
+ Your program should prompt the user for the name of an input file to use.
+ That input file should be read in and used to create the game board.
  + Show an error message and ask user to input again if the file fail to open
+ Game play continues by showing the user the current status of the board and
  asking for their next move.
  + Moves can be one of two types:
    + Click a cell, for example `c 2 3` shall search the cell at row 2,
      column 3.
    + Toggle the placement of a flag, e.g. `f 6 0` would place a flag at the
      cell in row 6, column 0. If a flag already exists at that location,
      then remove the flag.
  + Both upper and lower case command `c`, `C`, `f`, `F` are accepted.
  + Invalid inputs should trigger an error message.
    + Wrong commands: `z 0 0`
    + out-of-boundary coordinate
    + click, or flag a "cleared" cell

#### Sample Board Display
```
    0   1   2   3
  +---+---+---+---+
0 | ▢ | ▢ | 1 | 1 |
  +---+---+---+---+
1 | 1 | 1 | 2 |   |
  +---+---+---+---+
2 | ⚑ | 2 | 4 |   |
  +---+---+---+---+
3 | 2 | ⚑ | 3 |   |
  +---+---+---+---+
```

#### Sample data
The input data will just be a file filled with spaces and asterisks. A space
indicates an empty cell, while an asterisk indicates a mine. The input that
would create the [sample board display](#sample-board-display) above can be
found in [four-by-four.in](test/four-by-four.in) and looks like this:
```

   *
*  *
 * *
```

## Code organization
Read the [Makefile](Makefile) for files required in this project. Hint: A .o
files required in the Makefile means a corresponding cpp file.

Read the tests in the cpp files in the [test](test/) directory for the expected
usages of all classes and functions.

### Class descriptions
+ Cell class

  The Cell class takes care of a cell. It should memorize its own status and
  keep some useful constants.

  + Status to keep track: hasMine, isFlagged, isCleared, adjacentMineCount.
  + Generate a string of 1 character to represent the current status.
  + Keep several constants of the characters to be used to display.

    Declarations in the class block as public
    ```
    static const std::string MINE;
    static const std::string FLAG;
    static const std::string NO_ADJACENT_MINES;
    static const std::string UNKNOWN;
    ```

    Initializations in the cpp file
    ```
    const std::string Cell::MINE = "*";
    const std::string Cell::FLAG = "\u2691";
    const std::string Cell::NO_ADJACENT_MINES = "\u25A2";
    const std::string Cell::UNKNOWN = " ";
    ```

+ Board class

  The Board class memorize the board status and required behaviors to interact
  with it.

  + Store a 2D dynamic array of the Cell objects ``Cell **field``
  + Load a file to fill in the 2D array

    May need two rounds of file read. First to find the dimension, and second
    to read the board.

  + Delegate cell options to cells and get the feedback.
  + The ``click`` method should be able to recursively expend the ``cleared``
    region.

    When a cell is successfully clicked, you should recursively click all
    neighboring cells (8 of them) that does not have a mine. You may need to
    implement a recursive helper function for this. Also, you may need a 2D
    array to memory cells that are already clicked in this expansion to avoid
    duplicate. This 2D array should be cleared before the start of the
    recursive expansion. Another option is to use a set/vector of pair to
    memorize the clicked positions. Up to you to choose.

+ TextMenuApp class

  This class drives the text menu based application.

  + The ``run`` method is the entry point to start the app.
  + The ``getPrompt`` method will return what needs to be displayed in the
    current round as a string.
  + The ``move`` method triggers a move of either click or flag at a certain
    position.
  + This is the only class to include the iostream header unless you are
    showing debugging info in other classes.

## Test your code locally before pushing
> **Warning**: We have limited GitHub Classroom Augograding Quota. Do not push
> after every single commit! Run tests locally first. Only push significant
> commits where you have just passed some or all tests.

+ Compile with ``make``
+ Pass all tests with ``make test-all``
+ Pass all test runs with ``make test-run``
+ Pass all memory leak check with ``make test-memory``. Skip if you do not have
  a local copy of valgrind. It is strongly recommended to install a local
  valgrind though. You can also test your code with valgrind on the SSH server.

## Sample run

```
Please enter a file name with the minefield information: test/bad.file
Please enter a file name with the minefield information: test/four-by-four.in
      0   1   2   3
    +---+---+---+---+
  0 |   |   |   |   |
    +---+---+---+---+
  1 |   |   |   |   |
    +---+---+---+---+
  2 |   |   |   |   |
    +---+---+---+---+
  3 |   |   |   |   |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c 0 0
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 |   |
    +---+---+---+---+
  1 | 1 | 1 | 2 |   |
    +---+---+---+---+
  2 |   |   |   |   |
    +---+---+---+---+
  3 |   |   |   |   |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c -1 0
Invalid move. Please enter your next move: z 2 2
Invalid move. Please enter your next move: f 3 3
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 |   |
    +---+---+---+---+
  1 | 1 | 1 | 2 |   |
    +---+---+---+---+
  2 |   |   |   |   |
    +---+---+---+---+
  3 |   |   |   | ⚑ |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c 0 1
Invalid move. Please enter your next move: c 0 3
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 | 1 |
    +---+---+---+---+
  1 | 1 | 1 | 2 |   |
    +---+---+---+---+
  2 |   |   |   |   |
    +---+---+---+---+
  3 |   |   |   | ⚑ |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c 3 2
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 | 1 |
    +---+---+---+---+
  1 | 1 | 1 | 2 |   |
    +---+---+---+---+
  2 |   |   |   |   |
    +---+---+---+---+
  3 |   |   | 3 | ⚑ |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c 2 2
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 | 1 |
    +---+---+---+---+
  1 | 1 | 1 | 2 |   |
    +---+---+---+---+
  2 |   |   | 4 |   |
    +---+---+---+---+
  3 |   |   | 3 | ⚑ |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c 3 0
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 | 1 |
    +---+---+---+---+
  1 | 1 | 1 | 2 |   |
    +---+---+---+---+
  2 |   |   | 4 |   |
    +---+---+---+---+
  3 | 2 |   | 3 | ⚑ |
    +---+---+---+---+
Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: c 2 1
      0   1   2   3
    +---+---+---+---+
  0 | ▢ | ▢ | 1 | 1 |
    +---+---+---+---+
  1 | 1 | 1 | 2 | * |
    +---+---+---+---+
  2 | * | 2 | 4 | * |
    +---+---+---+---+
  3 | 2 | * | 3 | ⚑ |
    +---+---+---+---+
You Win!
```

## Important Notes:
- Projects will be graded on whether they correctly solve the problem, and
  whether they adhere to good programming practices.
- Projects must be received by the time specified on the due date. Projects
  received after that time will get a penalty or zero.
- Never change the test files! The results you get will be pointless as they
  will not align with our grading.
- Never change the makefile unless you are asked to do so
- Please review the academic honesty policy.
  - Note that viewing another student's solution, whether in whole or in part,
    is considered academic dishonesty.
  - Also note that submitting code obtained through the Internet or other
    sources, whether in whole or in part, is considered academic dishonesty.
    **All programs submitted will be reviewed for evidence of academic
    dishonesty, and all violations will be handled accordingly**.

### Submission Requirements:
1. All code must be added and committed to your local git repository.
2. All code must be pushed to the GitHub repository created when you "accepted"
   the assignment.
   1. After pushing, with `git push origin main`, visit the web URL of your
   repository to verify that your code is there. If you don't see the code
   there, then we can't see it either.
3. Your code must compile and run. The auto-grading tests will indicate your
   score for your submission.
   1. The auto-grading build should begin automatically when you push your code
      to GitHub.
   2. If your program will not compile, the graders will not be responsible for
      trying to test it.
   3. You should get an email regarding the status of your build, if it does
      not pass, keep trying.
   4. We have limited quota to run autograding. Try to make your tests to pass
      locally before pushing it to the server. **Do not abuse the
      autograding!**
4. **Never remove provided files!** Some data file and input files are
   essential in testing and autograding.

## Grading
- Breakdown
  + 90 pts GitHub Auto-grading
  + 10 pts Code style
- Auto-grading results can be checked at the top of this document like as a
  badge ***40/90***.
- View details:
    1. On your GitHub repo page, Click the :arrow_forward: **Actions** tab to
       see your graded results.
    1. If it isn't a green check mark (:heavy_check_mark:) then at least part of
       the testing failed.
    1. Click the commit message for the failing version then click "Autograding"
       on the left side of the page.
    1. Follow the :x: path and expand things to see what errors exist.
    1. It is usually **education/autograding@v1** and you can expend this path to
       view the detail.
