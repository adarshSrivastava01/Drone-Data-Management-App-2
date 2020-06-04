#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef struct Drone {
	int Drone_number;
	char Drone_name[20];
	float Max_distance,Load_capacity,highest_delivery_distance,highest_delivery_load;
}Dr;

typedef struct Delivery {
	int Drone_ID;
	char Drone_name[20];
	float Max_distance,Load_capacity,Distance_tvl,Load_delivered,Delivery_orig_loc_x,Delivery_orig_loc_y,Delivery_desti_loc_x,Delivery_desti_loc_y;
}Dlv;

int readData(Dr array[], char fileName[]) {
	/*
	Takes two arguments as Array of Structures and the name of file where to read data
	and fills the file data into various fields of structure
	*/
	FILE *ptr;
	char name[20];
	int number,cnt = 0,i;
	float max_distance,load_capacity,hdd,hdw;
	ptr = fopen(fileName,"r");
	if(ptr == NULL) {
		printf("\nSorry!! The File doesn't exist.");
	} else {
		while(fscanf(ptr,"%d %s %f %f %f %f\n",&number,name,&max_distance,&load_capacity,&hdd,&hdw) != -1) {
			array[cnt].Drone_number = number;
			strcpy(array[cnt].Drone_name, name);
			array[cnt].Max_distance = max_distance;
			array[cnt].Load_capacity = load_capacity;
			array[cnt].highest_delivery_distance = hdd;
			array[cnt].highest_delivery_load = hdw;
			cnt += 1;
		}
	}
	fclose(ptr);
	printf("\nList of Drone Information: \n");
	printf("\nDrone Number\tDrone Name\tMax Distance(km)\tLoad Capacity(kg)\tHighestDelDist\tHighest_Del_wg:\n");
	for(i=0; i<cnt ;i++) {
		printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_number,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].highest_delivery_distance,array[i].highest_delivery_load);
	}
	return cnt;
}

int a_in_b(Dr array[], int num, int length) {
	/*
	Simple Implementation of Linear Search
	returns index of structure if number matches otherwise -1
	*/
	int i=0;
	for(i=0; i<length ;i++) {
		if(array[i].Drone_number == num) {
			printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_number,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].highest_delivery_distance,array[i].highest_delivery_load);
			return i;
		}
	}
	return -1;
} 

void setDrones(Dr array[], int index) {
	/*
	Takes two args as Array of Structures and index position where to update
	Asks user to enter various details and updates the structure
	*/
	printf("\n-------------------------");
	printf("\nEnter The Drone Number: ");
	scanf("%d",&array[index].Drone_number);
	fflush(stdin);
	printf("\nEnter The Name of Drone: ");
	gets(array[index].Drone_name);
	fflush(stdin);
	printf("\nEnter The Max Distance of Drone: ");
	scanf("%f",&array[index].Max_distance);
	printf("\nEnter The Load Capacity of Drone: ");
	scanf("%f",&array[index].Load_capacity);
	printf("\nEnter The Highest Delivery Distance of Drone: ");
	scanf("%f",&array[index].highest_delivery_distance);
	printf("\nEnter The Highest Delivery Load of Drone: ");
	scanf("%f",&array[index].highest_delivery_load);
	printf("\n------------------------------------");
}

int add_update_drones(Dr array[], int index, int length) {
	/*
	takes three args as array of structs, index position and current length of array
	and it adds or update a drone info 
	*/
	if(index == -1) {
		printf("\nNo Drone exists with that Drone Number.\n");
		printf("You are going to add A New Drone.\n");
		setDrones(array, length);
		length += 1;
	} else {
		printf("\nDrone exists with that Drone Number.\n");
		printf("You are going to update A Drone.\n");
		setDrones(array, index);
	}
	return length;
}

void showDrones(Dr array[], int length) {
	/*
	Takes two args as array of structs and it's length
	and display all drone's info of that array
	*/
	int i = 0;
	printf("\nList of Drone Information: \n");
	printf("\nDrone Number\tDrone Name\tMax Distance(km)\tLoad Capacity(kg)\tHighestDelDist\tHighestDelLoad\n");
	for(i=0; i<length; i++) {
		printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_number,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].highest_delivery_distance,array[i].highest_delivery_load);
	}
}

void searchDroneByName(Dr array[], char query[], int length) {
	/*
	takes three args as array of structs , name as string and array's length
	returns info of a particular name if found
	if "all" entered displays all drones
	else gives error message
	*/
	int i;
	int j = 0;
	if(strcmpi(query,"all") != 0) {
		for(i=0; i<length; i++) {
			if(strcmpi(query, array[i].Drone_name) == 0) {
				printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_number,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].highest_delivery_distance,array[i].highest_delivery_load);
				j++;
			}
		}
		if(j==0)
			printf("\nNo Drones with that Drone Name..");
	} else {
		showDrones(array,length);
	}
}

