/********* a1_functions.c ********
	 Dorian Bansoodeb
*/

#include <stdio.h>
#include <string.h>
#include "a1_functions.h"

unsigned short int get_input_usi(void){
	int answer;
	scanf("%d",&answer);
	
	while(answer<0){
		printf("Please input a positive value\n");
		scanf("%d",&answer);
	}	
	return answer;
}

float get_input_f(void){
	float answer;
	scanf("%f",&answer);
	
	while(answer<0){
		printf("Please input a positive value\n");
		scanf("%f",&answer);
	}	
	return answer;
}

void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities){
	printf("Enter the Milestone Name\n");
	scanf("%s",milestone_to_int->name);
	printf("Enter the milestone id\n");
	milestone_to_int->id = get_input_usi();
	//initialize each activity in a milestone
	for(int i=0; i<num_activities; i++) {
		init_activity(&(milestone_to_int->activity_list[i]));
	}
	// creates a list of IDs to check for uniqueness
	unsigned short int id_list[3];
	for (int i =0;i<num_activities;i++){
		id_list[i] = milestone_to_int->activity_list[i].id;
	}
	milestone_to_int->actual_duration = 0;
	milestone_to_int->actual_cost = 0;
	milestone_to_int->completed = 0;
}

//function to initialize activity
void init_activity(activity_t * activity_to_int){
	unsigned short int id;
	char named [100];
	unsigned short int planned_cost;
	unsigned short int actual_cost;
	_Bool complete = 0;
	unsigned short int planned_duration;
	unsigned short int actual_duration;

	printf("What is the ID for the activity?\n");
	id = get_input_usi();
	printf("What is the name of the Activity?\n");
	scanf("%s",named);
	printf("What is the Planned Duration for the activity?\n");
	planned_duration = get_input_usi();
	
	activity_to_int-> id = id;
	strcpy(activity_to_int->name,named);
	activity_to_int->planned_cost = planned_duration*30;
	activity_to_int->actual_cost = 0; 
	activity_to_int->planned_duration = planned_duration;
	activity_to_int->actual_duration = 0;
	activity_to_int->completed = 0;

}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities){
	project_t project;
	float total_planned_cost =0;
	unsigned short int planned_duration = 0;

	project.actual_cost=0;
	project.actual_duration=0;
	project.completed=0;
	project.planned_cost = 0;

	strcpy(project.name,name);
	
	for (int i =0;i<number_milestones;i++){
		for (int j=0;j<number_activities[i];j++){
			total_planned_cost+=milestone_list[i].activity_list[j].planned_cost;
		}
	}
	
	for (int i =0;i<number_milestones;i++){
		for (int j=0;j<number_activities[i];j++){
			planned_duration+=milestone_list[i].activity_list[j].planned_duration;
		}
	}
	
	project.planned_cost = total_planned_cost;

	if(planned_duration%8 !=0){
		project.planned_duration = (planned_duration/8)+1;
	}
	else{
		project.planned_duration = (planned_duration/8);
	}
	return project;
}

void print_main_menu(void){
	printf("\nMAIN MENU, Select one of the following:\n");
	printf("1-Update Activity\n2-Print stats\n3-Exit");
}

void update_activity(activity_t * activity_to_update){
	unsigned short int actual_duration = 0;
	char answer;
	printf("Enter the actual duration:");
	actual_duration = get_input_usi();
	activity_to_update->actual_duration = actual_duration;
	printf("Is the activity finished?(Y/N)");
	scanf(" %c",&answer);
	if(answer == 'Y'||answer == 'y'){
		activity_to_update->completed=1;
	}
	else{
		activity_to_update->completed=0;
	}
	activity_to_update->actual_duration = actual_duration;
	activity_to_update->actual_cost = actual_duration*30;
}

