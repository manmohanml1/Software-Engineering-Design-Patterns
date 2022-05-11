CSCI 250 
Project 1(30%):
1. A maze is composed of various kinds of MapSite. For example, Room and Door. 
a. There are two kinds of Room (Magic Room and Enchanted Room). 
b. There are three kinds of Door (Bomb Door and Glass Door).  
c. There are 2*3 different kinds of Maze.  
Choose (a) suitable creational pattern(s) to implement this part. 
2. A Maze could be also configured based on its layout/representation. Client is 
allowed to input the number of rooms of a square Maze. Two layouts are 
available in a Maze. 
a. The first layout has all 4 doors in each room.   
b. The second layout is as follows: For each odd row, each even Room has 
WEST and EAST doors. For each even row, each odd Room has NORTH 
and SOUTH doors. 
c. Print the layout once it is done. 
3. Client can only instantiate one Maze object. Additionally, for each factory and 
builder class that you design, introduce a Singleton mechanism to allow only one 
object to be instantiated. 
4. (1), (2), (3) needs to be integrated together. 
5. Introduce a main function that executes all of the above features. 


Solution:
Q1) For this Question I hvae separately implemented in "project1part1.cpp".

UML Diagram is for the 1st question. I use the abstract factory to implement this part.

The advantages of this design are:
1. I am easily able to create factories of factories. 
2. It's easier to create different combination of rooms and doors.
3. This design makes it easier for code reusability, such as the Rooms and it's subclasses.
4. This design pattern helps us control the classes of objects, such as the Maze Factory that the main class creates.
   So from the main class we can manipulate the instances through their abstract class.
5. It is easier to instantiate the Factory as it is only instantiated once in the main class. SO, it's easier to say which Factory we want to use, such as EnchantedMaze, etc.

The disadvantages of this design are:
1. It's tough to introduce new concepts into maze like walls, paints, etc., without changing the source code.
2. Everytime we create a new room or door, then we need to create new factories if we want to use them.

Q2) For this Question I have implemented in "proj1-1". I have used matrix of objects of room in Maze to assign the matrix of rooms and have printed the expected output.

Q3) For this Question I have implemented in "". 

Q4) For this Question I have implemented in "proj1-1". I have integrated Q1 and Q2 in this file.

Q5) For this question I have implemented in all the files, so I am always using main class to execute the above requirements.
