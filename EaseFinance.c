#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define Maximum_groups 5
#define Maximum_users 10
#define Name_Length 50

struct User {
    char name[Name_Length];
    double balance;
};

struct Group {
    struct User users[Maximum_users];
    int userCount;
    char activity[Name_Length];
    double totalCost;
};

struct Group groups[Maximum_groups];
int groupCount = 0;

// Function to create a new group
void createNewGroup() {
    if (groupCount >= Maximum_groups) {
        printf("Maximum group limit reached.\n");
        printf("\n\n\n\n");
        return;
    }

    struct Group newGroup;
    newGroup.userCount = 0;
    printf("===================================================================\n");
    printf("Enter the number of members in the group (maximum %d): ", Maximum_users);
    scanf("%d", &newGroup.userCount);
    getchar();

    if (newGroup.userCount <= 0 || newGroup.userCount > Maximum_users) {
        printf("Invalid number of members. Please try again.\n");
        return;
    }

    for (int i = 0; i < newGroup.userCount; i++) {
        printf("Enter the name of member %d: ", i + 1);
        fgets(newGroup.users[i].name, Name_Length, stdin);
        newGroup.users[i].name[strcspn(newGroup.users[i].name, "\n")] = '\0';
    }

    printf("===================================================================\n");
    printf("Enter the activity for today (e.g., breakfast, lunch, dinner, shopping): ");
    fgets(newGroup.activity, Name_Length, stdin);
    newGroup.activity[strcspn(newGroup.activity, "\n")] = '\0';
    printf("===================================================================\n");
    printf("Enter the total cost of the bill: ");
    scanf("%lf", &newGroup.totalCost);
    getchar();

    double perPersonCost;
    char splitOption;
    printf("===================================================================\n");
    printf("Do you want to split the bill equally among group members? (Y/N): ");
    scanf("%c", &splitOption);
    getchar();

    if (splitOption == 'Y' || splitOption == 'y') {
        perPersonCost = newGroup.totalCost / newGroup.userCount;

        printf("===================================================================\n");
        printf("Everyone paid %.2lf equally\n", perPersonCost);
        printf("All debt clear. No one owes anything! \n\n\n");
    } else {
        printf("===================================================================\n");
        double totalPaid = 0.0;
        for (int i = 0; i < newGroup.userCount; i++) {
            printf("Enter the amount paid by %s: ", newGroup.users[i].name);
            scanf("%lf", &newGroup.users[i].balance);
            getchar();

            totalPaid += newGroup.users[i].balance;
        }
    }

    groups[groupCount] = newGroup;
    groupCount++;
}


// Function to load previous group details
void loadPreviousDetails() {


    for (int i = 0; i < groupCount; i++) {
        printf("======================DETAILS======================\n");
        printf("Group %d:\n", i + 1);
        printf("Activity: %s\n", groups[i].activity);
        printf("Total Cost: %.2f\n", groups[i].totalCost);
        printf("User Balances:\n");
        for (int j = 0; j < groups[i].userCount; j++) {
            printf("%s: %.2f\n", groups[i].users[j].name, groups[i].users[j].balance);
        }

        // Calculate amount owed
        double* amountOwed = malloc(groups[i].userCount * sizeof(double));
        memset(amountOwed, 0, groups[i].userCount * sizeof(double));

        for (int j = 0; j < groups[i].userCount; j++) {
            for (int k = 0; k < groups[i].userCount; k++) {
                if (j != k) {
                    amountOwed[j] += groups[i].users[k].balance;
                }
            }
        }
printf("===================================================================\n");
        printf("Amount Owed:\n");
        for (int j = 0; j < groups[i].userCount; j++) {
            printf("%s owes %.2f to others.\n", groups[i].users[j].name, amountOwed[j]);
        }

    }
}

// Function to save data to a text file
void saveDataToFile(const char* splitwise) {
    FILE* file = fopen(splitwise, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d\n", groupCount);

    for (int i = 0; i < groupCount; i++) {
        fprintf(file, "%d\n", groups[i].userCount);
        fprintf(file, "%s\n", groups[i].activity);
        fprintf(file, "%.2f\n", groups[i].totalCost);

        for (int j = 0; j < groups[i].userCount; j++) {
            fprintf(file, "%s %.2f\n", groups[i].users[j].name, groups[i].users[j].balance);
        }
    }

    fclose(file);
}

// Function to load data from a text file
void loadDataFromFile(const char* splitwise) {
    FILE* file = fopen(splitwise, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    fscanf(file, "%d\n", &groupCount);

    for (int i = 0; i < groupCount; i++) {
        struct Group loadedGroup;
        fscanf(file, "%d\n", &loadedGroup.userCount);
        fgets(loadedGroup.activity, Name_Length, file);
        loadedGroup.activity[strcspn(loadedGroup.activity, "\n")] = '\0';

        fscanf(file, "%lf\n", &loadedGroup.totalCost);

        for (int j = 0; j < loadedGroup.userCount; j++) {
            fscanf(file, "%s %lf\n", loadedGroup.users[j].name, &loadedGroup.users[j].balance);
        }

        groups[i] = loadedGroup;
    }

    fclose(file);
}


int main() {
    const char* splitwise = "splitwise.txt";

    // Load previous details from the file
    loadDataFromFile(splitwise);

    printf("===== Splitwise App =====\n");
    printf("Options:\n");
    printf("1. Create New Group\n");
    printf("2. Load Previous Details\n");
    printf("3. Exit\n");
    printf("===================================================================\n");

    while (true) {
        int option;
        printf("Enter your choice: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                createNewGroup();
                saveDataToFile(splitwise);
                break;
            case 2:
                system("clear");
                loadPreviousDetails();
                break;
            case 3:
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        printf("\n===== Splitwise App =====\n");
        printf("Options:\n");
        printf("1. Create New Group\n");
        printf("2. Load Previous Details\n");
        printf("3. Exit\n");
        printf("===================================================================\n");
    }

    return 0;
}