void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){
	_Bool complete =1;
	milestone_to_update->actual_duration=0;
	for (int i=0;i<activities_in_milestone;i++){
		milestone_to_update->actual_duration+=milestone_to_update->activity_list[i].actual_duration;
	}
	milestone_to_update->actual_cost=milestone_to_update->actual_duration*30;
	
	for(int i=0;i<activities_in_milestone;i++){
		if(milestone_to_update->activity_list[i].completed==0){
			complete =0;
		}
		
	}
	milestone_to_update->completed=complete;
}
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	my_project->actual_duration=0;
	my_project->actual_cost=0;
	for (int i =0;i<num_milestones;i++){
		my_project->actual_duration+=milestone_array[i].actual_duration;
	}
	if(my_project->actual_duration%8!=0){
		my_project->actual_duration= (my_project->actual_duration/8)+1;
	}
	else{
		my_project->actual_duration = my_project->actual_duration/8;
	}
	
	for (int i =0;i<num_milestones;i++){
		my_project->actual_cost+=milestone_array[i].actual_cost;
	}
	//printf("%u",my_project->actual_cost);
	_Bool complete = 1;
	for (int i = 0; i<num_milestones;i++){
		if(milestone_array[i].completed==0){
			complete = 0;
		}
	}
	my_project->completed = complete;
}

void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	printf("\n\nProject %s\n",details.name);
	
	if(details.completed==1){
		printf("Project is completed\n");
		if(details.planned_duration<details.actual_duration){
			printf("Finished %u days late\n",(details.actual_duration-details.planned_duration));
			printf("Finished $%.0f over budget\n",(details.actual_cost-details.planned_cost));
		}
		else{
			printf("Finished %u days early\n",(details.planned_duration-details.actual_duration));
			printf("Finished $%.0f under budget\n",(details.planned_cost-details.actual_cost));
		}
	}
	else{
		printf("Project is not completed\n");
		print_milestone_stats(list_milestones,num_milestones,number_activities);
	}
}

void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	unsigned short int num_activity_complete = 0;
	unsigned short int planned_duration = 0;
	unsigned short int planned_cost = 0;
	for (int i = 0;i<num_milestones;i++){
		unsigned short int planned_duration = 0;
		unsigned short int planned_cost = 0;
		num_activity_complete=0;

		for (int act = 0;act<number_activities[i];act++){
				planned_duration+=list_milestones[i].activity_list[act].planned_duration;
		}
		planned_cost = planned_duration*30;

		//prints differently whether or not the milestone is completed or not
		if(list_milestones[i].completed==1){
			printf("Miletone %s is complete\n%d out of %d activities complete\n",list_milestones[i].name,number_activities[i],number_activities[i]);
			//determines if the milestone was done over or under the time, as well as over or under budget
			if(planned_duration<list_milestones[i].actual_duration){
				printf("Finished Milestone %u hours late\n",(list_milestones[i].actual_duration-planned_duration));
				printf("Finished Milestone $%u over budget\n",(list_milestones[i].actual_duration-planned_duration)*30);
			}
			else{
				printf("Finished Milestone %u hours early\n",(planned_duration-list_milestones[i].actual_duration));
				printf("Finished Milestone $%u under budget\n",(planned_duration-list_milestones[i].actual_duration)*30);
			}
		}
		else{
			printf("Milestone %s is not complete\n",list_milestones[i].name);
			for(int j = 0;j<number_activities[i];j++){
				if (list_milestones[i].activity_list[j].completed==1){
					num_activity_complete+=1;
				}
			}
			printf("%u out of %u activities complete\n",num_activity_complete,number_activities[i]);
			printf("The Milestone's planned duration is %u hours\n",planned_duration);
			printf("The Milestone's planned cost is $%u\n",planned_cost);

		}
	}


}

// function to check for uniqueness
int unique(unsigned short int nums[],int size){
	for (int i = 0;i<size-1;i++){
		for (int j = i+1;j<size;j++){
			if(nums[i]==nums[j]){
				return 0;
			}
		}
	}
	return 1;
}