#include <stdio.h>
#include <string.h>

struct Event {
    char name[50];
    char date[15];
    char location[50];
    char organizer[30];
};

struct Event events[500];
int eventCount = 0;


void saveEventsToFile() {
    FILE *fp = fopen("events.txt", "w"); 
    if (!fp) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }

    for (int i = 0; i < eventCount; i++) {
        fprintf(fp, "%s|%s|%s|%s\n", 
            events[i].name, 
            events[i].date, 
            events[i].location, 
            events[i].organizer
        );
    }

    fclose(fp); 
    printf("All events have been saved to 'events.txt'.\n");
}

void loadEventsFromFile() {
    FILE *fp = fopen("events.txt", "r");
    if (!fp) {
        printf("No saved events found. Starting fresh.\n");
        return;
    }

    eventCount = 0; 
    char c;
    int index = 0, field = 0;
    char buffer[50]; 

    while ((c = fgetc(fp)) != EOF) {
        if (c == '|' || c == '\n') {
            buffer[index] = '\0'; 
            switch (field) {
                case 0: strncpy(events[eventCount].name, buffer, 49); break;
                case 1: strncpy(events[eventCount].date, buffer, 14); break;
                case 2: strncpy(events[eventCount].location, buffer, 49); break;
                case 3: strncpy(events[eventCount].organizer, buffer, 29); break;
            }
            field++;
            index = 0;

            if (c == '\n') { 
                eventCount++;
                field = 0;
            }
        } else {
            buffer[index++] = c; 
        }
    }

    fclose(fp);
    printf("Loaded %d event(s) from 'events.txt'.\n", eventCount);
}



void addEvent() {
    if (eventCount >= 500) {
        printf("Event limit reached! Cannot add more events.\n");
        return;
    }

    struct Event newEvent;
    printf("Enter the event name:\n");
    getchar(); 
    fgets(newEvent.name, sizeof(newEvent.name), stdin);
    strtok(newEvent.name, "\n"); 

    printf("Enter the event date (DD/MM/YYYY):\n");
    fgets(newEvent.date, sizeof(newEvent.date), stdin);
    strtok(newEvent.date, "\n");

    printf("Enter the event location:\n");
    fgets(newEvent.location, sizeof(newEvent.location), stdin);
    strtok(newEvent.location, "\n");

    printf("Enter the event organizer:\n");
    fgets(newEvent.organizer, sizeof(newEvent.organizer), stdin);
    strtok(newEvent.organizer, "\n");

    events[eventCount] = newEvent;
    eventCount++;
    printf("Event added successfully!\n");
}


void printAllEvents() {
    printf("*************************************\n");
    for (int i = 0; i < eventCount; i++) {
        printf("Event %d:\n", i + 1);
        printf("Name: %s\n", events[i].name);
        printf("Date: %s\n", events[i].date);
        printf("Location: %s\n", events[i].location);
        printf("Organizer: %s\n", events[i].organizer);
    }
    printf("*************************************\n");
}


void printEventsByFilter() {
    int filterOption;
    printf("Enter 1 to filter by location or 2 to filter by date:\n");
    scanf("%d", &filterOption);

    if (filterOption == 1) {
        char location[50];
        printf("Enter the location:\n");
        getchar();
        fgets(location, sizeof(location), stdin);
        strtok(location, "\n");

        printf("Events at location %s:\n", location);
        for (int i = 0; i < eventCount; i++) {
            if (strcmp(events[i].location, location) == 0) {
                printf("%s on %s organized by %s\n", events[i].name, events[i].date, events[i].organizer);
            }
        }
    } else if (filterOption == 2) {
        char date[15];
        printf("Enter the date (DD/MM/YYYY):\n");
        getchar();
        fgets(date, sizeof(date), stdin);
        strtok(date, "\n");

        printf("Events on date %s:\n", date);
        for (int i = 0; i < eventCount; i++) {
            if (strcmp(events[i].date, date) == 0) {
                printf("%s at %s organized by %s\n", events[i].name, events[i].location, events[i].organizer);
            }
        }
    }
}

