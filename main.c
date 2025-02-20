/********* a1_functions.c ********
	 Dorian Bansoodeb
*/


//Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include "a1_functions.h"
//#include "a1_data_structures.h"
#define max_milestones 5


int main()
{

    /** 1-  Display a welcome message **/
    char project_name[50];
    unsigned short int num_milestones;
    
    /** 1-  Display a welcome message **/
    printf("Welcome to ABC Company project manager!\n");


    /** 2- Get the project's name and number of milestones **/
    printf("What is the project's name?\n");
    scanf("%s",project_name);
    printf("How many Milestones are in the project?\n");
    num_milestones = get_input_usi();
    while(!(1<=num_milestones&&num_milestones<=5)){
        printf("Value must be between 1-5\nHow many Milestones are in the project?");
        num_milestones = get_input_usi();
    }

    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/
    //creates the array which contains all 5 of the milestones' information
    milestone_t arr_milestones[max_milestones];
    int id_number=0;
    short unsigned int id_list[max_milestones];
    unsigned short int activity_id_list[15];
    int total_activity_counter = 0;
    int activity_list[max_milestones];
    unsigned short int num_activities;
    unsigned short int milestones_initialized = 0;
    //ask user for important information for the milestone
    for(int milestone =0;milestone<num_milestones;milestone++){
        milestones_initialized+=1;
        printf("How many activities are there in milestone #%d?",milestone+1);
        num_activities = get_input_usi();
        
        while(!(1<=num_activities&&num_activities<=3)){
            printf("Value must be between 1-3\nHow many activities are there in milestone #%d?",milestone+1);
            num_activities = get_input_usi();
        }
        activity_list[milestone]=num_activities;
        total_activity_counter+=num_activities;

        //initializes a milestone
        init_milestone(&arr_milestones[milestone],num_activities);

        //checking uniqueness
        ///creates a array of id
        int milestone_act_count = 0;
        for(int j =0+total_activity_counter-num_activities;j<total_activity_counter;j++){
            
            activity_id_list[j]=arr_milestones[milestones_initialized-1].activity_list[milestone_act_count].id;
            milestone_act_count++;
        }
        
        if(unique(activity_id_list,total_activity_counter)==0){
            while((unique(activity_id_list,total_activity_counter))==0){
                printf("This milestone's activities aren't unique!\nPlease input unique activities\n");
                printf("Current list of IDs:\n");
                if(milestones_initialized==1){
                    printf("No ID list\n");
                }
                else{
                    for (int i=0;i<total_activity_counter-num_activities;i++){
                        printf("%u ",activity_id_list[i]);
                    }
                }
                for(int i =0;i<num_activities;i++){
                    printf("Input a valid ID for Actvity #%d of Milestone#%d\n",i+1,milestones_initialized);
                    arr_milestones[milestones_initialized-1].activity_list[i].id = get_input_usi();
                }
                int milestone_act_count = 0;
                for(int j =0+total_activity_counter-num_activities;j<total_activity_counter;j++){
                    
                    activity_id_list[j]=arr_milestones[milestones_initialized-1].activity_list[milestone_act_count].id;
                    milestone_act_count ++;
                }

            }
            

        }
        //checks for uniqueness of the milestone ids      
        if(milestones_initialized!=1){
            for(int i = 0;i<milestones_initialized;i++){
                id_list[i] = arr_milestones[i].id;
            }
        }   while(unique(id_list,milestone+1)==0){
                printf("The most recent Milestone ID is not unique!\n");
                printf("Current Milestone ID List:\n");
                for (int k = 0;k<milestone;k++){
                    printf("%u ",arr_milestones[k].id);
                }
                printf("\nPlease input a valid ID for Milestone#%d",milestone+1);
                arr_milestones[milestone].id = get_input_usi();
                id_list[milestone]= arr_milestones[milestone].id;
            }   
    }
    
    /** 4- Initialize the project **/
    
    project_t project = init_project(project_name,arr_milestones,num_milestones,activity_list);
    
    /** 5- Print the main menu **/
    print_main_menu();
    unsigned short int answer =0;

    /** 6- Get user choice and handle it as per the instructions**/
    
    int choice = 0;
    _Bool correct =0;
    int first2=0;
    //loops as long as choice isnt 3, once it is 3, the function stops
    while(choice!=3){
        //makes it so it prints the main menu on and after the second passthrough
        if(first2!=0){
            print_main_menu();
        }
        first2++;
        choice = get_input_usi();
        //checks that choice of the user is 1 or 2 or 3
        while(!(choice==1||choice==2||choice==3)){
            printf("Please input 1,2,or 3");
            choice = get_input_usi();
            print_main_menu();
        }
        if(choice==1){
            //performs submenu action when chosen 1
            for(int milestone=0;milestone<num_milestones;milestone++){
                for(int activity = 0;activity<activity_list[milestone];activity++){
                    printf("Activity Name:%s  Activty ID:%u ",arr_milestones[milestone].activity_list[activity].name,arr_milestones[milestone].activity_list[activity].id);
                    if (arr_milestones[milestone].activity_list[activity].completed==1){
                        printf(" Completed");
                    }
                    printf("\n");
                }
            }
            printf("\nWhich Activity do you want to modify? Input ID\n");
            answer = get_input_usi();
            int first = 0;
            correct = 0;
            //loops until a valid id is provided (not completed and is an existing ID number)
            while(correct==0){
                if(first!=0){
                    printf("\nIncorrect ID or is complete!\n");
                    printf("Which Activity do you want to modify? Input ID\n");
                    answer = get_input_usi();
                }
                first++;
                for (int i = 0;i<num_milestones;i++){
                    for(int j = 0;j<activity_list[i];j++){
                        if(arr_milestones[i].activity_list[j].completed ==1&&correct==0){
                            correct =0;
                        }
                        else if(answer == arr_milestones[i].activity_list[j].id){
                            correct=1;
                            update_activity(&arr_milestones[i].activity_list[j]);
                            update_milestone(&arr_milestones[i],activity_list[i]);
                            update_project(arr_milestones,num_milestones,activity_list,&project);

                            

                        }
                    }
                }   

            }

        }
        if (choice==2){
            //performs a stat display when chosen 2
            print_project_stats(project,arr_milestones,num_milestones,activity_list);
        }

    }

    return EXIT_SUCCESS;
}