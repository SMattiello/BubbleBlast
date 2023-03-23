# BubbleBlast
University Examination Project Planning 2021/2022


The program initially presents itself with a short introduction to the game, built on a 5x6 grid.

![Untitled](https://user-images.githubusercontent.com/95342628/227276818-2dcdfb2c-3a20-40cb-b52f-c0da3ef1a445.png)

The application algorithm is based on a recursive chain in which a real "BRUTE FORCING" is performed, as all possible options are tested in order to find the best way to solve the problem.

Initially, the idea was to use file reading and writing to store the matrices of the various steps, in order to simplify debugging.

After testing this system, I decided to try a solution that exclusively used RAM memory. This solution proved to be significantly more efficient and faster than the previous one.

---

Through the solution function in a do-while loop, the recursive function "solver" is called, to which the initial matrix and the number of moves, which increases every time the solver function fails (it returns a bool value), are passed.

This function will return the exact number of minimum moves required to solve the given matrix.

![Untitled 1](https://user-images.githubusercontent.com/95342628/227276937-b70561fe-7b23-4ef4-831e-6360b39af7eb.png)


The solver function prepares the matrix for the solving process and manages the count of necessary moves.

It takes the matrix and scrolls it tending to make moves and if they do not return the empty matrix goes back to the previous function and starts again with an extra number of moves

![Untitled 2](https://user-images.githubusercontent.com/95342628/227277154-a35d00f3-eeb9-40e9-9bec-4fb29aa76cc6.png)


Next, the function explode decreases the value at that point in the matrix and if the value is zero, it explodes by calling four other functions that will start the explosion in the four directions.

Finally, the function endCheck only checks that the grid is composed entirely of zeros and returns true or false depending on the composition of the passed matrix.

To make the graphical interface more attractive, the system("cls") function is called at each move to clean up the console and show only the updated matrix.

DEBUG functions have been included in the programme so that the steps performed can be explained to the teacher and the programme can be tested in the best possible way
