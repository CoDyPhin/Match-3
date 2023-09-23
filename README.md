# Match-3 Tech Task


Developed by Carlos Lousada, using C++ and libSDL (SDL2, SDL2_image and SDL2_TTF).
 

Game Requirements Implementation:
- By default, the game area is an 8x8 grid, of 5 possible objects (5 colors).

- The player can interact by swapping horizontally or vertically adjacent objects, excluding diagonals. To do that, there is a piece selection system:
	- When there is no piece selected and a user clicks a piece (left mouse button down + left mouse button up, without dragging), that piece is selected;
	- When a piece is selected and the user clicks on another piece (left mouse button down + left mouse button up, without dragging), if that piece is horizontally or vertically adjacent to the selected piece (excluding diagonals), the pieces are swapped. Otherwise, the clicked piece will be selected.
	- When a piece is selected and the user clicks either on the same piece or outside of the board, that piece will be de-selected.
	- When the user starts a dragging movement on a piece (left mouse button down + mouse movement), that piece is instantly selected (disregarding any previous selection).
	- When the user ends a dragging movement (left mouse button up after a mouse movement), if the mouse position at the end is on top of an adjacent piece to the piece that the selected piece, the pieces are swapped. Otherwise, nothing happens.
	
- If a swap results in a vertical or horizontal (or both) sequence of 3 or more pieces of the same color, those pieces disappear and points are awarded to the user's score. For each board state, those points are calculated as follows:
	- Score(brokenPieces) =
		- 10 * brokenPieces,					brokenPieces <= 3
		- Score(brokenPieces - 1) - 10 * (brokenPieces - 2),	brokenPieces > 3.

- If a swap does not result in a valid sequence, the pieces switch back to their original positions;

- Any time there are open spaces in the board, pieces above empty objects fall down, filling the gaps, and new pieces spawn from the top of the grid, filling any remaining gaps.



Extra Implementation Details:

- To facilitate the user experience when playing the game, the currently selected piece is surrounded by an asset that resembles a four-dimensional arrow;

- There is a simple hovering system implemented. When hovering a button, it slightly changes its color. When in-game and hovering a piece, there is a green border around it;

- There is a simple animation system for movement, that works using velocity. This velocity was made independent of framerate (works with deltatime);

- The game has a menu system implemented:
	- Main Menu, which leads to the Play Menu, the Highscores screen on Quits the game;
	- Play Menu, which leads to each different game mode: Free Play, Time Trials and Challenges, or returns to the Main Menu;
	- Time Trials Menu, which allows the user to select the maximum play time to achieve a highscore (1 minute, 2 minutes or 5 minutes) or to go back to the Play Menu;
	- Challenges Menu, which allows the user to proceed to the Next Level or go back to the Play Menu;
	- During any game mode, the user can also select the option "Retry" to restart the game mode they're playing, or the Main Menu button to go back to the Main Menu.

- The game has, as mentioned before, 3 different game modes:
	- Free Play:
		The user can play freely, to achieve the highest score in as much time as they please (both shown on the left of the screen).
	- Time Trials:
		The user competes to achieve the highest possible score in under a specified ammount of time. When the time ends, the user is presented with a screen that allows them to compare their score with the previous saved highscore on the same gamemode, retry or return to the main menu.
	- Challenges:
		The user progresses in a level system (currently designed 10 simple levels), each of them with goals (that are shown on the right side of the screen during the level). If the user completes the level, he is redirected back to the Challenges menu, with an indication of which was the last level they cleared. If they fail the level, they are presented with a message that states that, as well as the option to retry or go back to the Main Menu. If the user completes all 10 levels, they are reset back to level 1.

- The game has a very simplistic save and settings system implemented:
	- There is a file (/Assets/saveFile.txt) that stores the highscores, the current level, and some simple resolution settings. THIS FILE, IF REQUIRED, SHOULD BE TAMPERED WITH VERY CAREFULLY. The minimum supported width and height are, respectively, 1024px and 680px. The default resolution has the same resolution as the background image (1024x768). To change these values, edit the two last values of the file. The game also supports 4 different display modes: Windowed (0), Fullscreen (1), Screen Native Fullscreen (2) and Borderless (3). To alternated between these, change the value that is on top of the resolution values (default is 0). The remaining top 4 values are, respectively, the highest score in under 1 minute, 2 minutes, 5 minutes and the current level. 


Any additional questions or details, contact me via:
Email: carlosdaniel.rl@gmail.com
Phone number: +351 911 787 408
LinkedIn: https://www.linkedin.com/in/carloslousada00/

My GitHub: https://github.com/CoDyPhin
