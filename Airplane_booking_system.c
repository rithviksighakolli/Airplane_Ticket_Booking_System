#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Passenger{
    char name[50];
    struct Passenger* next;
};
struct Flight{
    int flightNumber;
    struct Passenger* passengers;
    struct Flight* next;
};
struct Passenger* createpassenger(char name[]){
    struct Passenger* newPassenger=(struct Passenger*)malloc(sizeof(struct Passenger));
    strcpy(newPassenger->name,name);
    newPassenger->next=NULL;
    return newPassenger;
}
struct Flight* createflight(int flightNumber){
    struct Flight* newFlight=(struct Flight*)malloc(sizeof(struct Flight));
    newFlight->flightNumber=flightNumber;
    newFlight->passengers=NULL;
    newFlight->next=NULL;
    return newFlight;
}
void reserveticket(struct Flight* flights,char name[],int flightNumber){
    struct Flight* currentFlight=flights;
    while(currentFlight!=NULL&&currentFlight->flightNumber!=flightNumber){
        currentFlight=currentFlight->next;
    }
    if(currentFlight!=NULL){
        struct Passenger* newPassenger=createpassenger(name);
        newPassenger->next=currentFlight->passengers;
        currentFlight->passengers=newPassenger;
        printf("Ticket has been reserved to %s for the flight %d\n",name,flightNumber);
    }
    else{
        printf("Flight not found\n");
    }
}
void cancelreservation(struct Flight* flights,char name[]){
    struct Flight* currentFlight=flights;
    while(currentFlight!=NULL){
        struct Passenger* currentPassenger=currentFlight->passengers;
        struct Passenger* previousPassenger=NULL;
        while(currentPassenger!=NULL){
            if(strcmp(currentPassenger->name,name)==0){
                if(previousPassenger==NULL) {
                    currentFlight->passengers=currentPassenger->next;
                }
                else{
                    previousPassenger->next=currentPassenger->next;
                }
                free(currentPassenger);
                printf("Reservation for %s on flight %d is canceled\n",name,currentFlight->flightNumber);
                return;
            }
            previousPassenger=currentPassenger;
            currentPassenger=currentPassenger->next;
        }
        currentFlight=currentFlight->next;
    }    
    printf("No reservation found for %s\n",name);
}
void checkreservation(struct Flight* flights,char name[]){
    struct Flight* currentFlight=flights;
    int found=0;
    while(currentFlight!=NULL){
        struct Passenger* currentPassenger=currentFlight->passengers;
        while(currentPassenger!=NULL){
            if (strcmp(currentPassenger->name,name)==0){
                printf("%s has a reservation on flight %d\n",name,currentFlight->flightNumber);
                found=1;
                break;
            }
            currentPassenger=currentPassenger->next;
        }
        currentFlight=currentFlight->next;
    }
    if(!found){
        printf("%s does not have a reservation\n",name);
    }
}
void displaypassengers(struct Flight* flights,int flightNumber){
    struct Flight* currentFlight = flights;
    while(currentFlight!=NULL&&currentFlight->flightNumber!=flightNumber){
        currentFlight = currentFlight->next;
    }
    if(currentFlight!=NULL){
        struct Passenger* currentPassenger=currentFlight->passengers;
        printf("Passengers for flight %d:\n",flightNumber);
        while(currentPassenger!=NULL) {
            printf("%s\n",currentPassenger->name);
            currentPassenger=currentPassenger->next;
        }
    } else{
        printf("Flight not found\n");
    }
}
void addflight(struct Flight** flights,int flightNumber){
    struct Flight* newFlight=createflight(flightNumber);
    newFlight->next=*flights;
    *flights=newFlight;
    printf("The flight with the number %d has been added\n",flightNumber);
}
int main(){
    struct Flight* flights=NULL;
    int choice;
    while(1){
        printf("\nAirline Ticket Reservation System\n");
        printf("1 Reserve a ticket\n");
        printf("2 Cancel a reservation\n");
        printf("3 Check reservation\n");
        printf("4 Display passengers\n");
        printf("5 Add a new flight\n");
        printf("6 Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                char name[50];
                int flightnumber;
                printf("Enter passenger name: ");
                scanf("%s",name);
                printf("Enter flight number: ");
                scanf("%d",&flightnumber);
                reserveticket(flights,name,flightnumber);               
                break;
            }
            case 2:{
                char name[50];
                printf("Enter passenger name: ");
                scanf("%s",name);
                cancelreservation(flights,name);
                break;
            }
            case 3:{
                char name[50];
                printf("Enter passenger name: ");
                scanf("%s",name);
                checkreservation(flights,name);
                break;
            }
            case 4:{
                int flightnumber;
                printf("Enter flight number: ");
                scanf("%d",&flightnumber);
                displaypassengers(flights,flightnumber);
                break;
            }
            case 5:{
                int flightnumber;
                printf("Enter flight number to add: ");
                scanf("%d",&flightnumber);
                addflight(&flights,flightnumber);               
                break;
            }
            case 6:
                while(flights!=NULL){
                    struct Flight* temp=flights;
                    flights=flights->next;
                    while(temp->passengers!=NULL){
                        struct Passenger* passenger=temp->passengers;
                        temp->passengers=temp->passengers->next;
                        free(passenger);
                    }
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice please try again\n");
        }
    }
    return 0;
}