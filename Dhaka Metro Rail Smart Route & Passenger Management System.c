#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Used for Metro Stations

struct Station
{
    int id;
    char name[50];
    double distance;

    struct Station *prev;
    struct Station *next;
};

struct Station *head = NULL;
struct Station *tail = NULL;

// CREATE NEW STATION NODE

struct Station* createStation(int id, char name[], double distance)
{
    struct Station *newStation;

    newStation = (struct Station*)malloc(sizeof(struct Station));

    newStation->id = id;
    strcpy(newStation->name, name);
    newStation->distance = distance;

    newStation->prev = NULL;
    newStation->next = NULL;

    return newStation;
}

// ADD STATION TO THE END

void addStation(int id, char name[], double distance)
{
    struct Station *newStation;

    newStation = createStation(id, name, distance);

    if (head == NULL)
    {
        head = newStation;
        tail = newStation;
    }
    else
    {
        tail->next = newStation;
        newStation->prev = tail;
        tail = newStation;
    }
}

// FIND STATION BY ID

struct Station* findStation(int id)
{
    struct Station *temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

// DISPLAY ALL STATIONS

void displayStations()
{
    struct Station *temp = head;

    printf("\n=================================================\n");
    printf("          DHAKA METRO RAIL - MRT LINE 6\n");
    printf("=================================================\n");

    while (temp != NULL)
    {
        printf("[%2d] %-25s %.1f KM\n",
               temp->id,
               temp->name,
               temp->distance);

        temp = temp->next;
    }

    printf("=================================================\n");
}

// DISPLAY STATIONS IN REVERSE

void displayReverse()
{
    struct Station *temp = tail;

    printf("\n=================================================\n");
    printf("             REVERSE STATION LIST\n");
    printf("=================================================\n");

    while (temp != NULL)
    {
        printf("[%2d] %-25s %.1f KM\n",
               temp->id,
               temp->name,
               temp->distance);

        temp = temp->prev;
    }

    printf("=================================================\n");
}

// SEARCH STATION

void searchStation()
{
    int id;

    printf("\nEnter Station ID: ");
    scanf("%d", &id);

    struct Station *result = findStation(id);

    if (result == NULL)
    {
        printf("\nStation not found!\n");
    }
    else
    {
        printf("\nStation Found!\n");
        printf("Station ID   : %d\n", result->id);
        printf("Station Name : %s\n", result->name);
        printf("Distance     : %.1f KM\n", result->distance);
    }
}

// FARE CALCULATION
// Academic Estimated Fare Model

int calculateFare(double distance)
{
    if (distance <= 3.0)
    {
        return 20;
    }
    else if (distance <= 6.0)
    {
        return 30;
    }
    else if (distance <= 9.0)
    {
        return 40;
    }
    else if (distance <= 12.0)
    {
        return 60;
    }
    else
    {
        return 100;
    }
}

// FIND ROUTE + DISTANCE + FARE + TIME

void findRouteAndFare(int sourceID, int destinationID)
{
    struct Station *source;
    struct Station *destination;
    struct Station *temp;

    double totalDistance;
    int stationsCrossed;
    int fare;
    int travelTime;

    int forward;


    // Find source station
    source = findStation(sourceID);

    // Find destination station
    destination = findStation(destinationID);


    // Check invalid station
    if (source == NULL || destination == NULL)
    {
        printf("\nInvalid Station ID!\n");
        return;
    }


    // Same station
    if (sourceID == destinationID)
    {
        printf("\nSource and destination are the same.\n");
        printf("Fare: 0 BDT\n");
        return;
    }


    // Calculate distance
    totalDistance =
        fabs(destination->distance - source->distance);


    // Calculate number of stations crossed
    stationsCrossed = abs(destinationID - sourceID);


    // Calculate fare
    fare = calculateFare(totalDistance);


    // Approximate travel time
    travelTime = stationsCrossed * 2;


    // Decide direction
    if (sourceID < destinationID)
    {
        forward = 1;
    }
    else
    {
        forward = 0;
    }

    // DISPLAY JOURNEY DETAILS

    printf("\n=================================================\n");
    printf("              JOURNEY DETAILS\n");
    printf("=================================================\n");

    printf("From               : %s\n", source->name);
    printf("To                 : %s\n", destination->name);

    printf("Total Distance     : %.1f KM\n", totalDistance);

    printf("Stations Crossed   : %d\n", stationsCrossed);

    printf("Estimated Time     : %d Minutes\n", travelTime);

    printf("Estimated Fare     : %d BDT\n", fare);


    // DISPLAY ROUTE

    printf("\nRoute:\n");


    if (forward == 1)
    {
        temp = source;

        while (temp != NULL)
        {
            printf("%s", temp->name);

            if (temp == destination)
            {
                break;
            }

            printf(" -> ");

            temp = temp->next;
        }
    }
    else
    {
        temp = source;

        while (temp != NULL)
        {
            printf("%s", temp->name);

            if (temp == destination)
            {
                break;
            }

            printf(" -> ");

            temp = temp->prev;
        }
    }


    printf("\n=================================================\n");
}

// Used for Passenger Management lq

struct Passenger
{
    int ticketID;
    char name[50];

