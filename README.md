# EaseFinance

Structures: Two structures are defined, User and Group, to store user information (name and balance) and group details (activity, total cost, user count, and user information).

Group Management:

The program can create and manage multiple groups (up to a maximum defined as Maximum_groups).
For each group, the program can store details like the activity, total cost, and user information.
Create New Group:

Users can create a new expense group by providing the number of members, member names, activity, total cost, and whether to split the bill equally or individually.
If users choose to split the bill equally, the program calculates the per-person cost and states that everyone paid equally.
If users choose to split the bill individually, they provide the amount paid by each member, and the program stores this information.
Load and Display Previous Group Details:

Users can load and display details of previously created groups.
This includes displaying the group's activity, total cost, user balances, and the amount owed by each member to others.
File I/O:

The program can save group details to a text file (easefinance.txt) and load them back.
It saves and loads information such as the number of groups, user counts, activity names, total costs, and user balances.
User Interface:

The program provides a simple user interface where users can choose from options like creating a new group, loading previous group details, or exiting the program.
After each action, the program returns to the main menu, allowing users to perform further actions.
The code manages the essential functionalities of an expense-sharing application, allowing users to input group details, calculate owed amounts, and save/load these details from a file. Note that the provided code might need further refinement and error handling to be robust for real-world use.****
