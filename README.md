# Tic-Tac-Toe
Dynamic Tic-Tac-Toe using Alpha Beta AI

##Instructions:
1. Use make or visual studio to compile (c++11 or greater).
2. Run.
3. Follow on screen instructions.

##Explanation
###Difficulty
When selecting difficulty you are really selecting the depth bound of the AI's search.
The higher the number the more "into the future" the AI can see and evaluate an optimal move.
Picking a lower number makes it easier and the AI more deceiving.
If the AI is taking a long time to choose its next move try lowering this number.
I have found that even with low difficulty the AI is still not possible to beat.

###Board Size
You can pick the size of the board to go beyond just a normal 3x3 game.
Note that this is exponential and therefore increases the time it takes for the AI to choose a move.
Winning a game with higher board sizes is increasingly more difficult by nature. To be truly effective a new scoring system should be implemented but I did not have time.