int* searchDronesByCapability(int* arr, Dr Drone_info[], float dist, float dl_wg, int length) {
	/*
	takes an int array whose first elem is last index of that drone who is capable to delivery,
	and second one is no. of drones capable to do delivery
	array of structs, it's length, distance and del. weight
	*/
	int i = 0;
	arr[0] = -1;
	arr[1] = 0;
	for(i=0; i<length ;i++) {
		if(Drone_info[i].Max_distance >= dist && Drone_info[i].Load_capacity >= dl_wg) {
			arr[0] = i;
			arr[1] += 1;
		}
	}
	return arr;
}

int setDeliveryInfo(Dlv arrayDl[], Dr array[], int secLen, float x1, float y1, float x2, float y2, float dist, float dl_wg, int array_index, int possible) {
	/*
	takes delivery array, drone array, co-ordinates of point
	delivery weight, distance, length of arrays, index pos. of drone in drone array and
	no. of possible drones
	add that info in delivery array
	and also prints a decorated recipt in console window
	*/
	char choice;
	arrayDl[secLen].Drone_ID = array[array_index].Drone_number;
	strcpy(arrayDl[secLen].Drone_name,array[array_index].Drone_name);
	arrayDl[secLen].Max_distance = array[array_index].Max_distance;
	arrayDl[secLen].Load_capacity = array[array_index].Load_capacity;
	arrayDl[secLen].Delivery_orig_loc_x = x1;
	arrayDl[secLen].Delivery_orig_loc_y = y1;
	arrayDl[secLen].Delivery_desti_loc_x = x2;
	arrayDl[secLen].Delivery_desti_loc_y = y2;
	arrayDl[secLen].Load_delivered = dl_wg;
	arrayDl[secLen].Distance_tvl = dist;
	fflush(stdin);
	if(dist>array[array_index].highest_delivery_distance) {
		printf("\nDo you want to Update Value of Highest Delivery Distance, press Y to update otherwise an other key: ");
		scanf("%c",&choice);
		if(choice == 'Y' || choice == 'y') {
			array[array_index].highest_delivery_distance = dist;
		}
	}
	fflush(stdin);
	if(dl_wg>array[array_index].highest_delivery_load) {
		printf("\nDo you want to Update Value of Highest Delivery Load, press Y to update otherwise an other key: ");
		scanf("%c",&choice);
		if(choice == 'Y' || choice == 'y') {
			array[array_index].highest_delivery_load = dl_wg;
		}
	}
	secLen += 1;
	printf("\n--------------------------------");
	printf("\nDrone Test/Simulation Result");
	printf("\nDrone Information:");
	printf("\n--------------------------------\n");
	printf("\nDrone Number:\t%d",array[array_index].Drone_number);
	printf("\nDrone Name:\t%s",array[array_index].Drone_name);
	printf("\nMax Distance:\t%.2f",array[array_index].Max_distance);
	printf("\nLoad Capacity:\t%.2f",array[array_index].Load_capacity);
	printf("\nHighest Delivery Distance:\t%.2f",array[array_index].highest_delivery_distance);
	printf("\nHighest Delivery Load:\t%.2f",array[array_index].highest_delivery_load);
	printf("\n--------------------------------");
	printf("\nOriginal location(x1,y1):\t(%.2f, %.2f)",x1,y1);
	printf("\nDestination Location(x2,y2):\t(%.2f, %.2f)",x2,y2);
	printf("\nWeight Delivery:\t%.2f",dl_wg);
	printf("\n--------------------------------");
	printf("\nDistance of Delivery:\t%.2f",dist);
	if(possible > 1) {
		printf("\nPossible Other Drone:\tY");
	} else {
		printf("\nPossible Other Drone:\tN");
	}
	return secLen;
}

void showDelArray(Dlv array[], int length) {
	/*
	takes two args as delivery array and it's length
	and siplay all the drones in delivery array
	*/
	int i=0;
	for(i=0; i<length ;i++) {
		printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_ID,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].Delivery_orig_loc_x,array[i].Delivery_orig_loc_y,array[i].Delivery_desti_loc_x,array[i].Delivery_desti_loc_y,array[i].Load_delivered);
	}
}

