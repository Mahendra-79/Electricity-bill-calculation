#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer {
    int id;
    char name[50];
    int units;
    float bill;
};

float calculateBill(int units) {
    if (units <= 100)
        return units * 5;
    else if (units <= 200)
        return 100 * 5 + (units - 100) * 7;
    else
        return 100 * 5 + 100 * 7 + (units - 200) * 10;
}

void addRecord() {
    FILE *fp = fopen("bills.txt", "a");
    struct customer c;

    printf("Enter Customer ID\n: ");
    scanf("%d", &c.id);
    printf("Enter Name\n: ");
    // getchar(); // clear newline
    // fgets(c.name,sizeof(c.name),stdin);
    scanf("%s",c.name);
    // gets(c.name);
    printf("Enter Units Consumed\n: ");
    scanf("%d", &c.units);

    c.bill = calculateBill(c.units);

    fprintf(fp, "%d %s %d %.2f\n", c.id, c.name, c.units, c.bill);
    fclose(fp);
    printf("Record added successfully!\n");
}

void displayRecords() {
    FILE *fp = fopen("bills.txt", "r");
    struct customer c;
    printf("\n--- All Customer Records ---\n");
    printf("ID\tName\tUnits\tBill\n");

    while (fscanf(fp, "%d %s %d %f", &c.id, c.name, &c.units, &c.bill) ==4) {
        printf("%d\t%s\t%d\t%.2f\n", c.id, c.name, c.units, c.bill);
    }
    fclose(fp);
}

void searchRecord() {
    FILE *fp = fopen("bills.txt", "r");
    struct customer c;
    int id, found = 0;

    printf("Enter Customer ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &c.id, c.name, &c.units, &c.bill) ==4) {
        if (c.id == id) {
            printf("Record found:\n");
            printf("ID: %d\nName: %s\nUnits: %d\nBill: %.2f\n", c.id, c.name, c.units, c.bill);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Record not found!\n");
}

void updateRecord() {
    FILE *fp = fopen("bills.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct customer c;
    int id, found = 0;

    printf("Enter Customer ID to update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &c.id, c.name, &c.units, &c.bill) ==4) {
        if (c.id == id) {
            printf("Enter new units consumed: ");
            scanf("%d", &c.units);
            c.bill = calculateBill(c.units);
            found = 1;
        }
        fprintf(temp, "%d %s %d %.2f\n", c.id, c.name, c.units, c.bill);
    }

    fclose(fp);
    fclose(temp);
    remove("bills.txt");
    rename("temp.txt", "bills.txt");

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Record not found!\n");
}

void deleteRecord() {
    FILE *fp = fopen("bills.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct customer c;
    int id, found = 0;

    printf("Enter Customer ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &c.id, c.name, &c.units, &c.bill) ==4) {
        if (c.id != id)
            fprintf(temp, "%d %s %d %.2f\n", c.id, c.name, c.units, c.bill);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("bills.txt");
    rename("temp.txt", "bills.txt");

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found!\n");
}

int main() {
    int choice;
    do {
        printf("\n====== Electricity Bill Management System ======\n");
        printf("1. Add Record\n");
        printf("2. Display All Records\n");
        printf("3. Search by ID\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
             addRecord();
             break;
            case 2: 
             displayRecords();
             break;
            case 3: 
             searchRecord();
             break;
            case 4:
             updateRecord(); 
             break;
            case 5: 
             deleteRecord(); 
             break;
            case 6: 
             printf("Exiting program...\n"); 
            break;
            default: 
             printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
