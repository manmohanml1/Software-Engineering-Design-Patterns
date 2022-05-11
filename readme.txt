CSCI 250 
Project 1-Part 2:
//I have my working model using design based on UML diagram saved as UML_Old_Design, and saved the file as proj1-2(Old Design).cpp.
//I have reworked the design using design UML_New_Design, and saved the file as proj1-2.cpp.(Please see that as I tried at the last moment as best to improve my design.)

1. A  hierarchical  structure  of  Fresno  State.  Please  refer  to  detailed  the  structure 
below. You will be required to manually build the structure per the attached figure 
in the main function. 

Ans: I have used a Dynammic way to create the Hierarchy, which lets User creates as they wish.

2. Please introduce 3 listservs.  
a. 1st listserv is for the entire Fresno State. All users within the hierarchy of 
Fresno State should subscribe to this listserv.  
b. 2nd listserv is CSM listserv that includes all members of CSM department 
c. 3rd listserv is CSci listserv that includes all members of CSCi department. 

Ans: I have made three ListServers - 
     1) For the entire Fresno State and all the users within it.
     2) I have made a dynammic College ListServer which creates a ListServers for that particular College.
     3) I have made a dynammic Department ListServer which creates a ListServers for that particular Department.

Note: in reality an academic unit may have multiple listservs. For example, Fresno State 
emergency  listserv  to  all  campus  members  and  Fresno  State  faculty  listserv  to  only 
faculty members. Your design may vary either based on the reality or based on the 
simplified fictional scenarios below. You will earn extra points if your design follows the 
reality. 
 
Scenarios (please implement them at suitable places): 
Scenario 1: Introduce an emergency message to send out to the entire Fresno State. //I have implemented this.
Scenario 2: 
a. Add a few new departments and then delete some existing department. //I have given a dynamic option for user to create as many Departments they want and also delete them.
b. Introduce a regular college message send to the updated CSM members. //I have done this aswell by notifying using the college ListServer.
Scenario 3:  
c. Add a few new members and then delete some existing members.//I have given a dynamic option for user to add as many Faculty or Students they want and also delete them.
d. Introduce a regular departmental message send to the updated CSCI members. //I have done this aswell by notifying using the Department ListServer.
 
Optional Scenarios for those who choose to implement the “reality” version. 
Scenario 4: Introduce an announcement message to send out to the entire Fresno State 
faculty. // I have halfway implemented this.
Scenario 5: Introduce an announcement message to send out to the entire CSCI students. // I have halfway implemented this.
 
BONUS POINTS (25 pts): Proxy pattern and Command Pattern 
1. A proxy that will delay to send an announcement until 10 seconds later (10 pts) 
2. A command that can undo the announcement before 10 seconds is over (15 pts)  


Solution:

UML Diagram: I have combined and used the composite and observer design pattern to implement this part.

The advantages of this design are:
1. I am easily able to observe different observers, i.e add them to List Server where notification can be sent to the different members in it.
2. I am also able to observe the behavior of different members as they are added and removed in the hierarchy.
3. I am able to easily create and add dynammically different Colleges, Departments, Faculty Members, Student Members in the Hierarchy and ListServers as well.
4. I am able to easily update the members subscrtibed to the listserver of new updates, such as member leaving, member addition as well.
5. It promotes loose coupling between objects that interact with one another (in this case, College, Department, Faculty, and Students).
6. Using the composite pattern helped in dealing with complex(sub-nodes) and simple(leaf) uniformly. As, it is easier to create either.
7. I have created a recurring menu, which has wide range of options to choose from. It is user firendly, also dependent on them to make use of it as they see fit.
8. I have followed all the SOLID principles.

The disadvantages of this design are:
1. To control the dynamic addition of members(Faculties and Students) in department, college can add complexity and lead to performance issues, when doing operations on them.
2. It can be difficult to build a consistent interface for classes with vastly different features (in this case, Composite and Leaf).
3. By, givng user to create a lot of things themselves. It consumes a lot of time for some redundant work.

