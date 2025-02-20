Description

This project is a simple project management system that allows users to initialize milestones and activities, ensure unique IDs, and update activities as they progress. The user interacts with the system through a menu-based interface.

Files

1. a1_functions.h

Contains function prototypes and necessary structure definitions.

2. a1_functions.c

Implements the functions declared in a1_functions.h, including milestone and activity initialization, project creation, and updating functions.

3. a1_data_structures.h

Defines the data structures for milestones, activities, and the project.

4. a1_main.c

Contains the main function, which handles user interaction, milestone and activity setup, and the main program loop.

Compilation

To compile the program, use the following command:

gcc -o project_manager a1_main.c a1_functions.c -Wall -Wextra -std=c11

Usage

Run the executable:

./project_manager

Follow the on-screen prompts to manage milestones and activities.

Features

Initialize project milestones and activities

Ensure unique milestone and activity IDs

Update activity completion status

Display project statistics

Author

Dorian Bansoodeb