    int sourceID;
    int destinationID;

    struct Passenger *next;
};


struct Queue
{
    struct Passenger *front;
    struct Passenger *rear;
};

// CREATE QUEUE

struct Queue* createQueue()
{
    struct Queue *q;

    q = (struct Queue*)malloc(sizeof(struct Queue));

    q->front = NULL;
    q->rear = NULL;

    return q;
};

// ENQUEUE PASSENGER

void enqueuePassenger(struct Queue *q,
                      int ticketID,
                      char name[],
                      int sourceID,
                      int destinationID)
{
    struct Passenger *newPassenger;

    newPassenger =
        (struct Passenger*)malloc(sizeof(struct Passenger));


    newPassenger->ticketID = ticketID;

    strcpy(newPassenger->name, name);

    newPassenger->sourceID = sourceID;

    newPassenger->destinationID = destinationID;

    newPassenger->next = NULL;


    // Queue is empty
    if (q->rear == NULL)
    {
        q->front = newPassenger;
        q->rear = newPassenger;
    }

    // Queue already has passengers
    else
    {
        q->rear->next = newPassenger;
        q->rear = newPassenger;
    }


    printf("\nPassenger added successfully!\n");
    printf("Ticket ID: %d\n", ticketID);
}

// DISPLAY PASSENGER QUEUE

void displayQueue(struct Queue *q)
{
    struct Passenger *temp;
    int position = 1;


    if (q->front == NULL)
    {
        printf("\nPassenger Queue is empty!\n");
        return;
    }


    printf("\n=================================================\n");
    printf("              PASSENGER TICKET QUEUE\n");
    printf("=================================================\n");


    temp = q->front;


    while (temp != NULL)
    {
        printf("%d. Ticket #%d | %s | %d -> %d\n",
               position,
               temp->ticketID,
               temp->name,
               temp->sourceID,
               temp->destinationID);

        position++;

        temp = temp->next;
    }


    printf("=================================================\n");
}

// DEQUEUE / PROCESS NEXT PASSENGER

void processPassenger(struct Queue *q)
{
    struct Passenger *temp;


    // Queue empty
    if (q->front == NULL)
    {
        printf("\nNo passenger waiting in the queue!\n");
        return;
    }


    // Take first passenger
    temp = q->front;


    printf("\n=================================================\n");
    printf("              PROCESSING TICKET\n");
    printf("=================================================\n");

    printf("Ticket ID : %d\n", temp->ticketID);

    printf("Passenger : %s\n", temp->name);


    // Show route and fare
    findRouteAndFare(temp->sourceID,
                     temp->destinationID);


    // Move front to next passenger
    q->front = q->front->next;


    // If queue becomes empty
    if (q->front == NULL)
    {
        q->rear = NULL;
    }


    // Free processed passenger
    free(temp);


    printf("\nTicket processed successfully!\n");
}

// BUILD MRT LINE

void buildMetroLine()
{
    addStation(0, "Uttara North", 0.0);

    addStation(1, "Uttara Center", 1.0);

    addStation(2, "Uttara South", 2.1);

    addStation(3, "Pallabi", 4.8);

    addStation(4, "Mirpur 11", 5.9);

    addStation(5, "Mirpur 10", 7.0);

    addStation(6, "Kazipara", 8.2);

    addStation(7, "Shewrapara", 9.3);

    addStation(8, "Agargaon", 11.0);

    addStation(9, "Bijoy Sarani", 12.3);

    addStation(10, "Farmgate", 13.4);

    addStation(11, "Karwan Bazar", 14.5);

    addStation(12, "Shahbagh", 15.7);

    addStation(13, "Dhaka University", 16.7);

    addStation(14, "Bangladesh Secretariat", 17.8);

    addStation(15, "Motijheel", 19.1);
}

// MAIN FUNCTION

int main()
{
    struct Queue *ticketQueue;

    int choice;

    int ticketCounter = 101;


    // Build Metro Station Linked List
    buildMetroLine();


    // Create Passenger Queue
    ticketQueue = createQueue();

    // MAIN MENU

    while (1)
    {
        printf("\n\n=================================================\n");
        printf("       DHAKA METRO RAIL SMART SYSTEM\n");
        printf("=================================================\n");


        printf("\n--- STATION MANAGEMENT ---\n");

        printf("1. View All Stations\n");

        printf("2. View Stations in Reverse\n");

        printf("3. Search Station\n");

        printf("4. Route & Fare Inquiry\n");


        printf("\n--- PASSENGER MANAGEMENT ---\n");

        printf("5. Add Passenger to Ticket Queue\n");

        printf("6. View Passenger Queue\n");

        printf("7. Process Next Passenger\n");


        printf("\n8. Exit\n");


        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        // OPTION 1

        if (choice == 1)
        {
            displayStations();
        }

        // OPTION 2

        else if (choice == 2)
        {
            displayReverse();
        }

        // OPTION 3

        else if (choice == 3)
        {
            searchStation();
        }

        // OPTION 4

        else if (choice == 4)
        {
            int source;
            int destination;


            printf("\nEnter Source Station ID      : ");

            scanf("%d", &source);


            printf("Enter Destination Station ID : ");

            scanf("%d", &destination);


            findRouteAndFare(source, destination);
        }

        // OPTION 5

        else if (choice == 5)
        {
            char name[50];

            int source;
            int destination;


            printf("\nEnter Passenger Name: ");

            scanf(" %[^\n]", name);


            printf("Enter Source Station ID: ");

            scanf("%d", &source);


            printf("Enter Destination Station ID: ");

            scanf("%d", &destination);


            if (source < 0 || source > 15 ||
                destination < 0 || destination > 15)
            {
                printf("\nInvalid Station ID!\n");
            }
            else
            {
                enqueuePassenger(ticketQueue,
                                 ticketCounter,
                                 name,
                                 source,
                                 destination);

                ticketCounter++;
            }
        }

        // OPTION 6

        else if (choice == 6)
        {
            displayQueue(ticketQueue);
        }

        // OPTION 7

        else if (choice == 7)
        {
            processPassenger(ticketQueue);
        }

        // OPTION 8

        else if (choice == 8)
        {
            printf("\nThank you for using Dhaka Metro Rail Smart System!\n");

            break;
        }

        // INVALID CHOICE

        else
        {
            printf("\nInvalid choice! Please select 1-8.\n");
        }
    }


    return 0;
}