void updateEvent() {
    char eventName[50];
    printf("Enter the name of the event you want to update:\n");
    getchar();
    fgets(eventName, sizeof(eventName), stdin);
    strtok(eventName, "\n");

    for (int i = 0; i < eventCount; i++) {
        if (strcmp(events[i].name, eventName) == 0) {
            printf("Event found! Select the detail to update:\n");
            printf("1. Update Name\n");
            printf("2. Update Date\n");
            printf("3. Update Location\n");
            printf("4. Update Organizer\n");
            int updateOption;
            scanf("%d", &updateOption);

            getchar();
            if (updateOption == 1) {
                printf("Enter the new name:\n");
                fgets(events[i].name, sizeof(events[i].name), stdin);
                strtok(events[i].name, "\n");
            } else if (updateOption == 2) {
                printf("Enter the new date (DD/MM/YYYY):\n");
                fgets(events[i].date, sizeof(events[i].date), stdin);
                strtok(events[i].date, "\n");
            } else if (updateOption == 3) {
                printf("Enter the new location:\n");
                fgets(events[i].location, sizeof(events[i].location), stdin);
                strtok(events[i].location, "\n");
            } else if (updateOption == 4) {
                printf("Enter the new organizer:\n");
                fgets(events[i].organizer, sizeof(events[i].organizer), stdin);
                strtok(events[i].organizer, "\n");
            } else {
                printf("Invalid option\n");
            }
            printf("Event updated successfully!\n");
            return;
        }
    }
    printf("Event not found\n");
}


void deleteEventByName() {
    char eventName[50];
    printf("Enter the name of the event you want to delete:\n");
    getchar();
    fgets(eventName, sizeof(eventName), stdin);
    strtok(eventName, "\n");

    for (int i = 0; i < eventCount; i++) {
        if (strcmp(events[i].name, eventName) == 0) {
            for (int j = i; j < eventCount - 1; j++) {
                events[j] = events[j + 1];
            }
            eventCount--;
            printf("Event deleted successfully!\n");
            return;
        }
    }
    printf("Event not found\n");
}

void deleteEventsByDate() {
    char eventDate[15];
    printf("Enter the date (DD/MM/YYYY) of the events you want to delete:\n");
    getchar();
    fgets(eventDate, sizeof(eventDate), stdin);
    strtok(eventDate, "\n");

    int deletedCount = 0;
    for (int i = 0; i < eventCount; i++) {
        if (strcmp(events[i].date, eventDate) == 0) {
            for (int j = i; j < eventCount - 1; j++) {
                events[j] = events[j + 1];
            }
            eventCount--;
            i--;
            deletedCount++;
        }
    }
    if (deletedCount > 0) {
        printf("%d event(s) on %s deleted successfully!\n", deletedCount, eventDate);
    } else {
        printf("No events found on %s\n", eventDate);
    }
}

int main() {
    int option;

    loadEventsFromFile(); 

    while (1) {
        printf("*************************************\n");
        printf("Press 1 to add a new event\n");
        printf("Press 2 to print events\n");
        printf("Press 3 to update an event\n");
        printf("Press 4 to delete an event\n");
        printf("Press 5 to save events to file\n");
        printf("Press 0 to exit\n");
        printf("*************************************\n");
        scanf("%d", &option);

        if (option == 1) {
            addEvent();
        } else if (option == 2) {
            int subOption;
            printf("Enter 1 to list all events or 2 to filter by location/date:\n");
            scanf("%d", &subOption);
            if (subOption == 1) {
                printAllEvents();
            } else if (subOption == 2) {
                printEventsByFilter();
            }
        } else if (option == 3) {  
            updateEvent();
        } else if (option == 4) {
            int subOption;
            printf("Enter 1 to delete by name or 2 to delete by date:\n");
            scanf("%d", &subOption);
            if (subOption == 1) {
                deleteEventByName();
            } else if (subOption == 2) {
                deleteEventsByDate();
            }
        } else if (option == 5) {
            saveEventsToFile();
        } else if (option == 0) {
            saveEventsToFile(); 
            printf("Thank you for using the Event Management System\n");
            break;
        } else {
            printf("Invalid option\n");
        }
    }

    return 0;
}