void displaySimRes(Dlv array[], char name[], int length) {
	/*
	Takes two args as delivery array and drone name and array's length
	and prints it's simulation result
	*/
	int cnt,i;
	printf("\nRequired Simulation Result is:\n");
	printf("\nDroneID\tDrone Name\tMax Distance\tLoad Capacity\tDelOrigX\tDelOrigY\tDeldestX\tDelDestY\tLoadDel.: \n");
	if(strcmpi(name,"all")==0) {
		for(i=0; i<length ;i++) {
			printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_ID,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].Delivery_orig_loc_x,array[i].Delivery_orig_loc_y,array[i].Delivery_desti_loc_x,array[i].Delivery_desti_loc_y,array[i].Load_delivered);
		}
	} else {
		for(i=0; i<length ;i++) {
			if(strcmpi(array[i].Drone_name,name) == 0) {
				printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",array[i].Drone_ID,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].Delivery_orig_loc_x,array[i].Delivery_orig_loc_y,array[i].Delivery_desti_loc_x,array[i].Delivery_desti_loc_y,array[i].Load_delivered);
				cnt+=1;
			}
		}
		if(cnt == 0) {
			printf("\nNo Drone with this name has been simulated...");
		}
	}
}

void displayWinner(Dlv array[], int length) {
	/*
	takes two args as delivery array and it's length
	and prints info of winner drones acc to specified condition
	*/
	int w1=0,w2=0,i;
	float a1,a2;
	if(length > 0) {
		a1 = array[0].Distance_tvl;
		a2 = array[0].Load_delivered;
		for(i=0; i<length ;i++) {
			if(array[i].Distance_tvl > a1) {
				a1 = array[i].Distance_tvl;
				w1 = i;
			}
		}
		for(i=0; i<length ;i++) {
			if(array[i].Load_delivered > a2) {
				a2 = array[i].Load_delivered;
				w2 = i;
			}
		}
		printf("\n-------------------");
		printf("\nWinner Drone by Distance: ");
		printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",array[w1].Drone_ID,array[w1].Drone_name,array[w1].Max_distance,array[w1].Load_capacity,array[w1].Delivery_orig_loc_x,array[w1].Delivery_orig_loc_y,array[w1].Delivery_desti_loc_x,array[w1].Delivery_desti_loc_y,array[w1].Load_delivered);
		printf("\nWinner Drone by Delivery Load: ");
		printf("\n%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",array[w2].Drone_ID,array[w2].Drone_name,array[w2].Max_distance,array[w2].Load_capacity,array[w2].Delivery_orig_loc_x,array[w2].Delivery_orig_loc_y,array[w2].Delivery_desti_loc_x,array[w2].Delivery_desti_loc_y,array[w2].Load_delivered);
	} else {
		printf("\nSorry No Drone have been simulated yet....");
		printf("\n----------------------------------------------");
	}
}

void saveDroneData(char fileName[], Dr array[], int length) {
	/*
	Takes three args as filename and array of drones and it's length
	and prints info of all drones in that file in a formatted way
	*/
	FILE *ptr;
	int i = 0;
	ptr = fopen(fileName,"w");
	if(ptr == NULL) {
		printf("\nSorry Some Error Occured!!!");
	} else {
		for(i=0; i<length ;i++) {
			fprintf(ptr,"%d %s %.2f %.2f %.2f %.2f\n",array[i].Drone_number,array[i].Drone_name,array[i].Max_distance,array[i].Load_capacity,array[i].highest_delivery_distance,array[i].highest_delivery_load);
		}
	}
	fclose(ptr);
}

void saveDeliveryData(char fileName[], Dlv array[], int length) {
	/*
	takes three args as fileName , delivery array, it's length
	and prints it's report or simulation result in file
	*/
	int i = 0;
	FILE *fp;
	if(length == 0) {
		printf("\nSorry No drones Simulated, No data to be saved");
	} else {
	fp = fopen(fileName,"w");
	if(fp == NULL) {
		printf("\nSome Error occured while Saving Data.");
	} else {
		for(i=0; i<length ;i++) {
				fprintf(fp,"\n%s","------------------------------");
				fprintf(fp,"\nDrone Number: %d",array[i].Drone_ID);
				fprintf(fp,"\nDrone Name: %s",array[i].Drone_name);
				fprintf(fp,"\nMax_distance: %.2f",array[i].Max_distance);
				fprintf(fp,"\nLoad_capacity: %.2f",array[i].Load_capacity);
				fprintf(fp,"\nOriginal Location(x1,y1): %.2f %.2f",array[i].Delivery_orig_loc_x,array[i].Delivery_orig_loc_y);
				fprintf(fp,"\nDestination Location(x2,y2): %.2f %.2f",array[i].Delivery_desti_loc_x,array[i].Delivery_desti_loc_y);	
				fprintf(fp,"\nWeight Delivery: %.2f",array[i].Load_delivered);
				fprintf(fp,"\nDistance of Delivery: %.2f",array[i].Distance_tvl);
				fprintf(fp,"\n%s","------------------------------");
			}
		}
		fclose(fp);	
	}
} 

