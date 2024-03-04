# mygrep_project
Small clone of grep tool from Linux.

In mygrep directory is project files for visual studio and Release build directory contains build version of program.

To run program in command prompt folllow these instructions.
  1. Make sure you are in correct directory example "C:/Downloads/mygrep_prjoect/Release build>".
  2. Run program typing "mygrep" and hit enter.

     This will run function where you need to type line and then you can search parts of that line and program will output which position that search is in the original line.
  3. Full functions of this programs are that it can search lines from text file with couple options.
     
     These options are  [-oo | -ol | -olo | -or | -oi | -olori]
     
     -oo Will give you amount of occurences of search.
     
     -ol Will give you line numbers where search apears.
     
     -olo Will give you lines, line numbers and amount of occurences based on search.
     
     -oi Will ignore upper and lower cases on search.
     
     -olori Will use all options at the same time.
     
  4. Finally running full program type "mygrep <filename> <search> [-oo | -ol | -olo | -or | -oi | -olori]".
