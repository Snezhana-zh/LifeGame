# LifeGame
Program requirements:  
Be able to read the “universe” from a file. The universe is described by (a) the cell transition rule; (b) field size; (c) the state of the cells.  
The file name is changed when the program starts.  
If the file is not submitted, start the game on a randomly initialized field of some fixed size.  
Third mode (“offline”): the program is given an input file, the number of iterations, and an output file. The program calculates the state of the field after the specified number of iterations and saves the universe to the specified output file.  
After the game starts, the program waits for the command:  
dump - save the universe to a file  
tick - calculate n (default 1) iterations and print the result. The name of the universe, the transition rule, should be displayed on the screen in front of the printed field.  
exit – end the game.  
help – print the help about the commands.  
print - print the field, the name of the universe and the transition rule.  
The field of play is considered closed (toroidal). Thus, the neighbors on top of the first row of the field are the cells of the last row and vice versa, similarly for the left and right edges of the universe.  
File format:  
Life 1.06 .  
Addition to the format:  
The first line of the file contains a comment with the name of the universe (any string).  
Example:  
#N My universe.  
The second line of the file should contain a comment with the following transition rule:  
#R Bx/Sy,  
where x and y are sequences of different digits from the set {0...8}.  
The sequence under the letter B (birth) contains the number of living cells necessary for the "birth" of the cell, under the letter S (survival) - cells necessary for the "survival" of the cell.  
The third line contains the size of the field.  
The name of the universe and the transition rule may be missing. By default, the name "My Universe" and the mode "B3/S23" will be used.