int main() {
	Dr Drone_info[50];
	Dlv Delivery_info[50];
	int current_length,index,update_drone_number,secondary_length = 0,array[2];
	char name[20];
	float distance,x1,y1,x2,y2,dl_wg;
	int* searched;
	int choice;
	
	printf("\n-----------------------------------");
	printf("\nWelcome To Drone Delivery Simulation Project");
	printf("\n-----------------------------------");
	current_length = readData(Drone_info, "Drone.txt");
	printf("\n-----------------------------------");
	printf("\nWelcome To Drone Delivery Simulation Project");
	printf("\n------------------------------------");
	while(1) {
		printf("\nMENU");
		printf("\n-----------------------------------");
		printf("\nEnter 1 to input/update drone information");
		printf("\nEnter 2 to Search a Drone");
		printf("\nEnter 3 to Simulate a Drone delivery Scenario");
		printf("\nEnter 4 to display Display Simulation results");
		printf("\nEnter 5 to Display Winner Drones");
		printf("\nEnter 6 to Save Drone Information");
		printf("\nEnter 7 to save all Results");
		printf("\nEnter 8 to exit the Program....");
		printf("\n-----------------------------------");
		printf("\nEnter Your Choice: ");
		scanf("%d",&choice);
		printf("\n-----------------------------------");
		fflush(stdin);
		
		switch(choice) {
			/*
			MENU Implemantion for different functionalities
			*/
			case 1: {
				printf("\nEnter The Drone Number you want to Search: ");
				scanf("%d",&update_drone_number);
				index = a_in_b(Drone_info, update_drone_number, current_length);
				current_length = add_update_drones(Drone_info, index, current_length);
				break;
			}
			
			case 2: {
				printf("\nEnter The Drone Name You want to Search: ");
				fflush(stdin);
				gets(name);
				searchDroneByName(Drone_info, name, current_length);				
				break;
			}
			
			case 3: {
				printf("\nEnter The Warehouse location point(x1, y1): ");
				scanf("%f%f",&x1,&y1);
				while(x1<=0 || x1>100) {
					printf("\nThe Value of x1 can't be this. Please Enter Again: ");
					scanf("%f",&x1);
				}
				while(y1<=0 || y1>100) {
					printf("\nThe Value of y1 can't be this. Please Enter Again: ");
					scanf("%f",&y1);
				}
				printf("\nEnter The Delivery Destination location point(x2, y2): ");
				scanf("%f%f",&x2,&y2);
				while(x2<=-100 || x2>100) {
					printf("\nThe Value of x2 can't be this. Please Enter Again: ");
					scanf("%f",&x2);
				}
				while(y2<=-100 || y2>100) {
					printf("\nThe Value of y2 can't be this. Please Enter Again: ");
					scanf("%f",&y2);
				}
				printf("\nEnter The Weight of Products to be delivered: ");
				scanf("%f",&dl_wg); 
				while(dl_wg<=0 || dl_wg>200) {
					printf("\nThe Value of delivery_weight can't be this. Please Enter Again: ");
					scanf("%f",&dl_wg);
				}
				distance = sqrt(pow((x1 - x2),2) + pow((y1 - y2), 2));
				searched = searchDronesByCapability(array, Drone_info, distance, dl_wg, current_length);
				if(searched[0]!=-1) {
					setDeliveryInfo(Delivery_info, Drone_info, secondary_length, x1, y1, x2, y2, distance, dl_wg, searched[0], searched[1]);
					secondary_length += 1;
				} else {
					printf("\nNo Drones Available");
				}				
				break;
			}
			
			case 4: {
				printf("\nEnter The Drone Name to View it's Simulation Result: ");
				fflush(stdin);
				gets(name);
				displaySimRes(Delivery_info, name, secondary_length);				
				break;
			}
			
			case 5: {
				displayWinner(Delivery_info, secondary_length);				
				break;
			}
			
			case 6: {
				saveDroneData("Drone.txt", Drone_info, current_length);
				printf("\nData has been saved.");				
				break;
			}
			
			case 7: {
				saveDeliveryData("Result.txt", Delivery_info, secondary_length);
				break;
			}
			
			case 8: {
				printf("\nYou asked to terminate the Program.");
				exit(3);
				break;
			}
			
			default: {
				printf("\nChoice is not Valid Enter Again: ");
				break;
			}
			
		}
		
	}	

}
