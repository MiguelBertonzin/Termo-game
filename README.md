Project Description: "Termo" Logic Game in C++

Summary

The "Termo" project was developed in C++ as an interactive application that allows the user to find randomly chosen five-letter words. The application simulates the game available at term.ooo, where the player must guess words based on feedback regarding their attempts.


Features


Word List: The game words are stored in a dynamic linked list. The user can add and remove words from this list through an interactive menu.

File Storage: Upon starting the program, the word list is loaded from a text file, and at the end of the game, the changes are saved back to the file.

Guessing System: The user can choose to play with 1, 2, 3, or 4 words simultaneously, with a defined number of attempts (6, 8, 10, or 12 attempts, respectively).

User Feedback: After each attempt, the game informs which letters are correct and in the correct position, and which are correct but in the wrong position, using a textual representation.

Attempt History: The user's attempts are stored in another linked list, displaying a history that facilitates tracking the player's progress.

Implementation


Data Structures: The game was implemented using linked lists, avoiding the use of built-in structures in the language, such as vector or list. The word list and the attempt list were carefully designed to meet the needs of the game.

Functions: The application uses various functions to manage the game logic, manipulate linked lists, read from and write to files, and interact with the user. The logical structure of the code is clear, with good indentation and explanatory comments.

User Interaction: The main menu allows the user to intuitively choose options, facilitating the inclusion and removal of words, as well as the selection of the game mode.
